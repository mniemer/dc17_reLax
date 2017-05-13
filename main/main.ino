#include <i2c_t3.h>
#include <LSM6.h>

// pin constants go here
const int LED = 13; // led on teensy

const int W_PWM1 = 3; // wheel pwm
const int W_DIR1 = 4; // wheel dir
const int W_PWM2 = 5;
const int W_DIR2 = 6;
const int W_PWM3 = 7;
const int W_DIR3 = 8;
const int W_PWM4 = 9;
const int W_DIR4 = 10;

const int L_OUT = A18; // laser out
const int L_IN1 = A19; // laser sensor inputs
const int L_IN2 = A20;
const int L_IN3 = A21;
const int L_IN4 = A22;

const int U_ECHO1 = A2; // ultrasonic echo (in)
const int U_TRIG1 = A6; // ultrasonic trigger (out)
const int U_ECHO2 = A3;
const int U_TRIG2 = A7;
const int U_ECHO3 = A4;
const int U_TRIG3 = A8;
const int U_ECHO4 = A5;
const int U_TRIG4 = A9;

const int B_IN1 = 24;
const int B_IN2 = 25;
const int B_IN3 = 26;
const int B_IN4 = 27;

const int FORWARD = 20; // directions for movement
const int BACKWARD = 21;
const int RIGHTWARD = 22;
const int LEFTWARD = 23;

const int DRIVING = 30; // states
const int CENTERING = 31;
const int WAITING = 32;
const int BUMPED = 33;
const int ROTATING1 = 34;
const int ROTATING2 = 35;

const unsigned long waitingTime = 3000;
const unsigned long rotatingTime = 500;
const unsigned long centeringTime = 8000;

int state;
int direction;
boolean bump_flag;
int prevMove;
unsigned long startStateMillis;

int posx;
int posy;

// setup functions here
void setup() {
  // put your setup code here, to run once:
  teensy_led(false);
  imu_sensor_setup();
  motor_controller_setup();
  laser_sensor_setup();
  ultrasonic_sensor_setup();
  bump_sensor_setup();
  state = WAITING;
  startStateMillis = millis();
  prevMove = BACKWARD;
  posx = 1;
  posy = 1;
}

// main loop
void loop() {
  // put your main code here, to run repeatedly
  run_laser();
  read_imu();
  
  switch(state) {
    case DRIVING:
    {
      // drive until we get a signal that we've stopped, then switch to centering
      // speed/time arguements will need to be replaced with appropriate values
      // need to update posx and posy before centering
      if (!drive_to_intersection(direction, 110)) {
        switch(direction) {
          case FORWARD:
            posy++;
            break;
          case BACKWARD:
            posy--;
            break;
          case RIGHTWARD:
            posx++;
            break;
          case LEFTWARD:
            posx--;
            break;
        }
        stop_moving();
        state = ROTATING1;
        startStateMillis = millis();
      }
      break;
    }
    case CENTERING:
    {
      unsigned long currStateMillis = millis();
      unsigned long stateTime = currStateMillis - startStateMillis;
      if (!center_in_intersection() || stateTime > centeringTime) {
        stop_moving();
        state = ROTATING2;
        startStateMillis = millis();
      }
      break;
    }
    case ROTATING1:
    {
      unsigned long currStateMillis = millis();
      unsigned long stateTime = currStateMillis - startStateMillis;
      if (!adjust_rotation() || stateTime > rotatingTime) {
        stop_moving();
        state = CENTERING;
        startStateMillis = millis();
      }
      break;
    }
    case ROTATING2:
    {
      unsigned long currStateMillis = millis();
      unsigned long stateTime = currStateMillis - startStateMillis;
      if (!adjust_rotation() || stateTime > rotatingTime) {
        stop_moving();
        state = WAITING;
        startStateMillis = millis();
      }
      break;
    }
    case WAITING:
    {
      teensy_led(false);
      // idle
      // check lasers, if we see adversary then move in appropriate direction
      int result = check_all_laser_sensors();
      if (result != -1) {
        state = DRIVING;
        
        int outOfBoundsDirX = 0;
        if (posx <= 1)
          outOfBoundsDirX = LEFTWARD;
        else if (posx >= 3)
          outOfBoundsDirX = RIGHTWARD;

        int outOfBoundsDirY = 0;
        if (posy <= 1)
          outOfBoundsDirY = BACKWARD;
        else if (posy >= 3)
          outOfBoundsDirY = FORWARD;
         
        switch (result) {
        case L_IN1:
        {
          direction = generate_direction(RIGHTWARD, outOfBoundsDirX, outOfBoundsDirY);
          break;
        }
        case L_IN2:
        {
          direction = generate_direction(BACKWARD, outOfBoundsDirX, outOfBoundsDirY);
          break;
        }
        case L_IN3:
        {
          direction = generate_direction(LEFTWARD, outOfBoundsDirX, outOfBoundsDirY);
          break;
        }
        case L_IN4:
        {
          direction = generate_direction(FORWARD, outOfBoundsDirX, outOfBoundsDirY);
          break;
        }
        default: // when we've been waiting for too long
          direction = generate_direction(0, outOfBoundsDirX, outOfBoundsDirY);
        }
        prevMove = direction;
        startStateMillis = millis();
      }
      break;
    }
    case BUMPED:
    {
      teensy_led(true);
      if (!retreat_after_bump()) {
        stop_moving();
        reset_bump_sensors();
        state = ROTATING1;
        startStateMillis = millis();
      }
      break;
    }
    default: // shouldn't get here
      stop_moving();
  }
}




