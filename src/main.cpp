#include <Arduino.h>
#include "servo-utils.h"
#include "wifi-utils.h"

#define MG996R_PIN 13

void setup() {
  Serial.begin(9600);
  setupWiFiConnection();
  servo::mg996r::getInstance(MG996R_PIN, 0);
}

void loop() {
}
