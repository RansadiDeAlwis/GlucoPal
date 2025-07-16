# GlucoPal 🩺 – Non-Invasive Blood Glucose Monitoring  
**Team NeuroBytes | University of Moratuwa**

---

## 🔍 Project Overview

**GlucoPal** is a **non-invasive, low-cost, portable device** for real-time blood glucose monitoring using **Near-Infrared (NIR) spectroscopy** and **Photoplethysmography (PPG)**. The system addresses the global diabetes epidemic, particularly in regions like **Sri Lanka**, where **20% of adults** are diabetic or pre-diabetic—many undiagnosed due to lack of screening tools.

**Goal:** Eliminate painful and costly finger-prick tests through a user-friendly device powered by optical sensing and AI.

---

## ⚙️ How It Works

1. **Finger Placement**: User places a finger on a 3D-printed sensor clip.
2. **Signal Acquisition**: A 940nm IR emitter/receiver captures PPG signals.
3. **Signal Processing**: ESP32 microcontroller amplifies, filters, and transmits data to a Raspberry Pi.
4. **Model Inference**: A trained **1D ResNet34 model** predicts glucose levels from the PPG data.
5. **Display Output**: Results are shown on an onboard OLED display.

---

## 🧪 Technologies Used

- **Hardware**: ESP32, IR emitter/receiver (940nm), TL084 op-amp, Raspberry Pi, OLED Display
- **Software**: PyTorch, SciPy, NumPy, Matplotlib
- **AI Model**: Customized **1D ResNet34** for regression
- **Signal Features**: Filtering, downsampling, normalization, segmentation
- **Cloud Integration**: **AWS Lambda**, **Amazon S3**, **Amazon DynamoDB**, **MQTT via AWS IoT Core**

---

## ☁️ Cloud Infrastructure (AWS Integration)

GlucoPal is designed with **IoT connectivity and cloud-based data management**, providing secure and scalable storage, processing, and analysis.

### AWS Components

| Service | Role |
|----------|------|
| **AWS Lambda** | Serverless preprocessing, validation, and forwarding |
| **Amazon S3** | Stores raw and processed PPG signal data, logs, backups |


---

### Data Flow
ESP32 → MQTT (AWS IoT Core) → AWS Lambda → S3 + DynamoDB → Visualization / Notifications


---

### Why Cloud?

- **Remote Access**: Patients and clinicians can access historical glucose data remotely.
- **Scalability**: No limits on data storage or concurrent users.
- **Security**: AWS IoT Core ensures secure MQTT communication with TLS.
- **Cost-Effective**: Pay-per-use model via AWS Lambda & S3.
- **Alerts & Automation**: Easy to integrate with AWS SNS or other health record systems.

---

## 🧬 Dataset

- **Source**: University of Science and Technology of Mazandaran, Iran
- **Type**: PPG signals at 2175Hz, labeled with glucose levels

### Preprocessing Pipeline

- Downsampling to **100Hz**
- Bandpass filtering (**0.5–8 Hz**)
- Zero-phase filtering & normalization
- Segmentation into **1-second windows**

---

## 📊 Model Performance

| Metric | Value |
|---------|-------|
| **Architecture** | Custom **1D ResNet34** |
| **RMSE** | 16.42 mg/dL |
| **MAE** | 13.41 mg/dL |
| **Clarke Error Grid** | Zone A & B (clinically acceptable) |
| **Inference Device** | Raspberry Pi |

---

## 🛠️ Features

- **Non-invasive** measurement
- **On-device display** via OLED
- **Wireless real-time communication** (ESP32 ↔ Raspberry Pi ↔ AWS)
- **Cloud-based storage and alerts**
- **Reusable, sustainable design** (no strips needed)
- **Low-cost components**, locally sourced

---

## 🖥️ Visualization & Monitoring

- **AWS S3**: For secure data logging of raw signals and glucose estimations.
- **AWS DynamoDB**: For structured storage of patient glucose history.
- **Web Dashboard / Node-RED (Optional)**: For live data monitoring.
- **AWS SNS**: For real-time alerts to caregivers or healthcare providers.

---

## ![Testing Frame](https://github.com/user-attachments/assets/0e1d9be2-4969-4f47-8db1-878491923e6e)

---

## 🔐 Ethics & IP

- **Ethical clearance** in progress for clinical testing.
- **No Personally Identifiable Information (PII)** is stored.
- **Intellectual Property** includes:
  - Custom signal acquisition circuitry
  - 3D-printed ergonomic enclosure
  - Cloud-integrated AI processing pipeline

---

## 🚀 Future Improvements

- **On-device AI inference** (eliminate Raspberry Pi dependency)
- **Edge processing with AWS Greengrass**
- **Clinical fine-tuning** with Sri Lankan patient data
- **Fully portable version** with LTE/Mobile MQTT connectivity

---

## 👨‍🔬 Team NeuroBytes

- **W. M. Ransadi de Alwis**  
- **Pravindu Goonetilleke**  
- **Mohamed Irshad Nadha**  
- **Pulasthi H. J. Udugamasooriya**

### Mentors

- Dr. Navoda Atapattu (Lady Ridgeway Hospital)  
- Dr. Nayana S. Fernando (UoM Faculty of Medicine)

---

## 📘 References

- [PPG Glucose Estimation Research](https://pmc.ncbi.nlm.nih.gov/articles/PMC10331674/)
- [PPG Dataset – Mendeley Data](https://doi.org/10.17632/37pm7jk7jn.3)

---

**Empowering early diabetes detection with innovation and accessibility.**


