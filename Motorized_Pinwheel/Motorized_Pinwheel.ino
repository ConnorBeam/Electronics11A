const int switchPin = 2;
const int motorPin = 9;
bool motorState = false;
int switchState = 0;
int state = 0;
int previousState = 0;
void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(switchPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  switchState = digitalRead(switchPin);
  if (switchState == HIGH && previousState == LOW) {
    if (state == HIGH) {
      state = LOW;
    } else {
      state = HIGH;
    }
  }
  digitalWrite(motorPin, state);
  Serial.println(state);
  previousState = switchState;
}
