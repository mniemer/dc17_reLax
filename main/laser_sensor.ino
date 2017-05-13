// laser sensor functions defined here
int laserState;
unsigned long prevMillis;
unsigned long interval_;
int laserThreshold;

void laser_sensor_setup() {
  pinMode(L_OUT, OUTPUT);
  pinMode(L_IN1, INPUT);
  pinMode(L_IN2, INPUT);
  pinMode(L_IN3, INPUT);
  pinMode(L_IN4, INPUT);
  prevMillis = 0;
  interval_ = 5;
  laserThreshold = 20;
  laserState = LOW;
  digitalWrite(L_OUT, laserState);
}

// this will run all the time
void run_laser() {
  //analogWriteFrequency(L_OUT, 10);
  
  unsigned long currMillis = millis();
 
  if(currMillis - prevMillis > interval_) {
    // save the last time you blinked the LED 
    prevMillis = currMillis;   

    // if the LED is off turn it on and vice-versa:
    if (laserState == LOW)
      laserState = HIGH;
    else
      laserState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(L_OUT, laserState);
  }
}

// checks a single laser sensor
boolean check_laser_sensor(int pin) {
  return analogRead(pin) > laserThreshold;
}

// Checks every laser sensor. If a signal is found, it returns the pin number for that sensor.
// If no laser sensor is found, return -1
int check_all_laser_sensors() {
  if (check_laser_sensor(L_IN1))
    return L_IN1;
  else if (check_laser_sensor(L_IN2))
    return L_IN2;
  else if (check_laser_sensor(L_IN3))
    return L_IN3;
  else if (check_laser_sensor(L_IN4))
    return L_IN4;
  else
    return -1;
}

