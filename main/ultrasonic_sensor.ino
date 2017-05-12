// ultrasonic sensor functions defined here
int ultrasonic[4];
int bestIndex;
boolean centering;
const unsigned long centerInterval = 250;
unsigned long startCenterMillis;
const int lowerThreshold = 23;
const int upperThreshold = 37;
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

    ultrasonic[0] = 10000;
    ultrasonic[1] = 10000;
    ultrasonic[2] = 10000;
    ultrasonic[3] = 10000;
    //for (int j = 0; j < 5; j++) {
      for (int i = 0; i < 4; i++) {
        int dist = send_receive_ultrasonic(i);
        //if (abs(dist-30) < abs(ultrasonic[i]-30))
          ultrasonic[i] = dist;
      //}
    }
    
    int min = 100000;
    //int done = 0;
    for (int i = 0; i < 4; i++) {
      if (ultrasonic[i] >= lowerThreshold && ultrasonic[i] <= upperThreshold)
        return false;
      if (abs(ultrasonic[i]-30) < min) {
        min = abs(ultrasonic[i]-30);
        bestIndex = i;
      }
    }

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

void center_y(int index, boolean tooFar) {
  switch(index) {
    case 0:
    case 3:
      if (tooFar)
        drive_forward(80);
      else
        drive_backward(80);
      break;
    case 1:
    case 2:
      if (tooFar)
        drive_backward(80);
      else
        drive_forward(80);
      break;
    default: // this shouldn't happen
      stop_moving();
  }
}

void center_x(int index, boolean tooFar) {
  switch(index) {
    case 0:
    case 1:
      if (tooFar)
        drive_left(80);
      else
        drive_right(80);
      break;
    case 2:
    case 3:
      if (tooFar)
        drive_right(80);
      else
        drive_left(80);
      break;
    default: // this shouldn't happen
      stop_moving();
      
  }
}








