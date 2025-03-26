#include "arduino-ha.h"
#include "door.h"
#include "card-utils.h"

#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

#define BROKER_ADDR     IPAddress(127,0,0,1)
#define BROKER_PORT     1883
#define BROKER_USERNAME "username"
#define BROKER_PASSWORD "password"

#define SCAN_INTERVAL   5000

byte mac[6];
WiFiClient client;
HADevice device(mac, sizeof(mac));
HAMqtt mqtt(client, device);

HAButton buttonA("DoorOpen");
HATagScanner scanner("DoorScanner");
unsigned long lastTagScannedAt = 0;

void scanInHA() {
    MFRC522 &rfid = cardUtils::getRFID();
    
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
      return;
    }
  
    if (millis() - lastTagScannedAt < SCAN_INTERVAL) {
      return; // Prevents spamming HA
    }
  
    // Convert tag UID to string
    char tag[rfid.uid.size*2+1] = {0};
    HAUtils::byteArrayToStr(tag, rfid.uid.uidByte, rfid.uid.size);
  
    Serial.print("Card scanned: ");
    Serial.println(tag);
  
    scanner.tagScanned(tag); // Send to Home Assistant
    lastTagScannedAt = millis();
}

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

    scanner.setName("Door RFID Scanner");

    connectMqtt();
}

void HA::loop() {
    // Check if MQTT is connected and reconnect if needed
    if (!mqtt.isConnected()) {
        Serial.println("MQTT connection lost. Reconnecting...");
        connectMqtt();
    }
    scanInHA();
    mqtt.loop();
}