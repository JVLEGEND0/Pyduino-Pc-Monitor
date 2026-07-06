# 📊 Pyduino PC Monitor

A tiny Arduino-powered desktop system monitor for Windows.

Pyduino PC Monitor is an open-source Python + Arduino project that turns a 16x2 I2C LCD into a real-time hardware monitor. It communicates over Serial and displays live system information, Spotify playback, alerts, and more.

![GitHub release](https://img.shields.io/github/v/release/JVLEGEND0/Pyduino-Pc-Monitor)
![Python](https://img.shields.io/badge/Python-3.11+-blue)
![Arduino](https://img.shields.io/badge/Arduino-Uno-success)
![License](https://img.shields.io/github/license/JVLEGEND0/Pyduino-Pc-Monitor)

---

## ✨ Features

- 🖥️ CPU usage
- 🌡️ CPU temperature
- 💾 RAM usage
- 📀 Disk usage
- 🎵 Spotify integration
- 🕒 Clock and date
- 👋 Gesture-based screen navigation (HC-SR04)
- 🚨 LED temperature warning
- 🔌 Idle screen when the PC disconnects
- ⚡ Real-time Serial communication
- 📜 Automatic scrolling for long song titles

---

## 📷 Preview

<p align="center">
  <img src="images/idle_pyduino.jpg" width="45%">
  <img src="images/cpu_pyduino.jpg" width="45%">
</p>

<p align="center">
  <img src="images/ram_pyduino.jpg" width="45%">
  <img src="images/disk_pyduino.jpg" width="45%">
</p>

<p align="center">
  <img src="images/spotify_pyduino.jpg" width="45%">
</p>

---

## 🔧 Hardware

- Arduino Uno (or compatible)
- 16x2 I2C LCD
- HC-SR04 ultrasonic sensor *(optional, for gesture control)*
- LED
- 220Ω resistor
- Jumper wires
- USB cable

---

## 🔌 Wiring

### LCD

| LCD | Arduino |
|------|----------|
| GND | GND |
| VCC | 5V |
| SDA | SDA (A4) |
| SCL | SCL (A5) |

### LED

| LED | Arduino |
|------|----------|
| Anode | D8 |
| Cathode | GND (220Ω resistor) |

### HC-SR04 *(optional)*

| HC-SR04 | Arduino |
|----------|----------|
| VCC | 5V |
| GND | GND |
| TRIG | D9 |
| ECHO | D10 |

A complete wiring diagram is available below:

![Pyduino Wiring](images/Pyduino.png)

---

## 📦 Installation

Clone the repository:

```bash
git clone https://github.com/JVLEGEND0/Pyduino-Pc-Monitor.git
```

Install the dependencies:

```bash
pip install -r requirements.txt
```

Upload the Arduino sketch.

Open `Pyduino_app.py` and configure:

- COM port
- Spotify credentials (optional)

---

## 🎵 Spotify Setup

1. Open the Spotify Developer Dashboard.
2. Create a new application.
3. Copy your Client ID and Client Secret.
4. Paste them into:

```python
CLIENT_ID = ""
CLIENT_SECRET = ""
REDIRECT_URI = ""
```

Run the application once and authorize your Spotify account.

---

## 🌡️ CPU Temperature

Pyduino uses **Libre Hardware Monitor** to read the CPU temperature.

### Installation

1. Download Libre Hardware Monitor.
2. Extract it anywhere.
3. Run `LibreHardwareMonitor.exe`.
4. Enable **Options → Remote Web Server**.
5. Keep Libre Hardware Monitor running while using Pyduino.

> **Note**
>
> CPU temperature will be unavailable if Libre Hardware Monitor is not running or the Remote Web Server is disabled.

Latest release:

https://github.com/LibreHardwareMonitor/LibreHardwareMonitor/releases

---

## 👋 Gesture Control

When an HC-SR04 ultrasonic sensor is connected, Pyduino can be controlled without any buttons.

Current controls:

- 👋 Pass your hand in front of the sensor to switch screens.

More gestures are planned for future releases.

---

## 🚀 Roadmap

- ESP32 support (Wi-Fi)
- Custom screens
- OLED display support
- More sensors
- Better animations
- Config file
- Plugin system
- Linux support

---

## 🤝 Contributing

Contributions, bug reports and suggestions are always welcome.

Feel free to open an Issue or submit a Pull Request.

---

Made with ❤️ using Python and Arduino.

⭐ If you like this project, consider giving it a star!
