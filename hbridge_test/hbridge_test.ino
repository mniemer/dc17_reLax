const int pwm1 = 10;
const int dir1 = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm1, OUTPUT);
  pinMode(dir1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(pwm1,255);
  digitalWrite(dir1,HIGH);
  delay(500);
  digitalWrite(dir1,LOW);
  delay(500);
}
