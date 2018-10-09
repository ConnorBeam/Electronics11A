const int controlPin1 = 2; //pin 7 on h-bridge
const int controlPin2 = 3; //pin 2 on h-bridge
const int enablePin = 9; // pin 1 on h-bridge
const int directionSwitchPin = 4; //bottom switch
const int onOffSwitchStateSwitchPin = 5; //top switch
const int potPin = A0; //speed control
const int speedPin1 = 10;
const int speedPin2 = 11;
const int speedPin3 = 12;

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup() {
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(speedPin1, OUTPUT);
  pinMode(speedPin2, OUTPUT);
  pinMode(speedPin3, OUTPUT);
  digitalWrite(enablePin, LOW);
}

void loop() {
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin)/4;
  if(onOffSwitchState != previousOnOffSwitchState) {
    if(onOffSwitchState == HIGH){
      motorEnabled = !motorEnabled;
    }
  }
  if(directionSwitchState != previousDirectionSwitchState) {
    if(directionSwitchState == HIGH){
      motorDirection = !motorDirection;
    }
  }
  if(motorDirection == 1) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }
  if(motorEnabled == 1) {
    analogWrite(enablePin, motorSpeed);
    if(motorSpeed < 2){
      digitalWrite(speedPin1, LOW);
      digitalWrite(speedPin2, LOW);
      digitalWrite(speedPin3, LOW);
    } else if(motorSpeed < 85 && motorSpeed > 2) {
      digitalWrite(speedPin1, HIGH);
      digitalWrite(speedPin2, LOW);
      digitalWrite(speedPin3, LOW);
    } else if(motorSpeed > 84 && motorSpeed < 170) {
      digitalWrite(speedPin1, HIGH);
      digitalWrite(speedPin2, HIGH);
      digitalWrite(speedPin3, LOW);
    } else {
      digitalWrite(speedPin1, HIGH);
      digitalWrite(speedPin2, HIGH);
      digitalWrite(speedPin3, HIGH);
    }
  } else {
    digitalWrite(speedPin1, LOW);
    digitalWrite(speedPin2, LOW);
    digitalWrite(speedPin3, LOW);
    analogWrite(enablePin, 0);
  }
  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
}
