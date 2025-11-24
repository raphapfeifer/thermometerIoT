# IoT Temperature & Humidity Monitor  
**ESP8266 + DHT22 + OLED SSD1306 + MQTT**

This project implements an IoT thermometer and hygrometer using an **ESP8266 (NodeMCU)**, a **DHT22 sensor**, an **OLED SSD1306 display**, and the **MQTT** protocol for sending temperature and humidity data to a broker in real time.

---

## 📌 Features
- Real-time temperature and humidity monitoring  
- Local visualization using an **SSD1306 OLED (128×64)**  
- MQTT data publishing using **HiveMQ public broker**  
- Auto-reconnection logic for Wi-Fi and MQTT  
- Non-blocking display cycling for temperature and humidity  
- Simple and clean architecture for IoT learning and expansion  

---

## 🧰 Hardware Components
| Component | Description |
|----------|-------------|
| **ESP8266 NodeMCU** | Wi-Fi enabled microcontroller |
| **DHT22 Sensor** | Temperature and humidity sensor |
| **OLED SSD1306 (I2C, 128×64)** | Display for local data |
| **Breadboard & jumper wires** | Prototyping |

---

## 🛠 Wiring Diagram

### **ESP8266 → DHT22**
| ESP8266 Pin | DHT22 Pin |
|-------------|-----------|
| **3V3** | VCC |
| **GND** | GND |
| **D5 (GPIO14)** | DATA |

> Tip: Use a **10k resistor** between DATA and VCC if your DHT22 module does not have one built-in.

---

### **ESP8266 → OLED SSD1306 (I2C)**
| ESP8266 Pin | Display Pin |
|-------------|-------------|
| **3V3** | VCC |
| **GND** | GND |
| **D2 (GPIO4)** | SDA |
| **D1 (GPIO5)** | SCL |

---

## 📷 Project Setup (Real Photo)

thermometerIoT.jpg

---

## 📡 MQTT Configuration

The device publishes readings to:

| Topic | Payload |
|-------|---------|
| `lab-rpl/temperature` | Temperature in Celsius |
| `lab-rpl/humidity` | Humidity in % |

Broker used:

broker.hivemq.com
Port: 1883


You can monitor messages using tools like:

- HiveMQ WebSocket Client  
- MQTT Explorer  
- Mosquitto CLI  

---

## 🧪 How It Works

1. On boot, the ESP8266 initializes the OLED and attempts to connect to Wi-Fi.  
2. After network setup, it connects to the configured MQTT broker.  
3. Temperature and humidity are read from the DHT22 sensor.  
4. Values are:
   - Displayed on the SSD1306 in alternating screens  
   - Published to the MQTT topics  
5. If Wi-Fi or MQTT drops, automatic reconnection kicks in.

---

## 🖥 OLED Display Behavior

- Displays **Temperature (°C)** in large font  
- Displays **Humidity (%)** in large font  
- Cycle duration: **2 seconds per screen**

The display is refreshed after each reading.

---

## 📦 Required Libraries

Install via `Tools → Manage Libraries` in Arduino IDE:

- **ESP8266WiFi**
- **PubSubClient**
- **DHT sensor library**
- **Adafruit Unified Sensor**
- **Adafruit SSD1306**
- **Adafruit GFX**

---

## 🚀 Uploading the Project

1. Install ESP8266 support in Arduino IDE  
2. Select board:  NodeMCU 1.0 (ESP-12E Module)
3. Select the correct COM port  
4. Upload the sketch  
5. Open Serial Monitor at **115200 baud**

---

## 🌐 Monitoring via MQTT

Subscribe to:

lab-rpl/temperature
lab-rpl/humidity


Use the HiveMQ Web Client:  
https://www.hivemq.com/demos/websocket-client/

---

## 📝 Future Improvements

- Add OTA firmware updates  
- Send JSON payloads  
- Add timestamps  
- Integrate with Home Assistant  
- Build a custom dashboard (Node-RED, Grafana, etc.)

---

## 📄 License
Open-source project — free for personal or educational use.

---




