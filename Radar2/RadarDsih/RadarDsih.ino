 #include <Servo.h>

Servo myservo;

unsigned long echo = 0;
int ultraSoundSignal = 10; // Ultrasound signal pin
unsigned long ultrasoundValue = 0;
int pos = 0;
int time = 0;
int previoustime = 250;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  pinMode(ultraSoundSignal, OUTPUT);
}

unsigned long ping() {
  pinMode(ultraSoundSignal, OUTPUT);
  digitalWrite(ultraSoundSignal, LOW);
  delayMicroseconds(2);
  digitalWrite(ultraSoundSignal, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultraSoundSignal, LOW);
  pinMode(ultraSoundSignal, INPUT);
  digitalWrite(ultraSoundSignal, HIGH);
  echo = pulseIn(ultraSoundSignal, HIGH);
  ultrasoundValue = (echo / 58.138);
  return ultrasoundValue;
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    time = millis();
    if (time - previoustime >= 25) {
      int x = 0;
      x = ping();
      Serial.print(pos);
      Serial.print(",");
      Serial.print(x);
      Serial.print(".");
      previoustime = time;
    }
    myservo.write(pos);
    delay(25);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    time = millis();
    if (time - previoustime >= 25) { 
      int x = 0;
      x = ping();
      Serial.print(pos);
      Serial.print(",");
      Serial.print(x);
      Serial.print(".");
      previoustime = time;
    }
    myservo.write(pos);
    delay(25);
  }
}
