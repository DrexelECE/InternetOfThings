/* ECEC 490 - Internet of Things - Summer 2014
Assignment 1-4
Authenticates user via NFC. If access granted, user can select
options via serial communication
James Kurtz and Greg Yeutter */

// for NFC:
#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

int led = 13;  // LED Pin 
char input = '0';
char doorState = 0; // 0: locked, 1: unlocked

void setup() {
  // Initialize pins and serial port
  pinMode(led, OUTPUT);  // initialize the digital pin as an output.
  Serial.begin(9600);  // start serial port
  
  // Initialize NFC  
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

void lockBlink() {
  digitalWrite(led, HIGH);
  delay(800);
  digitalWrite(led, LOW);
  delay(400);
    digitalWrite(led, HIGH);
  delay(800);
  digitalWrite(led, LOW);
}

void unlockBlink() {
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
}

void changeLockState() {
  if (doorState == '1') {
    Serial.print(" The door is unlocked. Lock it? 1 for Yes, 0 for No");
    input = Serial.read();
    if (input == '1') {
      doorState = '0';
      Serial.println("Door locked. Goodbye.");
      lockBlink();
    } else {
      Serial.println("Door remaining unlocked. Goodbye.");
      unlockBlink();
  } else {
    Serial.print(" The door is locked. Unlock it? 1 for Yes, 0 for No");
    if (input == '1') {
      doorState = '0';
      Serial.println("Door unlocked. Goodbye.");
      unlockBlink();
    } else {
      Serial.println("Door remaining locked. Goodbye.");
      lockBlink();
  }
}

void checkLockState() {
  if (doorState == '1') {
    Serial.print(" The door is unlocked. Goodbye.");
    unlockBlink();
  } else {
    Serial.print(" The door is locked. Goodbye.");
    lockBlink();
  }
}

void loop() {
  // Check for authorized users
  Serial.println("Waiting for card...");
  
  //NFC vars:
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  uint8_t card1[] = { 61, 137, 141, 154};
  uint8_t card2[] = { 180, 96, 190, 85};
  
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
  
  //DEBUG blinks  Serial.println((String)ledState + "\t" + (String) input + "\t" + (String) millis());
  
  if (success) {
    Serial.println("  Found a card...");
    //Serial.println("Found an ISO14443A card");
    //Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    //Serial.println("  UID Value: ");
    //nfc.PrintHex(uid, uidLength);
    
    boolean match1 = true;
    boolean match2 = false;
    
    if (uidLength != sizeof(card1)) {
      match1 = false;
    } else {
      for (int i=0; i<uidLength; i++) {
        if (uid[i] != card1[i]) {
        //  Serial.println(uid[i]);
          match1 = false;
          break;
        }
      }
    }
    
    
    if (!match1) {
      match2 = true;
      if (uidLength != sizeof(card2)) {
        match2 = false;
      } else {
        for (int i=0; i<uidLength; i++) {
          if (uid[i] != card2[i]) {
            match2 = false;
            break;
          }
        }
      }
    }
    
    if (match1) {
      Serial.println("Hello Greg.");
      changeLockState();
    } else if (match2) {
      Serial.println("Hello James.");
      changeLockState();
    } else {
      Serial.println("Access Denied.");
      checkLockState();
    }
    
    delay(1000);
    
  }
  
  /*
  if (input == '1') {
    blink(100);
  }else if (input == '2') {
    blink(500);
  }
  */
 
  /*
  if (Serial.available() > 0) {
    input = Serial.read();
    if (input == '0' || input == '1' || input == '2') {
      Serial.println(input);
      lightSetting = input;
    }
    */
    /*
    else if (input != '0' && input != '1' && input != '2') {
      Serial.println("Unrecognized Character");
    }
    */
  /*  
  }
  if (lightSetting == '1') {
    blink1();
  }
  else if (lightSetting == '2') {
    blink2();
  }
  */
 
}
