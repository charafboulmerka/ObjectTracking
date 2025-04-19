# 🎯 ObjectTrackerAndroidESP

An intelligent Android + ESP32-based object tracking system that uses real-time camera  input to keep a selected object perfectly centered on the frame — by dynamically adjusting servo motors on a mounted base.

---

## 👨‍💻 Project Overview

This project was part of my **Bachelor's degree final project** at *Université Frères Mentouri - Constantine 1*. It combines:

- 📱 An **Android app** (Kotlin/Java)
- 📷 **OpenCV** for real-time object coordinate detection
- 🤖 An **ESP32 module** that controls 2 servo motors

---

## 📱 Android App

Built using **Kotlin/Java**, the Android app opens the camera and allows the user to **select an object** by tapping on it. After selection:

- OpenCV tracks the object and **continuously extracts its X/Y coordinates**.
- These coordinates are sent via **Wi-Fi** to an ESP32 module.
- The phone is mounted on a **servo-based base** that can move **horizontally (left/right)** and **vertically (up/down)**.
- Based on the coordinates, the ESP32 moves the servos to **keep the object centered** on the screen — even if the phone itself is moving.

---

## 🔌 ESP32 Module

Included in the project is the ESP32-side code: `ESP32_SIDE.ino`

- Code written in **C++**
- Receives coordinate data over Wi-Fi
- Uses a **PID controller** to process the coordinates and **adjust the servo motors** smoothly and continuously
- Keeps the selected object **centered on the app screen** by controlling the arm/base movement

### 🔧 Setup

1. Flash the `ESP32_SIDE.ino` sketch to your ESP32.
2. The ESP32 shares a Wi-Fi network that the phone connects to.
3. In the Android app, update the **ESP32 IP address** inside the `CameraFragment`, specifically in the `sendESP()` function.

---

## 🧪 How It Works

1. Power on ESP32 – it starts broadcasting Wi-Fi.
2. Open the app and connect to ESP Wi-Fi.
3. Select an object on the screen to track.
4. The app continuously sends object coordinates to ESP32.
5. The ESP32 processes the coordinates using a PID controller and adjusts the servos accordingly.
6. The object stays centered on the phone screen.

---

## 🎮 Features

- Smooth real-time object tracking
- PID-based servo alignment to center object
- Easy setup: just connect to ESP Wi-Fi and go!
- Uses HTTP requests to communicate between Android & ESP

---

## 🛠 Tech Stack

| Component      | Technology              |
|----------------|--------------------------|
| Android App    | Kotlin / Java            |
| Vision         | OpenCV                   |
| Microcontroller| ESP32 (C++ / Arduino)    |
| Communication  | Wi-Fi + HTTP             |
| Hardware       | 2x Servo Motors (X/Y)    |

---

## 📸 Screenshots

*To be added here...*

---

## 🎥 Demo Video

*Will be added here...*

---

## ⚠️ Notes

- Make sure to **update the ESP IP** in `CameraFragment.kt → sendESP()` function.

---

## 👤 Author

**Charaf Boulmerka**  
Android & Web Developer  
📧 charaf.boulmerka25@gmail.com  

---

## 🤝 Contributions

Feel free to **fork** the project, **open issues**, or **send pull requests**.  
If you find this useful, give it a ⭐ on GitHub!

---

## ✨ Enjoy building smart tracking systems!
