# 🤖 GlucoPal: Machine Learning for Non-Invasive Glucose Prediction

This repository contains the machine learning pipeline for **GlucoPal**, a non-invasive glucometer using PPG signals and deep learning. This component is responsible for predicting blood glucose levels from optical signals acquired through an ESP32-based sensor.

---

## 📁 Dataset

- **Source**: [University of Science and Technology of Mazandaran (MUST), Iran](https://doi.org/10.17632/37pm7jk7jn.3)
- **Samples**: 67 raw PPG signals from 23 individuals
- **Sampling Rate**: 2175 Hz
- **Features**:
  - Green LED (550 nm) PPG signals
  - Age, gender
  - Invasively measured blood glucose levels
![download (3)](https://github.com/user-attachments/assets/6cc39898-a4ac-4da9-a58a-87756ff47b7c)

---

## 🛠️ Preprocessing Steps

1. **Downsampling**:
   - From 2175 Hz → 100 Hz using linear interpolation
2. **Filtering**:
   - 3rd-order Butterworth bandpass (0.5–8 Hz) via `scipy.signal`
   - Zero-phase filtering to preserve temporal structure
3. **Normalization**:
   - Standardization to zero mean and unit variance
4. **Segmentation**:
   - Split into 1-second windows (100 samples per segment)

---

## 🧠 Model Architecture – 1D ResNet34

A custom 1D version of ResNet34 was implemented using **PyTorch** for time-series PPG regression.

### 🔧 Structure Overview

- **Input**: (batch_size, 1, 100)
- **Initial Conv1D Layer** (64 filters, kernel size 7) + BatchNorm + ReLU + MaxPooling
- **Residual Blocks**:
  - 3 × [64 filters]
  - Transition: Conv1D → 128
  - 3 × [128 filters]
  - Transition: Conv1D → 256
  - 3 × [256 filters]
- **Global Average Pooling**
- **Dense Layer** (256 units + ReLU)
- **Dropout** (0.5)
- **Output**: 1 neuron (regression output)

---

## 🏋️‍♂️ Training Details

- **Framework**: PyTorch
- **Loss Function**: Mean Squared Error (MSE)
- **Optimizer**: Adam
- **Batch Size**: 64
- **Epochs**: 50 (adjustable)
- **Validation Split**: 20%

---

## 📊 Model Performance

### 📈 Evaluation Metrics
- **Root Mean Squared Error (RMSE)**: `16.42 mg/dL`
- **Mean Absolute Error (MAE)**: `13.41 mg/dL`
- **Clarke Error Grid Analysis**:
  - Majority of predictions in Zones **A** & **B** (clinically acceptable)
  - Minimal predictions in Zones C–E
![download (1)](https://github.com/user-attachments/assets/1a21dd73-3e03-404a-88e3-b61d672e2fc5)

![download (2)](https://github.com/user-attachments/assets/eb929d8a-28e6-4179-bc0e-f3dd6f8972ad)

---

## 🖥️ Inference Pipeline

- The trained model runs on a **Raspberry Pi**, receiving PPG data from an ESP32 over Wi-Fi.
- Preprocessing and inference are done on-device using the trained PyTorch model.
- Output is transmitted back to the ESP32 and displayed on an OLED screen.

---
