/* ECEC 490 - Internet of Things - Summer 2014
 * Assignment 1-1
 * Establishes 2 LED blink patterns and allows the user to
 * select the pattern via serial communication
 * James Kurtz and Greg Yeutter */


// for NFC
#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);


int lastBlink

int led = 13;  // LED Pin 
char input = '0';

void setup() {
  
  /* initialize on-board stuff */
  pinMode(led, OUTPUT);  // initialize the digital pin as an output.
  Serial.begin(115200);  // start serial port 
  
  
  /* Initialize NFC */
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  nfc.setPassiveActivationRetries(1);
  nfc.SAMConfig();   // configure board to read RFID tags
  
  Serial.println("Init complete.");
}

void blink1() {
  digitalWrite(led, HIGH);
  delay(800);
  digitalWrite(led, LOW);
  delay(400);
}

void blink2() {
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);
}

void loop() {
  //NFC vars:
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  if (Serial.available() > 0) {
    input = Serial.read();
    Serial.println(input);
    if (input != '0' && input != '1' && input != '2') {
      Serial.println("Unrecognized Character");
    }
  }
  
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  //success = nfc.waitUntilReady(10);
  
  if (success) {
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");
    
    wait(100);
    
    
    if (input=='1') {
      input = '2';
    } else {
      input = '1';
    }
  }
  
  if (input == '1') {
    blink1();
  }
  else if (input == '2') {
    blink2();
  }
 
}
