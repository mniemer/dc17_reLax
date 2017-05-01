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

boolean check_ultrasonic_sensor() {
  long duration, distance;
  digitalWrite(U_TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(U_TRIG1, LOW);
;
  duration = pulseIn(U_ECHO1, HIGH);
  distance = (duration/2) / 29.1;
  return distance < 20;
}

