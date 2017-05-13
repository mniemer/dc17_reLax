
const int laserPin = 14;
int laserState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 5;           // interval at which to blink (milliseconds)

void setup() {
  // put your setup code here, to run once:
  pinMode(laserPin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (laserState == LOW)
      laserState = HIGH;
    else
      laserState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(laserPin, laserState);
  }
}
