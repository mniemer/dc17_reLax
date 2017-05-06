const int pwm1 = 3; // wheel 1 (forward/backward)
const int dir1 = 4;
const int pwm2 = 5; // wheel 2 (left/right)
const int dir2 = 6;
const int pwm3 = 7; // wheel 3 (forward/backward)
const int dir3 = 8;
const int pwm4 = 9; // wheel 4 (left/right)
const int dir4 = 10;

// const int spd = 100; // motor speed
int drv = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  pinMode(dir4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  /*digitalWrite(dir4, HIGH);
  digitalWrite(dir3, HIGH);
  digitalWrite(dir2, HIGH);
  digitalWrite(dir1, HIGH);

  analogWrite(pwm1,100);
  delay(1000);
  analogWrite(pwm1,0);
  analogWrite(pwm2,100);
  delay(1000);
  analogWrite(pwm2,0);
  analogWrite(pwm3,100);
  delay(1000);
  analogWrite(pwm3,0);
  analogWrite(pwm4,100);
  delay(1000);
  analogWrite(pwm4,0);*/
  
  /*drive_angle(90, 100); //drive_forward();
  delay(1000);
  stop_moving();
  delay(100);
  drive_angle(0, 100); //drive_right();
  delay(1000);
  stop_moving();
  delay(100);
  drive_angle(270, 100); //drive_backward();
  delay(1000);
  stop_moving();
  delay(100);
  drive_angle(180, 100); //drive_left();
  delay(1000);
  stop_moving();
  delay(2000);*/

  drive_angle(drv, 70);
  delay(10);
  ++drv;
}

void drive_angle(double angle, int spd) {
  angle = (PI/180) * angle;
  int motor1 = spd*sin(angle);
  int motor3 = spd*sin(angle);
  int motor2 = spd*cos(angle);
  int motor4 = spd*cos(angle);
  
  digitalWrite(dir1,motor1>=0);
  analogWrite(pwm1,abs(motor1));
  digitalWrite(dir2,motor2>=0);
  analogWrite(pwm2,abs(motor2));
  digitalWrite(dir3,motor3>=0);
  analogWrite(pwm3,abs(motor3));
  digitalWrite(dir4,motor4>=0);
  analogWrite(pwm4,abs(motor4));
}

void drive_forward(int spd) {
  analogWrite(pwm1,spd);
  digitalWrite(dir1,HIGH);
  analogWrite(pwm3,spd);
  digitalWrite(dir3,HIGH);

  analogWrite(pwm2,0);
  analogWrite(pwm4,0);
}

void drive_backward(int spd) {
  analogWrite(pwm1,spd);
  digitalWrite(dir1,LOW);
  analogWrite(pwm3,spd);
  digitalWrite(dir3,LOW);

  analogWrite(pwm2,0);
  analogWrite(pwm4,0);
}

void drive_left(int spd) {
  analogWrite(pwm2,spd);
  digitalWrite(dir2,LOW);
  analogWrite(pwm4,spd);
  digitalWrite(dir4,LOW);

  analogWrite(pwm1,0);
  analogWrite(pwm3,0);
}

void drive_right(int spd) {
  analogWrite(pwm2,spd);
  digitalWrite(dir2,HIGH);
  analogWrite(pwm4,spd);
  digitalWrite(dir4,HIGH);

  analogWrite(pwm1,0);
  analogWrite(pwm3,0);
}

void stop_moving() {
  analogWrite(pwm1,0);
  digitalWrite(dir1,HIGH);
  analogWrite(pwm3,0);
  digitalWrite(dir3,HIGH);

  analogWrite(pwm2,0);
  digitalWrite(dir2,HIGH);
  analogWrite(pwm4,0);
  digitalWrite(dir4,HIGH);
}


