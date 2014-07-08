#include <Adafruit_NFCShield_I2C.h>



/* ECEC 490 - Internet of Things - Summer 2014
Assignment 1-1
Establishes 2 LED blink patterns and allows the user to
select the pattern via serial communication
James Kurtz and Greg Yeutter */

int led = 13;  // LED Pin 
char input = '0';

void setup() {
  pinMode(led, OUTPUT);  // initialize the digital pin as an output.
  Serial.begin(9600);  // start serial port at 9600 bps:
  Serial.println("Enter the blink sequence number, 1 or 2. To turn off, enter 0.");
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
  if (Serial.available() > 0) {
    input = Serial.read();
    Serial.println(input);
    if (input != '0' && input != '1' && input != '2') {
      Serial.println("Unrecognized Character");
    }
  }
  else if (input == '1') {
    blink1();
  }
  else if (input == '2') {
    blink2();
  }
 
}
