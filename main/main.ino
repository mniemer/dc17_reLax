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

const int FORWARD = 20; // directions for movement
const int BACKWARD = 21;
const int RIGHTWARD = 22;
const int LEFTWARD = 23;

const int DRIVING = 30; // states
const int CENTERING = 31;
const int WAITING = 32;

int state;
int direction;

// setup functions here
void setup() {
  // put your setup code here, to run once:
  teensy_led(true);
  motor_controller_setup();
  laser_sensor_setup();
  ultrasonic_sensor_setup();
  state = WAITING;
  direction = FORWARD;
}

// main loop
void loop() {
  // put your main code here, to run repeatedly:
  run_laser();

  switch(state) {
    case DRIVING:
    {
      // drive until we get a signal that we've stopped, then switch to centering
      // speed/time arguements will need to be replaced with appropriate values
      if (!drive_to_intersection(direction, 100, 1000)) {
        state = CENTERING;
      }
      break;
    }
    case CENTERING:
    {
      // run centering routine until finished, then wait
      teensy_led(false); // doing this for debugging right now
      break;
    }
    case WAITING:
    {
      // idle
      // check lasers, if we see adversary then move in appropriate direction
      int result = check_all_laser_sensors();
      if (result != -1) {
        // set direction and switch state to driving
        state = DRIVING;
      }
      break;
    }
    default: // shouldn't get here
      stop_moving();
  }
}


