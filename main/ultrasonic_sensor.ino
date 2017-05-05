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

 check_ultrasonic_sensor(int trigPin, int echoPin) {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration/2) / 29.1;
  return distance;
  // when I tested distance = 20 was a about 3-4 inches away
}

// routine to center robot
// should check ultrasonic sensors one at a time and move appropriately
// returns false if still centering
// returns true when done
boolean center_in_intersection() {

  // TODO: write this
  // we decided that using all four sensors is always fine (on walls and corners too)
  
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

