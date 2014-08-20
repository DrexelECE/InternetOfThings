int magnetPin = 2; // Interrupt on pin 2? (interrupt 0?) Check board docs
unsigned long timeElapsed = 0;
unsigned long lastMicros = 0;
volatile int magnetPasses = 0;

void setup() {
  attachInterrupt(0,magnetTick,RISING); // RISING assumes NO sensor, change to FALLING for NC
}

void magnetTick() {
  magnetPasses++;
}

void loop() {
  if (magnetPasses >= 10) {
    transmit();
    timeElapsed = 0;
  }   
}

void transmit() {
  unsigned long currentMicros = micros() - lastMicros;
  lastMicros = micros();
  // TODO transmit code here
  
  
}
