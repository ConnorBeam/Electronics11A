#include <Servo.h>
Servo myServo;
int const potPin = A0;
int potVal;
int angle;
void setup() {
  myServo.attach(9);
  Serial.begin(9600);
}

void loop() {
//  potVal = analogRead(potPin);
//  Serial.print("potval: ");
//  Serial.print(potVal);
//  angle = map(potVal, 0, 1023, 0, 179);
//  Serial.print(", angle: ");
//  Serial.println(angle);
//  myServo.write(angle);
//  delay(15);
  for(int i=0; i <= 179; i++){
    myServo.write(i);
    delay(15);
  }
  for(int i=179; i >= 0; i--){
    myServo.write(i);
    delay(15);
  }
}
