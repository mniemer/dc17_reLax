// bump sensor functions defined here
boolean[4] bump_sensors;
boolean retreating;
int bump_count;

void bump_sensor_setup() {
  pinMode(B_IN1, INPUT);
  pinMode(B_IN2, INPUT);
  pinMode(B_IN3, INPUT);
  pinMode(B_IN4, INPUT);
  reset_bump_sensors();
  retreating = false;
}

boolean check_bump_sensor(int pin) {
  return digitalRead(pin) == LOW;
}

void update_bump_sensors() {
  bump_sensors[0] = check_bump_sensor(B_IN1);
  bump_sensors[1] = check_bump_sensor(B_IN2);
  bump_sensors[2] = check_bump_sensor(B_IN3);
  bump_sensors[3] = check_bump_sensor(B_IN4);
}

void reset_bump_sensors() {
  for (int i = 0; i < 4; i++) {
    bump_sensors[i] = false;
  }
}

boolean check_all_bump_sensors() {
  update_bump_sensors();
  return bump_sensors[0] && bump_sensors[1] && bump_sensors[2] && bump_senors[3];
}

boolean retreat_after_bump() {
  if (!retreating) {
    bump_count = 0;
    for (int i = 0; i < 4; i++) {
      if (bump_sensors[i])
        bump_count++;
    }
    switch (bump_count) {
      case 1:
      {
        break;
      }
      case 2:
      {
        break;
      }
      default: // this shouldn't happen. do nothing
    }
    return true;
  }
  else {
    return true;
  }
}



