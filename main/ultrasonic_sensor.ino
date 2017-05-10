// ultrasonic sensor functions defined here
int ultrasonic[4];
int bestIndex;
boolean centering;
const unsigned long centerInterval = 500;
unsigned long startCenterMillis;
const int lowerThreshold = 25;
const int upperThreshold = 35;
boolean center_y_done;

void ultrasonic_sensor_setup() {
  pinMode(U_ECHO1, INPUT);
  pinMode(U_ECHO2, INPUT);
  pinMode(U_ECHO3, INPUT);
  pinMode(U_ECHO4, INPUT);
  pinMode(U_TRIG1, OUTPUT);
  pinMode(U_TRIG2, OUTPUT);
  pinMode(U_TRIG3, OUTPUT);
  pinMode(U_TRIG4, OUTPUT);
  centering = false;
}

int send_receive_ultrasonic(int id) {   // inputs 0-3
  int echo_pin = 16+id;
  int trig_pin = 20+id;
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  unsigned long distance = pulseIn(echo_pin, HIGH,8000);
  int cm = distance/58;
  return cm;
}

// routine to center robot
// should check ultrasonic sensors one at a time and move appropriately
// returns false if still centering
// returns true when done
boolean center_in_intersection() {
  if (!centering) {
    startCenterMillis = millis();
    centering = true;
    
    for (int i = 0; i < 4; i++) {
      ultrasonic[i] = send_receive_ultrasonic(i);
    }
    
    int min = 100000;
    int done = 0;
    for (int i = 0; i < 4; i++) {
      if (ultrasonic[i] >= lowerThreshold && ultrasonic[i] <= upperThreshold)
        done++;
      if (abs(ultrasonic[i]-30) < min) {
        min = abs(ultrasonic[i]-30);
        bestIndex = i;
      }
    }
    if (done >= 2)
      return false;

    center_x(bestIndex, (ultrasonic[bestIndex]-30) > 0);
    center_y_done = false;
  }
  else {
    unsigned long currCenterMillis = millis();
    // if we've been centering for long enough, stop
    if (currCenterMillis - startCenterMillis > centerInterval) {
      if (!center_y_done) {
        stop_moving();
        center_y(bestIndex, (ultrasonic[bestIndex]-30) > 0);
        startCenterMillis = millis();
        center_y_done = true;
      }
      else {
        centering = false;
      }
    }
  }
  return true;                
}

void center_x(int index, boolean tooFar) {
  switch(index) {
    case 0:
    case 3:
      if (tooFar)
        drive_right(80);
      else
        drive_left(80);
      break;
    case 1:
    case 2:
      if (tooFar)
        drive_left(80);
      else
        drive_right(80);
      break;
    default: // this shouldn't happen
      stop_moving();
  }
}

void center_y(int index, boolean tooFar) {
  switch(index) {
    case 0:
    case 1:
      if (tooFar)
        drive_backward(80);
      else
        drive_forward(80);
      break;
    case 2:
    case 3:
      if (tooFar)
        drive_forward(80);
      else
        drive_backward(80);
      break;
    default: // this shouldn't happen
      stop_moving();
      
  }
}

void drive_angle(double angle, int speed) {
  angle = (PI/180) * angle;
  int motor1 = speed*sin(angle);
  int motor3 = speed*sin(angle);
  int motor2 = speed*cos(angle);
  int motor4 = speed*cos(angle);
  
  digitalWrite(W_DIR1,motor1>=0);
  analogWrite(W_PWM1,abs(motor1));
  digitalWrite(W_DIR2,motor2>=0);
  analogWrite(W_PWM2,abs(motor2));
  digitalWrite(W_DIR3,motor3>=0);
  analogWrite(W_PWM3,abs(motor3));
  digitalWrite(W_DIR4,motor4>=0);
  analogWrite(W_PWM4,abs(motor4));
}














  // old code, don't throw away yet
  /*
  boolean done_x;
  boolean done_y;

  // center on the x axis first
  // robot is on the left side
  if (posx <= MIN_X) {
    // move to appropriate space away from one bucket (bucket is to the right)
    done_x = center_one_sensor(U_TRIG1, U_ECHO1); // the actual sensor number will change
  }
  // robot is on the right side
  else if (posx >= MAX_X) {
    // move to appropriate space away from one bucket (bucket is to the left)
    done_x = center_one_sensor(U_TRIG2, U_ECHO2); // the actual sensor number will change
  }
  else {
    // center between two buckets (x axis)
    done_x = center_two_sensors(U_TRIG1, U_ECHO1, U_TRIG2, U_ECHO2);
  }

  if (!done_x) // if we haven't finished centering on the x axis, return false. Don't start centering on the y axis yet.
    return false;

  // if we get here the x axis should be centered
  // robot is on bottom
  if (posy <= MIN_Y) {
    // move to appropriate space away from one bucket (bucket is above)
    done_y = center_one_sensor(U_TRIG3, U_ECHO3); // the actual sensor number will change
  }
  // robot is on top
  else if (posy >= MAX_Y) {
    // move to appropriate space away from one bucket (bucket is below)
    done_y = center_one_sensor(U_TRIG4, U_ECHO4); // the actual sensor number will change
  }
  else {
    // center between two buckets (y axis)
    done_y = center_two_sensors(U_TRIG3, U_ECHO3, U_TRIG4, U_ECHO4);
  }

  if (!done_y) // if we haven't finished centering on the y axis, return false.
    return false;

  // if we get here then we should be all done. yay!
  return true;
}

// returns false if still centering
// returns true when done
boolean center_one_sensor(int trigPin, int echoPin) {
  // TODO: write this
  return false;
}

// returns false is still centering
// returns true when done
boolean center_two_sensors(int trigPin1, int echoPin1, int trigPin2, int echoPin2) {
  return false;
}
*/

