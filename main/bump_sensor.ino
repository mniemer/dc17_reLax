// bump sensor functions defined here
boolean bump_sensors[4];
boolean retreating;
int bump_count;
unsigned long startRetreatMillis;
const unsigned long retreatInterval = 750;
boolean secondMove;
int firstDir;
int secondDir;

void bump_sensor_setup() {
  pinMode(B_IN1, INPUT);
  pinMode(B_IN2, INPUT);
  pinMode(B_IN3, INPUT);
  pinMode(B_IN4, INPUT);

  attachInterrupt(B_IN1, button_isr, FALLING); // interrrupt 1 is data ready
  attachInterrupt(B_IN2, button_isr, FALLING);
  attachInterrupt(B_IN3, button_isr, FALLING);
  attachInterrupt(B_IN4, button_isr, FALLING);
  reset_bump_sensors();
  retreating = false;
}

void button_isr() {
  if (!bump_flag) {
    for (int i = 0; i < 4; i++) {
      bump_sensors[i] = true;
    }
    delayMicroseconds(30000);
    for (int i=0; i<5; i++) {
      for (int j = B_IN1; j < B_IN4+1; j++) {
        bump_sensors[j-B_IN1] &= check_bump_sensor(j);  
      }
    }
    for (int i = 0; i < 4; i++) {
        //stop_moving();
        //delay(1000*(j-B_IN1+1)*bump_sensors[j-B_IN1]);
        bump_flag |= bump_sensors[i];
    }
    if (bump_flag) {
      state = BUMPED;
    }
  }
  else {
    state = BUMPED;
  }
}

boolean check_bump_sensor(int pin) {
  return digitalRead(pin) == LOW;
}

// probably don't need this
void update_bump_sensors() {
  bump_sensors[0] = check_bump_sensor(B_IN1);
  bump_sensors[1] = check_bump_sensor(B_IN2);
  bump_sensors[2] = check_bump_sensor(B_IN3);
  bump_sensors[3] = check_bump_sensor(B_IN4);
}

void reset_bump_sensors() {
  bump_flag = false;
  for (int i = 0; i < 4; i++) {
    bump_sensors[i] = false;
  }
}

boolean retreat_after_bump() {
  if (!retreating) {
    startRetreatMillis = millis();
    retreating = true;
    bump_count = 0;
    for (int i = 0; i < 4; i++) {
      if (bump_sensors[i])
        bump_count++;
    }
    switch (bump_count) {
      case 1:
      {
        if (bump_sensors[0]) {
          firstDir = LEFTWARD;
          secondDir = FORWARD;
        }
        else if (bump_sensors[1]) {
          firstDir = LEFTWARD;
          secondDir = BACKWARD;
        }
        else if (bump_sensors[2]) {
          firstDir = RIGHTWARD;
          secondDir = BACKWARD;
        }
        else if (bump_sensors[3]) {
          firstDir = RIGHTWARD;
          secondDir = FORWARD;
        }
        break;
      }
      case 2:
      {
        // set dir1 and dir 2 to be the same
        if (bump_sensors[0] && bump_sensors[1]) {
          firstDir = LEFTWARD;
          secondDir = LEFTWARD;
        }
        else if (bump_sensors[1] && bump_sensors[2]) {
          firstDir = BACKWARD;
          secondDir = BACKWARD;
        }
        else if (bump_sensors[2] && bump_sensors[3]) {
          firstDir = RIGHTWARD;
          secondDir = RIGHTWARD;
        }
        else if (bump_sensors[3] && bump_sensors[0]) {
          firstDir = FORWARD;
          secondDir = FORWARD;
        }
        else {
          // if this happens we're pretty much dead. do nothing
        }
        break;
      }
      default:
      {
        // this shouldn't happen. do nothing
      }
    }
    // do first move
    set_motors(firstDir, 80);
    secondMove = false;
  }
  else {
    unsigned long currRetreatMillis = millis();
    // if we've been moving for long enough, stop
    if (currRetreatMillis - startRetreatMillis > retreatInterval) {
      if (!secondMove) {
        // do second move
        set_motors(secondDir, 80);
        startRetreatMillis = millis();
        secondMove = true;
      }
      else {
        retreating = false;
        return false;
      }
    }
  }
  return true;
}



