# MotionPlatform

## Description
  
  Object tracking system with Raspberry Pi based vision processing (for object recognition) and ESP32 based pan and tilt camera mount.
  The ultimate goal is to design a system that can identify a 'target' (specific person or object) and track it within the systems range of mobility. This project is an attempt to incorperate various hardware and software technologies into a single system that has practical applications.

## Dependencies
  
### ESP32

- [AsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [WifiManager](https://github.com/tzapu/WiFiManager)
- [ESP32Servo](https://github.com/madhephaestus/ESP32Servo)
- [SPIFFS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/spiffs.html)

### Stats

- ESP32 Pinout:
  - X Servo: 32
  - Y Servo: 33
  - Onboard LED: 2 (used for status indication)

### Notes

  ESP32 webGUI may not be necessary once serial based control is established. A web interface hosted on the primary vision processing unit may be preferred due to easier integration with the camera system and greater processing power.

### Roadmap

  Currently working on creating a stable ESP32 codebase for controlling servos via webGUI and serial.
  Once this is complete, proceed to scripting of external control (via Python & Serial).
  After reliable programmatic external control is established, implement vision processing system to identify and track targets.

#### Software

- Complete:  
  - X & Y Servo control methods via human readable commands
  - Basic web interface for jogging and homing servos  
  ![webGUI](/Docs/webGUI.png)
  - WifiManager for wifi configuration
  - SPIFFS onboard file system
  - Three part web interface framework (HTML, JavaScript, CSS)
  - Individual header files for handling webGUI and servo objects
  - Servo object for storing unique settings (min, max, delay, home, etc.) per servo

- To-Do:
  - Beautify web interface
  - Expand SerialIO for RPi communication
  - Begin Python script for control from external device (to be integrated with upcoming vision processing system)

#### Hardware

- Complete:
- To-Do:
  - Determine best servos based on size, weight and power consumption
  - Begin PTZ mount design
  - Consider additional hardware features such as zoom/focus control servo, switchable IR & visible illumination, and status indicators.

#### Documentation

- Complete:

- To-Do:
