const int switchPin = 8;
const int buzzerPin = 9;
unsigned long previousTime = 0;
int switchState = 0;
int prevSwitchState = 0;
int led = 2;
long interval = 1000;
void setup() {
  for(int x = led;x<8;x++){
    pinMode(x, OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  pinMode(switchPin, INPUT);
}

void loop() {
  unsigned long currentTime = millis();
  if(currentTime - previousTime > interval) {
    previousTime = currentTime;
    digitalWrite(led, HIGH);
    led++;
    if(led == 8){
      for(int x = 0;x<4;x++){
        siren();
      }
      noTone(buzzerPin);
    }
  }
  switchState = digitalRead(switchPin);
  if(switchState != prevSwitchState){
    for(int x = 2;x<8;x++){
      digitalWrite(x, LOW);
    }
    led = 2;
    previousTime = currentTime;
  }
  prevSwitchState = switchState;
}

void siren() {
  for(int y = 0;y<501;y++){
          tone(buzzerPin,y);
          delay(2);
        }
        for(int z = 501;z>1;z--){
          tone(buzzerPin,z);
          delay(2);
        }
}


