#include "arduino-ha.h"
#include "door.h"
#include <Arduino.h>
#include <WiFi.h>

#define BROKER_ADDR     IPAddress(127,0,0,1)
#define BROKER_PORT     1883
#define BROKER_USERNAME "username"
#define BROKER_PASSWORD "password"

byte mac[6];
WiFiClient client;
HADevice device(mac, sizeof(mac));
HAMqtt mqtt(client, device);

HAButton buttonA("DoorOpen");

void onButtonCommand(HAButton* sender)
{
    if (sender == &buttonA) {
        door::open();
        delay(5000);
        door::close();
    }
}

void connectMqtt() {
    Serial.println("Connecting to MQTT broker...");
    
    bool result = mqtt.begin(BROKER_ADDR, BROKER_USERNAME, BROKER_PASSWORD);
    
    if (result) {
        Serial.println("Connected to MQTT broker!");
    } else {
        Serial.println("Failed to connect to MQTT broker. Will retry...");
    }
}

void HA::setup() {
    WiFi.macAddress(mac);

    device.setName("homeassistant-ESP32-Door");
    device.setSoftwareVersion("1.0.0");

    buttonA.setIcon("mdi:door-open");
    buttonA.setName("开门");

    buttonA.onCommand(onButtonCommand);

    connectMqtt();
}

void HA::loop() {
    // Check if MQTT is connected and reconnect if needed
    if (!mqtt.isConnected()) {
        Serial.println("MQTT connection lost. Reconnecting...");
        connectMqtt();
    }
    mqtt.loop();
}