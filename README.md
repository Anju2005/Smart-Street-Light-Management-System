# Smart Street Light System using ESP8266 and IR Sensors

This project demonstrates a Smart Street Lighting System using ESP8266 (NodeMCU), IR Sensors, and LEDs. It combines automatic street light control based on motion detection with manual web-based control using WiFi.

#  Features

-  Motion-based automatic street light activation using IR sensors
-  Manual ON/OFF control for each street light via a WiFi web interface
-  Real-time LED status updates on the web page
-  Works on your local WiFi network

#  How It Works

- Each IR sensor detects motion.
- If motion is detected, the corresponding LED (streetlight) turns ON automatically.
- You can override automatic behavior via a web interface to manually turn ON/OFF each LED.
- When manually turned OFF, the LED ignores IR input.

# Components Used

| Component         | Quantity |
| ESP8266 (NodeMCU) | 1        |
| IR Sensor         | 3        |
| LED               | 3        |
| Jumper Wires      | Several  |
| Breadboard        | 1        |
| Resistors (220Ω)  | 3        |
| USB Cable         | 1        |

# Circuit Diagram

| Device       | ESP8266 Pin |
| IR Sensor 1  | D5 (GPIO14) |
| IR Sensor 2  | D6 (GPIO12) |
| IR Sensor 3  | D7 (GPIO13) |
| LED 1        | D1 (GPIO5)  |
| LED 2        | D2 (GPIO4)  |
| LED 3        | D3 (GPIO0)  |

> IR sensors are active LOW: they output `LOW` when motion is detected.

# Web Interface

Once ESP8266 connects to WiFi, it hosts a webpage where you can:

- View the status of each street light (ON/OFF)
- Manually turn each LED ON or OFF

The interface updates automatically and redirects back to the home page after every action.

# How to Use

1. Connect the components as described above.
2. Flash the provided Arduino code to your ESP8266.
3. Replace the following in the code with your WiFi credentials:
   ```cpp
   const char* ssid = "YourWiFiSSID";
   const char* password = "YourWiFiPassword";
