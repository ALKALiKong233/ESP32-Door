#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H
#include <WiFi.h>
#include <WiFiManager.h>
#include <Preferences.h>
void setupWiFiConnection() {
    // WiFiManager, Local intialization
    WiFiManager wm;

    // Set custom AP name
    wm.setAPCallback([](WiFiManager *wm) {
        Serial.println("WiFi connection failed. Starting configuration portal.");
    });
  
    // If WiFiManager fails to connect, it will start an access point named "ESP32-Door-Setup"
    // with password "password"
    if (!wm.autoConnect("ESP32-Door-Setup", "password")) {
        Serial.println("Failed to connect and hit timeout");
        delay(3000);
        ESP.restart();
    }
    
    Serial.println("Connected to WiFi");
    Serial.print("WiFi SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
#endif