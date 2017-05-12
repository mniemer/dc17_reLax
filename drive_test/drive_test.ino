const int W_PWM1 = 3; // wheel pwm
const int W_DIR1 = 4; // wheel dir
const int W_PWM2 = 5;
const int W_DIR2 = 6;
const int W_PWM3 = 7;
const int W_DIR3 = 8;
const int W_PWM4 = 9;
const int W_DIR4 = 10;

// const int spd = 100; // motor speed
int drv = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(W_PWM1, OUTPUT);
  pinMode(W_DIR1, OUTPUT);
  pinMode(W_PWM2, OUTPUT);
  pinMode(W_DIR2, OUTPUT);
  pinMode(W_PWM3, OUTPUT);
  pinMode(W_DIR3, OUTPUT);
  pinMode(W_PWM4, OUTPUT);
  pinMode(W_DIR4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  drive_forward(80);
  delay(1000);
  drive_backward(80);
  delay(1000);
  drive_right(80);
  delay(1000);
  drive_left(80);
  delay(1000);
  stop_moving();

}


// speed: int between 0 and 255
void drive_right(int speed) {
  // stop the other pair of wheels (2 and 4)
  analogWrite(W_PWM2, 0);
  analogWrite(W_PWM4, 0);

  // make wheels 1 and 3 turn forward
  analogWrite(W_PWM1, speed);
  digitalWrite(W_DIR1, HIGH);
  analogWrite(W_PWM3, speed);
  digitalWrite(W_DIR3, HIGH);
}

void drive_left(int speed) {
  // stop the other pair of wheels (2 and 4)
  analogWrite(W_PWM2, 0);
  analogWrite(W_PWM4, 0);

  // make wheels 1 and 3 turn backward
  analogWrite(W_PWM1, speed);
  digitalWrite(W_DIR1, LOW);
  analogWrite(W_PWM3, speed);
  digitalWrite(W_DIR3, LOW);
}


void drive_forward(int speed) {
  // stop the other pair of wheels (1 and 3)
  analogWrite(W_PWM1, 0);
  analogWrite(W_PWM3, 0);

  // make wheels 2 and 4 turn forward (HIGH/LOW values may need to be swapped)
  analogWrite(W_PWM2, speed);
  digitalWrite(W_DIR2, HIGH);
  analogWrite(W_PWM4, speed);
  digitalWrite(W_DIR4, HIGH);
}


void drive_backward(int speed) {
  // stop the other pair of wheels (1 and 3)
  analogWrite(W_PWM1, 0);
  analogWrite(W_PWM3, 0);

  // make wheels 2 and 4 turn forward (HIGH/LOW values may need to be swapped)
  analogWrite(W_PWM2, speed);
  digitalWrite(W_DIR2, LOW);
  analogWrite(W_PWM4, speed);
  digitalWrite(W_DIR4, LOW);
}

void stop_moving() {
  // stop all wheels
  analogWrite(W_PWM1, 0);
  digitalWrite(W_DIR1, HIGH);
  analogWrite(W_PWM2, 0);
  digitalWrite(W_DIR2, HIGH);
  analogWrite(W_PWM3, 0);
  digitalWrite(W_DIR3, HIGH);
  analogWrite(W_PWM4, 0);
  digitalWrite(W_DIR4, HIGH);
}

/*
  digitalWrite(dir4, HIGH);
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
  analogWrite(pwm4,0);
  
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

  /*drive_angle(drv, 70);
  delay(10);
  ++drv;


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
*/

