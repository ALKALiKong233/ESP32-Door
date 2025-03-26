#ifndef CARD_UTILS_H
#define CARD_UTILS_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5   // ESP32 pin GPIO5 
#define RST_PIN 22  // ESP32 pin GPIO22

namespace cardUtils {
    void setup();
    void loop();
    MFRC522& getRFID();
    MFRC522::MIFARE_Key& getKey();
}
#endif // CARD_UTILS_H