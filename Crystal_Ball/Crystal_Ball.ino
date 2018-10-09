#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int positionCounter = 0;
String whitespace = " ";
const char* responses[] = {"Yes", "Most Likely", "Certainly", "Outlook Good", "Unsure", "Ask Again", "Doubtful", "No"};
char* str = responses[random(7)];
void setup() {
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  lcd.print("Ask The");
  lcd.setCursor(0, 1);
  lcd.print("Crystal Ball");
}

void loop() {
  switchState = digitalRead(switchPin);
  if (switchState != prevSwitchState) {
    if (switchState == LOW) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The ball says:");
      switchState = digitalRead(switchPin);
      str = responses[random(7)];
      lcd.setCursor(0, 1);
      lcd.print(str);
      delay(2000);
      while (true) {
        lcd.clear();
        lcd.print("The ball says:");
        lcd.setCursor(positionCounter, 1);
        lcd.print(str);
        delay(150);
        if (positionCounter == 15){positionCounter = -15;}
        positionCounter++;
        if(digitalRead(switchPin) == LOW){break;}
      }
      positionCounter = 0;
      delay(1000);
    }
  }
  prevSwitchState = switchState;
}
