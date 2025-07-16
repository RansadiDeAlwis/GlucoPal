#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "";
const char* password = "";
const char* serverURL = ""; // API URL

// Analog read
const int analogPin = 34; // Using GPIO34 (ADC1_CH6)
const int numSamples = 1000; // Collect 1000 samples
int readings[numSamples];

// Button
const int buttonPin = 23; // GPIO23 for exit button

// OLED Display config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Local HTTP server
WebServer server(8000);  // For receiving glucose data
float receivedGlucose = -1;  // Store last received glucose value

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();
  delay(1000);
  display.clearDisplay();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup HTTP endpoint to receive glucose result
  server.on("/receive", HTTP_POST, []() {
    if (server.hasArg("plain")) {
      String body = server.arg("plain");
      int glucoseIndex = body.indexOf("glucose");
      if (glucoseIndex != -1) {
        int colon = body.indexOf(":", glucoseIndex);
        int endBrace = body.indexOf("}", colon);
        if (colon != -1 && endBrace != -1) {
          String glucoseStr = body.substring(colon + 1, endBrace);
          receivedGlucose = glucoseStr.toFloat();
          Serial.print("Received glucose: ");
          Serial.println(receivedGlucose);

          // Display glucose on OLED
          display.clearDisplay();
          display.setCursor(0, 0);
          display.setTextSize(1);
          display.println("GLUCOSE:");
          display.setTextSize(2);
          display.setCursor(0, 16);
          display.print(receivedGlucose);
          display.println(" mg/dL");
          display.display();
        }
      }
    }
    server.send(200, "application/json", "{\"message\":\"Glucose received\"}");
  });

  server.begin();
  Serial.println("Local HTTP server started at port 8000");
}

void loop() {
  // Handle any incoming glucose result
  server.handleClient();

  // Collect 1000 analog readings
  Serial.println("Collecting data...");
  display.clearDisplay();

  for (int i = 0; i < numSamples; i++) {
    int sensorValue = analogRead(analogPin);
    readings[i] = 4096 - sensorValue;

    Serial.println(sensorValue);

    int amplifiedValue = sensorValue * 10;
    int y = map(sensorValue, 1900, 2250, SCREEN_HEIGHT, 0);
    y = constrain(y, 0, SCREEN_HEIGHT);
    int x = map(i, 0, numSamples, 0, SCREEN_WIDTH);

    if (x < SCREEN_WIDTH) {
      display.drawPixel(x, y, SSD1306_WHITE);
    }

    if (i % 8 == 0) {
      display.display();
    }

    delay(10); // ~100Hz sampling
  }

  display.display();

  Serial.println("Data collection complete. Sending to server...");

  // Send data to Server
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;

    if (https.begin(client, serverURL)) {  // HTTPS
      https.addHeader("Content-Type", "application/json");

      String csvData = "";
      for (int i = 0; i < numSamples; i++) {
        csvData += String(readings[i]);
        if (i < numSamples - 1) csvData += ",";
      }

      String jsonPayload = "{\"values\":[" + csvData + "]}";

      int httpResponseCode = https.POST(jsonPayload);

      if (httpResponseCode > 0) {
        String response = https.getString();
        Serial.print("Server response: ");
        Serial.println(response);

        // *** NEW CODE TO DISPLAY GLUCOSE ON OLED ***
        int glucoseIndex = response.indexOf("glucose");
        if (glucoseIndex != -1) {
          int colon = response.indexOf(":", glucoseIndex);
          int endBrace = response.indexOf("}", colon);
          if (colon != -1 && endBrace != -1) {
            String glucoseStr = response.substring(colon + 1, endBrace);
            receivedGlucose = glucoseStr.toFloat();

            display.clearDisplay();
            display.setCursor(0, 0);
            display.setTextSize(1);
            display.println("GLUCOSE:");
            display.setTextSize(2);
            display.setCursor(0, 16);
            display.print(receivedGlucose);
            display.println(" mg/dL");
            display.display();
          }
        }
      } else {
        Serial.print("Error sending POST. HTTP response code: ");
        Serial.println(httpResponseCode);
      }

      https.end();
    } else {
      Serial.println("Unable to connect");
    }
  } else {
    Serial.println("WiFi disconnected. Cannot send data.");
  }

  // Wait until button is pressed
  Serial.println("Waiting for button press to restart...");
  while (true) {
    server.handleClient(); // Keep checking for glucose result
    if (digitalRead(buttonPin) == LOW) {
      Serial.println("Button pressed! Restarting data collection...");
      delay(500); // debounce
      break;
    }
  }
}
