/* ECEC 490 - Internet of Things - Summer 2014
 * Assignment 1-4
 * Establishes 2 LED blink patterns and allows the user to
 * select the pattern via serial communication
 * James Kurtz and Greg Yeutter */

// for XBee
#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3); // Arduino RX, TX (XBee Dout, Din)

// for NFC
#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);


int led = 13;  // LED Pin 
char input = '0';

unsigned long lastBlink = 0;
int ledState = LOW;

void setup() {
  
  /* initialize on-board stuff */
  pinMode(led, OUTPUT);  // initialize the digital pin as an output.
  XBee.begin(115200);  // start serial port at 9600 bps, 115200 is too high a baud rate, causes garbled text
  
  /* Initialize NFC */
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    XBee.print("Didn't find PN53x board");
    while (1); // halt
  }
  
  XBee.print("Found chip PN5"); XBee.println((versiondata>>24) & 0xFF, HEX); 
  XBee.print("Firmware ver. "); XBee.print((versiondata>>16) & 0xFF, DEC); 
  XBee.print('.'); XBee.println((versiondata>>8) & 0xFF, DEC);
  
  nfc.setPassiveActivationRetries(1);
  nfc.SAMConfig();   // configure board to read RFID tags
  
  XBee.println("Init complete.");
}

/* the blinking function */
void blink(int time) {
  if (lastBlink < millis()-time) {
    if (ledState==LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    lastBlink = millis();
  }
  digitalWrite(led, ledState);
}

void loop() {
  //NFC vars:
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  uint8_t card1[] = { 61, 137, 141, 154};
  uint8_t card2[] = { 180, 96, 190, 85};
  
  if (XBee.available() > 0) {
    input = XBee.read();
    XBee.println(input);
    if (input != '0' && input != '1' && input != '2') {
      XBee.println("Unrecognized Character");
    }
  }
  
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  //success = nfc.waitUntilReady(10);
  
  //DEBUG blinks  XBee.println((String)ledState + "\t" + (String) input + "\t" + (String) millis());
  
  if (success) {
    XBee.println("  Found a card...");
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
      XBee.println("oh look. Greg's card!");
      if (input == '1') {
        input = '2';
      } else {
        input = '1';
      }
    } else if (match2) {
      XBee.println("oh look. James's card!");
      if (input == '1') {
        input = '2';
      } else {
        input = '1';
      }
    } else {
      XBee.println("Access Denied.  No LEDs for you.");
      input = '0';
    }
    
    delay(1000);
    
  }
  
  if (input == '1') {
    blink(100);
  }else if (input == '2') {
    blink(500);
  }
 
}
