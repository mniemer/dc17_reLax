// laser sensor functions defined here
int laserState;
long previousMillis;
long interval_;

void laser_sensor_setup() {
  pinMode(L_OUT, OUTPUT);
  previousMillis = 0;
  laserState = LOW;
  interval_ = 1000000;
}

void run_laser() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval_) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (laserState == LOW)
      laserState = HIGH;
    else
      laserState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(L_OUT, laserState);
  }
}

