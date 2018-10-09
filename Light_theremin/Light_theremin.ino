int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;
const int ledPin = 13;
const int ledPin2 = 5; //Addition
const int ledPin3 = 6; //Addition
const int ledPin4 = 7; //Addition
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  digitalWrite(ledPin, HIGH);
  while (millis() < 5000) {
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
    digitalWrite(ledPin, LOW);
  }
  Serial.print("SensorHigh:");
  Serial.print(sensorHigh);
  Serial.print(", SensorLow:");
  Serial.println(sensorLow);
}

void loop() {
  sensorValue = analogRead(A0);
  int pitch = map(sensorValue,sensorLow,sensorHigh,50,4000);
  if(pitch < 1167) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
  } else if(pitch < 2334) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, LOW);
  } else {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
  }
  Serial.println(pitch);
  tone(8,pitch,20);
  delay(15);
}
