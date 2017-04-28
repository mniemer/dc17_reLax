// motor controller functions defined here

void motor_controller_setup() {
  pinMode(LW_PWM, OUTPUT);
  pinMode(RW_DIR, OUTPUT);
  pinMode(RW_PWM, OUTPUT);
  pinMode(LW_DIR, OUTPUT);
}

void drive_forward() {
  analogWrite(LW_PWM, 255);
  digitalWrite(RW_DIR, HIGH);
  analogWrite(RW_PWM, 255);
  digitalWrite(LW_DIR, HIGH);
}

void drive_backward() {
  analogWrite(LW_PWM,255);
  digitalWrite(RW_DIR,LOW);
  analogWrite(RW_PWM,255);
  digitalWrite(LW_DIR,LOW);
}

void turn_left() {
  analogWrite(LW_PWM,255);
  digitalWrite(RW_DIR,LOW);
  analogWrite(RW_PWM,255);
  digitalWrite(LW_DIR,HIGH);
}

void turn_right() {
  analogWrite(LW_PWM,255);
  digitalWrite(RW_DIR,HIGH);
  analogWrite(RW_PWM,255);
  digitalWrite(LW_DIR,LOW);
}

void stop_moving() {
  analogWrite(LW_PWM,0);
  digitalWrite(RW_DIR,HIGH);
  analogWrite(RW_PWM,0);
  digitalWrite(LW_DIR,HIGH);
}
