# Arduino LED Control IoT Project

Welcome to the Arduino LED Control IoT project! This repository contains everything you need to control LEDs using Arduino and NodeMCU ESP8266, allowing you to create stunning visual effects that respond to music or commands from your iOS device.

![Project Demo](demo.gif)

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Hardware Requirements](#hardware-requirements)
  - [Software Requirements](#software-requirements)
  - [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This project was initially developed as part of a university assignment, aiming to explore the integration of Arduino with IoT technologies. Now, it's being shared with the open-source community to inspire and educate enthusiasts in the field of embedded systems and IoT.

## Features

- Control LEDs based on Fast Fourier Transform (FFT) values, creating mesmerizing visual effects synced with music.
- Communicate with an iOS application using Blynk.io, enabling remote control and automation of LED patterns.
- Easily adaptable codebase for experimentation and customization.

## Getting Started

### Hardware Requirements

To replicate this project, you'll need the following hardware components:

- Arduino UNO board
- NodeMCU ESP8266 (WiFi module)
- LEDs (RGB or single-color)
- Jumper wires
- Breadboard

### Software Requirements

Ensure you have the following software installed on your development environment:

- Arduino IDE
- Blynk mobile app (available on [App Store](https://apps.apple.com/us/app/blynk-iot-for-arduino-esp32/id808760481))

### Installation

1. Clone this repository to your local machine.
   ```
   git clone https://github.com/your_username/arduino-led-control-iot.git
   ```

2. Open the Arduino UNO file (`arduino_led_control.ino`) in the Arduino IDE and upload it to your Arduino board.

3. Open the ESP8266 WiFi file (`esp8266_wifi_control.ino`) in the Arduino IDE and upload it to your NodeMCU ESP8266 board.

4. Install the Blynk app on your iOS device and create a new project.

5. Configure the Blynk app to communicate with your NodeMCU ESP8266 using the provided authentication token.

6. Enjoy controlling your LEDs remotely through the Blynk app or watch them dance to the rhythm of your music!

## Usage

Once everything is set up, you can interact with the LEDs in multiple ways:

- Use the Blynk app to send commands and control LED patterns remotely.
- Play music through the Arduino and watch the LEDs react in real-time to the audio spectrum.
- Experiment with different LED configurations and code modifications to create your own unique effects.

## Contributing

Contributions are welcome! If you have ideas for improvements or new features, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Please share and enjoy this project!** If you find it helpful or inspiring, don't hesitate to spread the word and contribute to the community of Arduino and IoT enthusiasts. Together, we can make technology more accessible and fun for everyone. 🚀
