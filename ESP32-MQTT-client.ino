#include "defines.h"

#ifdef ESP_32
#include <WiFi.h>
#include <esp_wifi.h>
#endif

#ifdef ESP_8266
#include <ESP8266WiFi.h>
#endif

#include <MQTTClient.h>
#include <ArduinoJson.h>

#include "LED.h"

#ifdef PRODUCER
#include "RotaryEncoder.h"
#include "Potentiometer.h"
#include "Display.h"

String modtype = "producer/";

#ifdef ROTARY_ENCODER
RotaryEncoder reader;
#endif
#ifdef POTENTIOMETER
Potentiometer reader;
#endif

Display screen;
double power = 0;

void send_reading(int value) {
  JsonDocument message;
  message["value"] = value;
  send_to_MQTT("esp/update", message);
}
#endif

#ifdef CONSUMER
String modtype = "consumer/";
#endif

const char WIFI_SSID[] = "DancingCow";
const char WIFI_PASSWORD[] = "perfectwe1";

const int MQTT_PORT = 1883;

const char MQTT_USERNAME[] = "hello";
const char MQTT_PASSWORD[] = "hello";

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);
IPAddress ip;
IPAddress broker_ip;

String MAC_ADDRESS;
LED led_control;

void wifi_connect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("ESP - Connecting to Wi-Fi Network: %s\n", WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.printf("Connected to WiFi Network: %s\n", WIFI_SSID);
  Serial.print("IP Address: ");
  ip = WiFi.localIP();
  Serial.println(ip);
  broker_ip = WiFi.localIP();
  broker_ip[3] = 183;
  Serial.print("Broker IP: ");
  Serial.println(broker_ip);
}

void setup() {
  Serial.begin(115200);

  wifi_connect();

#ifdef PRODUCER
  reader.setup_pins();
  screen.setup();
#endif

  led_control.setup_pins();

  MAC_ADDRESS = read_MAC_address();
  connect_to_MQTT();
  send_type();
}

void loop() {
  mqtt.loop();
#ifdef PRODUCER
  static int64_t lastupdate = millis();
#ifdef ROTARY_ENCODER
  reader.check_and_send();
#endif
  if (millis() - lastupdate > UPDATE_INTERVAL) {
#ifdef POTENTIOMETER
    reader.check_and_send();
#endif
    screen.draw(reader.percentage, power);
    led_control.rotate_color(reader.percentage);
    lastupdate = millis();
  }
#endif
}

void connect_to_MQTT() {
  mqtt.begin(broker_ip.toString().c_str(), MQTT_PORT, network);
  mqtt.onMessage(message_handler);

  Serial.printf("ESP - Connecting to MQTT broker at %s (port %d)\n",
                broker_ip.toString().c_str(), MQTT_PORT);

  while (!mqtt.connect(MAC_ADDRESS.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("");

  if (!mqtt.connected()) {
    Serial.println("ESP " + MAC_ADDRESS + " - MQTT broker Timeout.");
    return;
  }

  if (mqtt.subscribe(modtype + MAC_ADDRESS))
    Serial.print("Subscribed to the topic: ");
  else
    Serial.print("Failed to subscribe to the topic: ");
  Serial.println(modtype + MAC_ADDRESS);

  Serial.println("ESP - MQTT broker Connected.");
}

void message_handler(String &topic, String &payload) {
  JsonDocument input;
  deserializeJson(input, payload);
  if (VERBOSE) {
    Serial.println("ESP " + MAC_ADDRESS + " - recieved control message:");
    Serial.println(payload);
  }
#ifdef PRODUCER
  if (topic == (modtype + MAC_ADDRESS))
    power = double(input["power"]);
#endif
#ifdef CONSUMER
  if (topic == (modtype + MAC_ADDRESS)) {
    int time = float(input["time"]) * 2;
    bool status = input["status"];
    led_control.rotate_color(time, status);
  }
#endif
}

void send_to_MQTT(String topic, JsonDocument data) {
  data["MAC"] = MAC_ADDRESS;
  char dataBuffer[128];
  serializeJson(data, dataBuffer);

  mqtt.publish(topic.c_str(), dataBuffer);

  if (VERBOSE) {
    Serial.println("ESP - sent to MQTT:");
    Serial.printf("- topic: %s\n", topic.c_str());
    Serial.printf("- payload: %s\n", dataBuffer);
  }
}

void send_type() {
  JsonDocument message;
  message["module_type"] = MODULE_TYPE;
  message["region_id"] = REGION;
  send_to_MQTT("esp/connect", message);
}

String read_MAC_address() {
#ifdef ESP_8266
  return WiFi.macAddress();
#endif
#ifdef ESP_32
  char tmp[18];
  uint8_t baseMac[6];
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
  if (ret == ESP_OK) {
    snprintf(tmp, sizeof(tmp),
             "%02X:%02X:%02X:%02X:%02X:%02X",
             baseMac[0], baseMac[1], baseMac[2],
             baseMac[3], baseMac[4], baseMac[5]);
    Serial.println(MAC_ADDRESS);
  } else {
    Serial.println("Failed to read MAC address");
  }
  return String(tmp);
#endif
}
