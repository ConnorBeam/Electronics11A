int incomingByte = 0;   // for incoming serial data
int led[9];
int inbuffer;
void setup() {
  led[0] = 2;
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  for (int i = 1; i < 9; i++) {
    led[i] = i + 2;
  }
  for (int i = 0; i < 9; i++) {
    pinMode(led[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.println(incomingByte);
  }
  switch (incomingByte) {
    case 9:
      turnOff();
      break;
    default:
      turnOff();
      digitalWrite(led[incomingByte], HIGH);
  }
}

void turnOff() {
  for (int i = 0; i < 9; i++) {
    digitalWrite(led[i], LOW);
  }
}

