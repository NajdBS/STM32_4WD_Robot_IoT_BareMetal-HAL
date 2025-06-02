## 📚 Overview
This project reimplements the 4WD Robot system using STM32 HAL, focusing on modular sensor acquisition and cloud integration. Sensor data is collected using ADC in DMA mode for efficient analog signal sampling, and temperature data is read via I2C from the DS1621 digital temperature sensor. Wi-Fi communication is handled by an ESP8266 module to upload sensor data to the cloud (ThingSpeak) and enable remote monitoring through a web interface. This version is a continuation of a previous full bare-metal implementation that included BLE-based robot control.
- **Microcontroller Board:** STM32F407VG Discovery  
- **Development Approach:** Hybrid  
  - **Bare-Metal Version:** Complete implementation (BLE control, cloud and local web server communication)  
  - **HAL Version:** Focused on cloud communication and monitoring interface (BLE control not included)
- **Features:**
  - Motor control via PWM
  - Sensor data acquisition
  - Wi-Fi communication with ESP8266
  - Cloud data upload (ThingSpeak)
  - Web-based monitoring interface

## 📦 Project Structure
- `src/` – Source code  
- `inc/` – Header files  
- `images/` – Diagrams and architecture images  

## 📌 Notes
- The original **bare-metal version** includes full robot control (including BLE commands such as forward, backward, etc.), and supports both cloud and local web server communication.  
- The **HAL version** reuses parts of the original structure, focusing on cloud upload and monitoring, but **does not include** BLE-based robot command control.
