// pin constants go here
const int LED = 13; // led on teensy

const int LW_PWM = 5; // left wheel
const int LW_DIR = 6;
const int RW_PWM = 9;  // right wheel
const int RW_DIR = 10;

const int L_OUT = A18;
const int L_IN1 = A19;
const int L_IN2 = A20;
const int L_IN3 = A21;
const int L_IN4 = A22;


// setup functions here
void setup() {
  // put your setup code here, to run once:
  teensy_led(true);
  motor_controller_setup();
}

// main loop
void loop() {
  // put your main code here, to run repeatedly:
  drive_forward();
  delay(1000);
  drive_backward();
  delay(1000);
  turn_left();
  delay(1000);
  turn_right();
  delay(1000);
  stop_moving();
  delay(1000);

  run_laser();
}


