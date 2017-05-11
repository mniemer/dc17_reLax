/*
The sensor outputs provided by the library are the raw
16-bit values obtained by concatenating the 8-bit high and
low accelerometer and gyro data registers. They can be
converted to units of g and dps (degrees per second) using
the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).

Example: An LSM6DS33 gives an accelerometer Z axis reading
of 16276 with its default full scale setting of +/- 2 g. The
LA_So specification in the LSM6DS33 datasheet (page 11)
states a conversion factor of 0.061 mg/LSB (least
significant bit) at this FS setting, so the raw reading of
16276 corresponds to 16276 * 0.061 = 992.8 mg = 0.9928 g.
*/

#include <i2c_t3.h>
#include <LSM6.h>

LSM6 imu;
char report[80];
double z_rate_avg = 0;  // 100,000 samples gave: -531.935501, should check before competition, earlier was around -667
int z_rate;
long long count = 1;
int current_time;
int prev_time;
int time_diff;
float z_drift = 0;

void setup()
{
  while(!Serial) {;}
  
  Serial.begin(9600);
  Wire.begin(I2C_MASTER, B1101011, I2C_PINS_33_34, I2C_PULLUP_EXT, 400000);

  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
}

void loop()
{
  imu.read();

  
  z_rate = imu.g.z;
  if (count < 100000) {
    if (count == 1)
      Serial.println("Counting...");
    z_rate_avg = ((count-1.0)/count)*z_rate_avg + (1.0/count)*z_rate;
    //snprintf(report, sizeof(report), "current z_rate: %d",imu.g.z);
    //Serial.println(report);
  }
  else if (count == 100000) {
    snprintf(report, sizeof(report), "average z_rate: %f",z_rate_avg);
    Serial.println(report);
    prev_time = millis();
  }
  else if (count > 100000) {
    current_time = millis();
    time_diff = current_time - prev_time;
    if (abs(z_rate_avg-z_rate) > 400) {
      z_drift += (245.0/32767.0)*(z_rate_avg-z_rate)*time_diff/1000.0;
      snprintf(report, sizeof(report), "drift angle: %f z_rate: %d",z_drift,z_rate);
      Serial.println(report);
    }
      prev_time = current_time;
 
    //delay(100);
  }
  count++;
}
