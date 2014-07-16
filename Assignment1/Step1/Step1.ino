/* ECEC 490 - Internet of Things - Summer 2014
Assignment 1-1
Establishes 2 LED blink patterns and allows the user to
select the pattern via serial communication
James Kurtz and Greg Yeutter */

int led = 13;  // LED Pin 
char input = '0';
char ledSetting = '0';

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

void getSerialInput() {
  if (Serial.available() > 0) {
    input = Serial.read();
    Serial.println(input);
    checkInput();
  }
}

void checkInput() {
  if (input == '1') {
    ledSetting = '1';
  } else if (input == '2') {
    ledSetting = '2';
  } else if (input == '0') {
    ledSetting = '0';
  } 
}

void runBlinkSequence() {
  if (ledSetting == '1') {
    blink1();
  } else if (ledSetting == '2') {
    blink2();
  } else if (ledSetting == '0') {
    digitalWrite(led, LOW);
    delay(500);
  }
}

void loop() {
  getSerialInput();
  runBlinkSequence();
}
