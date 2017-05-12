// bump sensor functions defined here
boolean bump_flag = false;
boolean[4] bump_sensors;
boolean retreating;
int bump_count;

void button_isr();

void bump_sensor_setup() {
  pinMode(B_IN1, INPUT);
  pinMode(B_IN2, INPUT);
  pinMode(B_IN3, INPUT);
  pinMode(B_IN4, INPUT);

  attachInterrupt(B_IN1, button_isr, FALLING); // interrrupt 1 is data ready
  attachInterrupt(B_IN2, button_isr, FALLING); // interrrupt 1 is data ready
  attachInterrupt(B_IN3, button_isr, FALLING); // interrrupt 1 is data ready
  attachInterrupt(B_IN4, button_isr, FALLING); // interrrupt 1 is data ready
  
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
  bump_flag = false;
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

void button_isr() {
  if (bump_flag == false) {
    bump_sensors[0] = 1;
    bump_sensors[1] = 1;
    bump_sensors[2] = 1;
    bump_sensors[3] = 1;
    delayMicroseconds(30);
    for (int i=0; i<5; i++) {
      for (int j = B_IN1; j < B_IN4+1; j++) {
        bump_sensors[j-B_IN1] &= check_bump_sensor(j);  
      }
      //delayMicroseconds(5);
    }
    for (int j = B_IN1; j < B_IN4+1; j++) {
        stop_moving();
        //delayMicroseconds(1000*(j-B_IN1+1)*bump_sensors[j-B_IN1]);
        bump_flag |= bump_sensors[j-B_IN1];
    }
    if (bump_flag == true) {
      state = BUMPED;
    }
    /*Serial.print(bump_flag);
    Serial.print(bump_sensors[0]);
    Serial.print(bump_sensors[1]);
    Serial.print(bump_sensors[2]);
    Serial.println(bump_sensors[3]);*/
  }
}

