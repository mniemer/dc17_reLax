// laser sensor functions defined here
int laserState;
unsigned long previousMillis;
unsigned long interval_;
int laserThreshold;

void laser_sensor_setup() {
  pinMode(L_OUT, OUTPUT);
  pinMode(L_IN1, INPUT);
  pinMode(L_IN2, INPUT);
  pinMode(L_IN3, INPUT);
  pinMode(L_IN4, INPUT);
  previousMillis = 0;
  interval_ = 5;
  laserThreshold = 50;
  laserState = LOW;
  digitalWrite(L_OUT, laserState);
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

boolean check_laser_sensor(int pin) {
  return analogRead(pin) > laserThreshold;
}
