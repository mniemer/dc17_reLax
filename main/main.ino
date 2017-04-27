const int pwm1 = 10; // left wheel
const int dir1 = 11;
const int pwm2 = 9;  // right wheel
const int dir2 = 12;

void setup() {
  // put your setup code here, to run once:
  motor_controller_setup();
}

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
}
