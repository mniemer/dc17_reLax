#include <avr/interrupt.h>

const int pwm1 = 3; // wheel 1 (forward/backward)
const int dir1 = 4;
const int pwm2 = 5; // wheel 2 (left/right)
const int dir2 = 6;
const int pwm3 = 7; // wheel 3 (forward/backward)
const int dir3 = 8;
const int pwm4 = 9; // wheel 4 (left/right)
const int dir4 = 10;

const int led = 13;

const int B_IN1 = 24;
const int B_IN2 = 25;
const int B_IN3 = 26;
const int B_IN4 = 27;

boolean bump_sensors[4];
boolean bump_flag = false;

// const int spd = 100; // motor speed
int drv = 0;

int sensor = 0;

void button_isr();

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

  pinMode(B_IN1, INPUT);
  pinMode(B_IN2, INPUT);
  pinMode(B_IN3, INPUT);
  pinMode(B_IN4, INPUT);

  attachInterrupt(B_IN1, button_isr, FALLING); // interrrupt 1 is data ready
  attachInterrupt(B_IN2, button_isr, FALLING); // interrrupt 1 is data ready
  attachInterrupt(B_IN3, button_isr, FALLING); // interrrupt 1 is data ready
  attachInterrupt(B_IN4, button_isr, FALLING); // interrrupt 1 is data ready

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  bump_flag = false;

  digitalWrite(dir4, HIGH);
  digitalWrite(dir3, LOW);
  digitalWrite(dir2, LOW);
  digitalWrite(dir1, HIGH);

  analogWrite(pwm1,75);
  analogWrite(pwm2,75);
  analogWrite(pwm3,75);
  analogWrite(pwm4,75);

  //delay(2000);

  /*if (check_bump_sensor(B_IN1)) {
    stop_moving();
    delay(1000);
  }
  if (check_bump_sensor(B_IN2)) {
    stop_moving();
    delay(2000);
  }
  if (check_bump_sensor(B_IN3)) {
    stop_moving();
    delay(3000);
  }
  if (check_bump_sensor(B_IN4)) {
    stop_moving();
    delay(4000);
  }*/
  
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
  ++drv;*/
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

boolean check_bump_sensor(int pin) {
  return digitalRead(pin) == LOW;
}

void button_isr() {
  if (bump_flag == false) {
    bump_sensors[0] = 1;
    bump_sensors[1] = 1;
    bump_sensors[2] = 1;
    bump_sensors[3] = 1;
    delay(30);
    for (int i=0; i<5; i++) {
      for (int j = B_IN1; j < B_IN4+1; j++) {
        bump_sensors[j-B_IN1] &= check_bump_sensor(j);  
      }
      //delay(5);
    }
    for (int j = B_IN1; j < B_IN4+1; j++) {
        stop_moving();
        //delay(1000*(j-B_IN1+1)*bump_sensors[j-B_IN1]);
        bump_flag |= bump_sensors[j-B_IN1];
    }
    // if (bump_flag == TRUE) STATE = BUMPED;
    Serial.print(bump_flag);
    Serial.print(bump_sensors[0]);
    Serial.print(bump_sensors[1]);
    Serial.print(bump_sensors[2]);
    Serial.println(bump_sensors[3]);
  }
}


