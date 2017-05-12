// imu sensor functions defined here

const int KP = 10;
const int KD = 20;

LSM6 imu;
double z_rate_avg = -531.935501;  // 100,000 samples gave: -531.935501, should check before competition, earlier was around -667
int z_rate;
double z_drift;
double desired_angle;
int count = 1;
int curr_imu_time;
int prev_imu_time;
int imu_time_diff;
int imu_speed;
int imu_old_error;
int imu_d_error;
int imu_count;

void imu_sensor_setup() {
  Wire.begin(I2C_MASTER, B1101011, I2C_PINS_33_34, I2C_PULLUP_EXT, 400000);
  imu.init();
  imu.enableDefault();
  desired_angle = 0;
  z_drift = 0;
  imu_speed = 0;
  imu_old_error = 0;
  imu_d_error = 0;
  imu_count = 1;
}

void read_imu() {
  imu.read();
  z_rate = imu.g.z;
  curr_imu_time = millis();
  imu_time_diff = curr_imu_time - prev_imu_time;
  //if (imu_count == 1) {
    //imu_time_diff = 0;
    //imu_count = 2;
  //}
  if (abs(z_rate_avg-z_rate) > 400) {
    z_drift += (245.0/32767.0)*(z_rate_avg-z_rate)*imu_time_diff/1000.0;
   }
  prev_imu_time = curr_imu_time;
}

boolean adjust_rotation() {
  double error = (z_drift-desired_angle);
  imu_d_error = error-imu_old_error;
  imu_speed = (signed int) (KP*error + KD*imu_d_error);
  imu_old_error = error;

  if (imu_speed > 75) {
    imu_speed = 75;
  } else if (imu_speed < -75) {
    imu_speed = -75;
  }
  if (abs(error) > 0.5) {
    if (imu_speed <= 0) {
      rotate_ccw(abs(imu_speed));
    } else {
      rotate_cw(imu_speed);
    }
    return true;
  }  
  else {
    return false;
  }
}
