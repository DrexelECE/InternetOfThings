/* ECEC 490 - Internet of Things - Summer 2014
Assignment 1-3
Establishes 2 LED blink patterns and allows the user to
select the pattern via serial communication over 802.15.4
James Kurtz and Greg Yeutter */

int led = 13;  // LED Pin 
char input = '0';
char lightSetting = input;

void setup() {
  pinMode(led, OUTPUT);  // initialize the digital pin as an output.
  Serial.begin(9600);  // 115200 causes garbled text, switch to 9600
  delay(100);
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
    if (input == '0' || input == '1' || input == '2') {
      Serial.println(input);
      lightSetting = input;
    }
    // error checking is currently off
    /*
    else if (input != '0' && input != '1' && input != '2') {
      Serial.println("Unrecognized Character");
    }
    */
  }
  if (lightSetting == '1') {
    blink1();
  }
  else if (lightSetting == '2') {
    blink2();
  }
 
}
