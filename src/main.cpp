#include <Arduino.h>
#include "servo-utils.h"
#include "wifi-utils.h"

#define MG996R_PIN 13

servo::mg996r mg996r(MG996R_PIN, 0);

void setup() {
  Serial.begin(9600);
  setupWiFiConnection();
}

void loop() {
}
