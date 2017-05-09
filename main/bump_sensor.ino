// bump sensor functions defined here

void bump_sensor_setup() {
  pinMode(B_IN1, INPUT);
  pinMode(B_IN2, INPUT);
  pinMode(B_IN3, INPUT);
  pinMode(B_IN4, INPUT);
}

boolean check_bump_sensor(int pin) {
  return digitalRead(pin) == LOW;
}

int check_all_bump_sensors() {
  if (check_bump_sensor(B_IN1))
    return B_IN1;
  else if (check_bump_sensor(B_IN2))
    return B_IN2;
  else if (check_bump_sensor(B_IN3))
    return B_IN3;
  else if (check_bump_sensor(B_IN4))
    return B_IN4;
  else
    return -1;
}

