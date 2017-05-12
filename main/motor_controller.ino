// motor controller functions defined here
// wheels 1 and 3 are parallel, 2 and 4 are parallel
boolean driving;
unsigned long startMillis;

void motor_controller_setup() {
  pinMode(W_PWM1, OUTPUT);
  pinMode(W_DIR1, OUTPUT);
  pinMode(W_PWM2, OUTPUT);
  pinMode(W_DIR2, OUTPUT);
  pinMode(W_PWM3, OUTPUT);
  pinMode(W_DIR3, OUTPUT);
  pinMode(W_PWM4, OUTPUT);
  pinMode(W_DIR4, OUTPUT);
  driving = false;
  startMillis = 0;
}

// drives in given direction at a given speed for given amount of time
// returns boolean indicating whether or not we're still driving
boolean drive_to_intersection(int direction, int speed, unsigned long time) {
  if (!driving) {
    startMillis = millis();
    driving = true;
    switch(direction) {
    case FORWARD:
      drive_forward(speed);
      break;
     case BACKWARD:
      drive_backward(speed);
      break;
     case RIGHTWARD:
      drive_right(speed);
      break;
     case LEFTWARD:
      drive_left(speed);
      break;
     default: // shouldn't get here
      stop_moving();
    }
  }
  else {
    unsigned long currMillis = millis();
    // if we've been driving for long enough, stop
    if (currMillis - startMillis > time) { 
      driving = false;
    }
  }
  return driving;
}

// speed: int between 0 and 255
void drive_forward(int speed) {
  // stop the other pair of wheels (2 and 4)
  analogWrite(W_PWM2, 0);
  analogWrite(W_PWM4, 0);

  // make wheels 1 and 3 turn forward
  analogWrite(W_PWM1, speed);
  digitalWrite(W_DIR1, HIGH);
  analogWrite(W_PWM3, speed);
  digitalWrite(W_DIR3, HIGH);
}

void drive_backward(int speed) {
  // stop the other pair of wheels (2 and 4)
  analogWrite(W_PWM2, 0);
  analogWrite(W_PWM4, 0);

  // make wheels 1 and 3 turn backward
  analogWrite(W_PWM1, speed);
  digitalWrite(W_DIR1, LOW);
  analogWrite(W_PWM3, speed);
  digitalWrite(W_DIR3, LOW);
}


void drive_right(int speed) {
  // stop the other pair of wheels (1 and 3)
  analogWrite(W_PWM1, 0);
  analogWrite(W_PWM3, 0);

  // make wheels 2 and 4 turn forward (HIGH/LOW values may need to be swapped)
  analogWrite(W_PWM2, speed);
  digitalWrite(W_DIR2, HIGH);
  analogWrite(W_PWM4, speed);
  digitalWrite(W_DIR4, HIGH);
}


void drive_left(int speed) {
  // stop the other pair of wheels (1 and 3)
  analogWrite(W_PWM1, 0);
  analogWrite(W_PWM3, 0);

  // make wheels 2 and 4 turn forward (HIGH/LOW values may need to be swapped)
  analogWrite(W_PWM2, speed);
  digitalWrite(W_DIR2, LOW);
  analogWrite(W_PWM4, speed);
  digitalWrite(W_DIR4, LOW);
}

void rotate_cw(int speed) {
  analogWrite(W_PWM1, speed);
  digitalWrite(W_DIR1, LOW);
  analogWrite(W_PWM3, speed);
  digitalWrite(W_DIR3, HIGH);
  analogWrite(W_PWM2, speed);
  digitalWrite(W_DIR2, HIGH);
  analogWrite(W_PWM4, speed);
  digitalWrite(W_DIR4, LOW);
}

void rotate_ccw(int speed) {
  analogWrite(W_PWM1, speed);
  digitalWrite(W_DIR1, HIGH);
  analogWrite(W_PWM3, speed);
  digitalWrite(W_DIR3, LOW);
  analogWrite(W_PWM2, speed);
  digitalWrite(W_DIR2, LOW);
  analogWrite(W_PWM4, speed);
  digitalWrite(W_DIR4, HIGH);
}

void stop_moving() {
  // stop all wheels
  analogWrite(W_PWM1, 0);
  digitalWrite(W_DIR1, HIGH);
  analogWrite(W_PWM2, 0);
  digitalWrite(W_DIR2, HIGH);
  analogWrite(W_PWM3, 0);
  digitalWrite(W_DIR3, HIGH);
  analogWrite(W_PWM4, 0);
  digitalWrite(W_DIR4, HIGH);
}
