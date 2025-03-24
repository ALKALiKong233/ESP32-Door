#include <Arduino.h>
#include "servo-utils.h"
#include "wifi-utils.h"
#include "door.h"

#define MG996R_PIN 13
#define BUTTON 2

volatile bool shouldOpen = false;

void button_trigger() {
  shouldOpen = true;
}

void setup() {
  Serial.begin(9600);
  setupWiFiConnection();
  servo::mg996r::getInstance(MG996R_PIN, 0);
  pinMode(BUTTON, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BUTTON), button_trigger, FALLING);
}

void loop() {
  if ( shouldOpen ) {
    door::open();
    delay(1000);
    door::close();
    shouldOpen = false;
  }
}
