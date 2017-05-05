// ultrasonic sensor functions defined here

void ultrasonic_sensor_setup() {
  pinMode(U_ECHO1, INPUT);
  pinMode(U_ECHO2, INPUT);
  pinMode(U_ECHO3, INPUT);
  pinMode(U_ECHO4, INPUT);
  pinMode(U_TRIG1, OUTPUT);
  pinMode(U_TRIG2, OUTPUT);
  pinMode(U_TRIG3, OUTPUT);
  pinMode(U_TRIG4, OUTPUT);
}

boolean check_ultrasonic_sensor(int trigPin, int echoPin) {
  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance < 20; // this value may/will need to be replaced
}

// routine to center robot
// should check ultrasonic sensors one at a time and move appropriately
// will need to know location in the grid
boolean center_in_intersection() {
  return false;
}

