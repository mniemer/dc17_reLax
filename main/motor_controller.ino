// motor controller functions defined here

void motor_controller_setup() {
  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dir2, OUTPUT);
}

void drive_forward() {
  analogWrite(pwm1, 255);
  digitalWrite(dir1, HIGH);
  analogWrite(pwm2, 255);
  digitalWrite(dir2, HIGH);
}

void drive_backward() {
  analogWrite(pwm1,255);
  digitalWrite(dir1,LOW);
  analogWrite(pwm2,255);
  digitalWrite(dir2,LOW);
}

void turn_left() {
  analogWrite(pwm1,255);
  digitalWrite(dir1,LOW);
  analogWrite(pwm2,255);
  digitalWrite(dir2,HIGH);
}

void turn_right() {
  analogWrite(pwm1,255);
  digitalWrite(dir1,HIGH);
  analogWrite(pwm2,255);
  digitalWrite(dir2,LOW);
}

void stop_moving() {
  analogWrite(pwm1,0);
  digitalWrite(dir1,HIGH);
  analogWrite(pwm2,0);
  digitalWrite(dir2,HIGH);
}
