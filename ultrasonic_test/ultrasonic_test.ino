const int U_ECHO1 = 16; // ultrasonic echo (in)
const int U_TRIG1 = 20; // ultrasonic trigger (out)
const int U_ECHO2 = 17;
const int U_TRIG2 = 21;
const int U_ECHO3 = 18;
const int U_TRIG3 = 22;
const int U_ECHO4 = 19;
const int U_TRIG4 = 23;

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
int count = 0;
int ultrasonic[4];

int send_receive_ultrasonic(int id);

void setup() {
  // put your setup code here, to run once:
  pinMode(U_TRIG1, OUTPUT); 
  pinMode(U_ECHO1, INPUT);
  pinMode(U_TRIG2, OUTPUT); 
  pinMode(U_ECHO2, INPUT);
  pinMode(U_TRIG3, OUTPUT); 
  pinMode(U_ECHO3, INPUT);
  pinMode(U_TRIG4, OUTPUT); 
  pinMode(U_ECHO4, INPUT);
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i<4; i++) {
    ultrasonic[i] = send_receive_ultrasonic(i);
  }
    Serial.printf("%d, %d, %d, %d\r\n",ultrasonic[0],ultrasonic[1],ultrasonic[2],ultrasonic[3]);
   
   /*int distance = send_receive_ultrasonic(0);
   if (count%1 == 0) {
    Serial.println(distance);
   }*/
   delay(0);
   
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

