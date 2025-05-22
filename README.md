# GlucoPal 🩺 – Non-Invasive Blood Glucose Monitoring  
**Team NeuroBytes | University of Moratuwa**

## 🔍 Project Overview
**GlucoPal** is a non-invasive, low-cost, and portable device for real-time blood glucose monitoring using **Near-Infrared (NIR) spectroscopy** and **Photoplethysmography (PPG)**. The system addresses the global diabetes epidemic, especially in resource-limited regions like Sri Lanka, where 20% of adults are diabetic or pre-diabetic, many undiagnosed due to limited screening tools.

Our goal: eliminate the need for painful and costly finger-prick methods through a user-friendly device powered by optical sensing and AI.

---

## ⚙️ How It Works

1. **Finger Placement**: User places a finger on a custom 3D-printed sensor clip.
2. **Signal Acquisition**: A 940nm IR emitter/receiver captures PPG signals.
3. **Signal Processing**: ESP32 microcontroller amplifies, filters, and sends data to a Raspberry Pi.
4. **Model Inference**: A trained 1D ResNet34 model predicts glucose levels from the PPG data.
5. **Display Output**: Results are shown on an onboard OLED screen.

---

## 🧪 Technologies Used

- **Hardware**: ESP32, IR emitter/receiver (940nm), TL084 op-amp, Raspberry Pi, OLED Display
- **Software**: PyTorch, SciPy, NumPy, Matplotlib
- **AI Model**: Customized 1D ResNet34 for regression
- **Signal Features**: Extracted via filtering, downsampling, normalization, and segmentation

---

## 🧬 Dataset

- **Source**: University of Science and Technology of Mazandaran, Iran
- **Type**: PPG signals at 2175Hz, labeled with glucose levels
- **Preprocessing**:
  - Downsampling to 100Hz
  - Bandpass filtering (0.5–8 Hz)
  - Zero-phase filtering & normalization
  - Segmentation into 1-second windows

---

## 📊 Model Performance

- **Architecture**: Custom 1D ResNet34
- **Test Results**:
  - **RMSE**: 16.42 mg/dL
  - **MAE**: 13.41 mg/dL
  - **Clarke Error Grid**: Most predictions fall in clinically acceptable Zone A & B
- **Inference Device**: Raspberry Pi

---

## 🛠️ Features

- Non-invasive measurement
- On-device display via OLED
- Reusable and sustainable design (no strips)
- Low-cost and local component sourcing
- Real-time wireless communication (ESP32 ↔ Raspberry Pi)

---

## 🔐 Ethics & IP

- Ethical data collection approval in progress
- No PII stored
- IP includes custom circuitry, 3D-printed enclosure, and integrated processing pipeline

---

## 🚀 Future Improvements

- On-device model deployment on ESP32 (no Raspberry Pi needed)
- Clinical fine-tuning with locally collected data
- Improved portability and real-time security

---

## 👨‍🔬 Team NeuroBytes

- W. M. Ransadi de Alwis  
- Pravindu Goonetilleke  
- Mohamed Irshad Nadha  
- Pulasthi H. J. Udugamasooriya  

Mentors:  
Dr. Navoda Atapattu (Lady Ridgeway Hospital)  
Dr. Nayana S. Fernando (UoM Faculty of Medicine)

---

## 📘 References

- [PPG Glucose Estimation Research](https://pmc.ncbi.nlm.nih.gov/articles/PMC10331674/)
- [PPG Dataset – Mendeley Data](https://doi.org/10.17632/37pm7jk7jn.3)

---

**Empowering early diabetes detection with innovation and accessibility.**
