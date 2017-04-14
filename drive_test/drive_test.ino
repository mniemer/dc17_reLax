const int pwm1 = 10; // left wheel
const int dir1 = 11;
const int pwm2 = 9;  // right wheel
const int dir2 = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dir2, OUTPUT);

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

void drive_forward() {
  analogWrite(pwm1,255);
  digitalWrite(dir1,HIGH);
  analogWrite(pwm2,255);
  digitalWrite(dir2,HIGH);
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


