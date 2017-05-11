#include <i2c_t3.h>
#include <LSM6.h>

const int pwm1 = 3; // wheel 1 (forward/backward)
const int dir1 = 4;
const int pwm2 = 5; // wheel 2 (left/right)
const int dir2 = 6;
const int pwm3 = 7; // wheel 3 (forward/backward)
const int dir3 = 8;
const int pwm4 = 9; // wheel 4 (left/right)
const int dir4 = 10;

const int KP = 10;
const int KD = 20;

LSM6 imu;
double z_rate_avg = -531.935501;  // 100,000 samples gave: -531.935501, should check before competition, earlier was around -667
int z_rate;
int count = 1;
int current_time;
int prev_time;
int time_diff;
double z_drift = 0;
double desired_angle = 0;

int spd = 0;
int old_error = 0;
int d_error = 0;

void setup()
{ 
  Serial.begin(9600);
  Wire.begin(I2C_MASTER, B1101011, I2C_PINS_33_34, I2C_PULLUP_EXT, 400000);

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();

  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  pinMode(dir4, OUTPUT);
}

void loop()
{
  imu.read();
  z_rate = imu.g.z;
  current_time = millis();
  time_diff = current_time - prev_time;
  if (count == 1) {
    time_diff = 0;
    count = 2;
  }
  if (abs(z_rate_avg-z_rate) > 400) {
    z_drift += (245.0/32767.0)*(z_rate_avg-z_rate)*time_diff/1000.0;
   }
  prev_time = current_time;
  double error = (z_drift-desired_angle);
  Serial.println(error);

  d_error = error-old_error;
  spd = (signed int) (KP*error + KD*d_error);
  old_error = error;

  if (spd > 75) {
    spd = 75;
  } else if (spd < -75) {
    spd = -75;
  }
  if (abs(error)>0.5) {
    if (spd <= 0) {
      rotate_ccw(abs(spd));
    } else {
      rotate_cw(spd);
    }
  }  
  else {
    stop_moving();
  }
  
}

void rotate_cw(int sped) {
  //sped+=20;
  analogWrite(pwm1,sped);
  digitalWrite(dir1,LOW);
  analogWrite(pwm3,sped);
  digitalWrite(dir3,HIGH);
  analogWrite(pwm2,sped);
  digitalWrite(dir2,HIGH);
  analogWrite(pwm4,sped);
  digitalWrite(dir4,LOW);
}

void rotate_ccw(int sped) {
  //sped+=20;
  analogWrite(pwm1,sped);
  digitalWrite(dir1,HIGH);
  analogWrite(pwm3,sped);
  digitalWrite(dir3,LOW);
  analogWrite(pwm2,sped);
  digitalWrite(dir2,LOW);
  analogWrite(pwm4,sped);
  digitalWrite(dir4,HIGH);
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


