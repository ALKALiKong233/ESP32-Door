#include "card-utils.h"

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte nuidPICC[4];

namespace cardUtils {
  unsigned long lastRFIDCheckTime = 0;
}
#define RFID_CHECK_INTERVAL 30000

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
  // Check RFID connection periodly
  if (millis() - lastRFIDCheckTime > RFID_CHECK_INTERVAL) {
    if (!cardUtils::checkRFIDConnection()) {
        cardUtils::resetRFID();
    }
    lastRFIDCheckTime = millis();
  }

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

bool cardUtils::checkRFIDConnection() {
  byte status = rfid.PCD_ReadRegister(MFRC522::Status1Reg);

  // The status would be 0x00 if disconnected.
  if ( (status == 0x00) ) {
    Serial.println("RFID reader connection failed or not responding");
    return false;
  }
  
  return true;
}

void cardUtils::resetRFID() {
  Serial.println("Resetting RFID reader...");
  // Hard reset RFID
  digitalWrite(RST_PIN, LOW);
  delay(3000);
  digitalWrite(RST_PIN, HIGH);
  delay(3000);
  
  // Re-init
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RFID reader reset completed");
}

MFRC522& cardUtils::getRFID() {
    return rfid;
}

MFRC522::MIFARE_Key& cardUtils::getKey() {
    return key;
}
