// pin constants go here
const int LED = 13; // led on teensy

const int LW_PWM = 5; // left wheel
const int LW_DIR = 6;
const int RW_PWM = 9;  // right wheel
const int RW_DIR = 10;

const int L_OUT = A18; // laser out
const int L_IN1 = A19; // laser sensor inputs
const int L_IN2 = A20;
const int L_IN3 = A21;
const int L_IN4 = A22;

boolean stopped;

// setup functions here
void setup() {
  // put your setup code here, to run once:
  teensy_led(true);
  motor_controller_setup();
  laser_sensor_setup();
  stopped = false;
}

// main loop
void loop() {
  // put your main code here, to run repeatedly:
  if (!stopped){
    drive_forward();
  }
  run_laser();
  if (check_laser_sensor(L_IN1)) {
    stop_moving();
    stopped = true;
  }
}


