# IoT Home Surveillance System

## 📌 Overview
This project implements an IoT-based home surveillance system using ESP32, PIR sensor, and a PC webcam.

- PIR sensor detects motion
- ESP32 sends notification via Blynk
- ESP32 triggers Flask server running on PC
- PC webcam captures snapshot and stores it
- Speaker plays a warning voice alert

## ⚡ Features
- Real-time motion detection
- Blynk push notifications
- Automatic webcam snapshot
- Voice deterrent via speaker

## 🛠️ Requirements
- ESP32 board
- PIR sensor (HC-SR501)
- LED + Buzzer (optional)
- PC with Python 3 and webcam
- Arduino IDE with ESP32 core
- Blynk mobile app

## ▶️ Running the Project
1. Flash `esp32_home_surveillance.ino` to ESP32 (update Wi-Fi, Blynk token, and PC IP).
2. On PC:
   ```bash
   pip install flask opencv-python playsound
   python server.py
   ```
3. Trigger PIR sensor → ESP32 sends request → PC saves snapshot + plays alert.

## 📂 Files
- `esp32_home_surveillance.ino` → ESP32 code
- `server.py` → Flask server for webcam + audio
- `README.md` → Project documentation
