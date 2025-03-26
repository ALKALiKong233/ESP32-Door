#include <Arduino.h>
#include <WebServer.h>

#include "servo-utils.h"
#include "wifi-utils.h"
#include "door.h"
#include "arduino-ha.h"
#include "card-utils.h"

#define MG996R_PIN 13
#define BUTTON 2

#define WEB_SERVER_PORT 80

volatile bool shouldOpen = false;

void button_trigger() {
  shouldOpen = true;
}

void web_trigger() {
  shouldOpen = true;
}

WebServer server(WEB_SERVER_PORT);

void setup() {
  Serial.begin(9600);
  setupWiFiConnection();
  servo::mg996r::getInstance(MG996R_PIN, 0);
  pinMode(BUTTON, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BUTTON), button_trigger, FALLING);
  server.on("/open", web_trigger);
  server.begin();
  Serial.println("HTTP server started");
  cardUtils::setup();
  HA::setup();
}

void loop() {
  server.handleClient();
  if ( shouldOpen ) {
    door::open();
    delay(5000);
    door::close();
    shouldOpen = false;
  }
  HA::loop();
  cardUtils::loop();
}
