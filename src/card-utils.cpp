#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#include "card-utils.h"

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte nuidPICC[4];

void cardUtils::setup() {
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522 

  Serial.println("RFID Reader initialized. Scan a card:");
  
  // Prepare the key (used both for authentication and encryption)
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void cardUtils::loop() {
  // Check for new cards
  if (!rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been read
  if (!rfid.PICC_ReadCardSerial())
    return;

  Serial.print("RFID Tag UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  Serial.println();

  // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
  
  delay(100); // Small delay to prevent multiple reads
}
