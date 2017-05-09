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

const int MIN_X = 0;
const int MAX_X = 4; // I have no idea how wide the grid is
const int MIN_Y = 0;
const int MAX_Y = 4; // or how long it is

int state;
int direction;
int posx;
int posy;

// setup functions here
void setup() {
  // put your setup code here, to run once:
  teensy_led(true);
  motor_controller_setup();
  laser_sensor_setup();
  ultrasonic_sensor_setup();
  bump_sensor_setup();
  state = WAITING;
  posx = 0;
  posy = 0;
}

// main loop
void loop() {
  // put your main code here, to run repeatedly:vc
  run_laser();
  
  if (check_all_bump_sensors() != -1) {
    stop_moving();
    state = BUMPED;
  }
  
  switch(state) {
    case DRIVING:
    {ok 
      teensy_led(true); // doing this for debugging right now
      // drive until we get a signal that we've stopped, then switch to centering
      // speed/time arguements will need to be replaced with appropriate values
      // need to update posx and posy before centering
      if (!drive_to_intersection(direction, 80, 3000)) {
        stop_moving();
        state = WAITING;
      }
      break;
    }
    case CENTERING:
    {
      // run centering routine until finished, then wait
      teensy_led(true); // doing this for debugging right now
      if (!center_in_intersection()) {
        stop_moving();
        state = WAITING;
      }
      break;
    }
    case WAITING:
    {
      teensy_led(false); // if we're stuck in waiting (ie the laser sensor is faulty rn then the led will be off)
      // idle
      // check lasers, if we see adversary then move in appropriate direction
      int result = check_all_laser_sensors();
      if (result != -1) {
        // set direction and switch state to driving

        // TODO: choose the direction based on what laser you read 
        
        state = DRIVING;
        switch (result) {
        case L_IN1:
          direction = BACKWARD;
          break;
        case L_IN2:
          direction = RIGHTWARD;
          break;
        case L_IN3:
          direction = FORWARD;
          break;
        case L_IN4:
          direction = LEFTWARD;
          break;
        default: // this shouldn't happen
          direction = FORWARD;
        }
      }
      break;
    }
    case BUMPED:
    {
      // you're stuck here now bitch
      teensy_led(true);
    }
    default: // shouldn't get here
      stop_moving();
  }
}


