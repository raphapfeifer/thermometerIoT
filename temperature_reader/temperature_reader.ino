//--WIFI--
#include <ESP8266WiFi.h>
const char* ssid = "";
const char* password = "";
WiFiClient nodeMcuClient;

//--MQTT---
#include <PubSubClient.h>
const char* mqtt_broker = "broker.hivemq.com";
const char* mqtt_clientId = "thermometerIOT";
PubSubClient client(nodeMcuClient);
const char* temperatureTopic = "lab-rpl/temperature";
const char* humidityTopic = "lab-rpl/humidity";


//--DHT--
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN D5
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);
float humidity;
float temperature;

//--DISPLAY--
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//--SETUP--
void setup() {
  Serial.begin(115200);
  dht.begin();
  displayConfig();
  wifiConnect();
  client.setServer(mqtt_broker, 1883);
}

//--LOOP--
void loop() {
    if(!client.connected()){
      mqttReconnect();
    }
    measureTemperatureHumidity();
    publishTemperatureHumidity();
    showTemperatureHumidity();
  }

//--FUNÇÕES AUXILIARES
void wifiConnect(){
  delay(10);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Connecting");
  display.display();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    display.print(".");
    display.display();
  }
}

void mqttReconnect(){
  while(!client.connected()){
    client.connect(mqtt_clientId);
  }
}


void displayConfig(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();
}

void publishTemperatureHumidity(){
  client.publish(temperatureTopic, String(temperature).c_str(), true);
  client.publish(humidityTopic, String(humidity).c_str(), true);
}


void measureTemperatureHumidity() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature(false);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temperature);
}

void showTemperatureHumidity(){
  showMessageOnDisplay("Temperature", (temperature), " C");
  showMessageOnDisplay("Humidity", (humidity), " %");
}

void showMessageOnDisplay(const char* text1, int measure, const char* text2){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print(text1);
  display.setTextSize(5);
  display.setCursor(20,20);
  display.print(measure);
  display.setTextSize(2);
  display.print(text2);
  display.display();
  delay(2000);
}
