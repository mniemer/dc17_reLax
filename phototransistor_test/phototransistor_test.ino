const int LED = 13; // led on teensy
const int L_OUT = A18; // laser out
const int L_IN1 = A19; // laser sensor inputs
const int L_IN2 = A20;
const int L_IN3 = A21;
const int L_IN4 = A22;
const int thresh = 50;

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
int count = 0;
int ultrasonic[4];

int send_receive_ultrasonic(int id);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(L_OUT, OUTPUT);
  pinMode(L_IN1, INPUT); 
  pinMode(L_IN2, INPUT);
  pinMode(L_IN3, INPUT);
  pinMode(L_IN4, INPUT);

  analogWriteFrequency(L_OUT, 10);   // frequency of pin 37 at 10Hz
  analogWrite(L_OUT,128);
}

void loop() {
  if ((analogRead(L_IN1) > thresh) || (analogRead(L_IN2) > thresh) || (analogRead(L_IN3) > thresh) || (analogRead(L_IN4) > thresh))
    digitalWrite(LED,HIGH);
  else
    digitalWrite(LED,LOW);
   
}

int send_receive_ultrasonic(int id) {   // inputs 0-3
  int echo_pin = 16+id;
  int trig_pin = 20+id;
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  unsigned long distance = pulseIn(echo_pin, HIGH,8000);
  int cm= distance/58;
  return cm;
}

