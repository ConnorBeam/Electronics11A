#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int x = 0;
int realNumber = 0;
String attempt = "";
boolean locked = false;
String inString;
boolean stringComplete = false;
void setup() {
  lcd.begin(16, 2);
  Serial2.begin(115200);
  Serial.begin(9600);
  lcd.print("Keypad Lock LCD");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(5000);
  lcd.clear();
  printUnlocked();
}

void loop() {
  if (Serial2.available() != 0) {
    x = Serial2.read();
    Serial.println(x);
    switch (x) {
      case 0:
        break;
      case 10:
        Serial.println("LOCKED");
        delay(50);
        attempt = "";
        printLocked();
        break;
      case 11:
        Serial.println("UNLOCKED");
        delay(50);
        attempt = "";
        printUnlocked();
        break;
      case 12:
        Serial.println("FAILED ATTEMPT");
        delay(50);
        attempt = "failed";
        printLocked();
        delay(500);
        attempt = "";
        printLocked();
        break;
      case 13:
        Serial.println("CORRECT ATTEMPT");
        delay(50);
        attempt = "";
        break;
      case 14:
        Serial.println("COMBO RESET");
        delay(50);
        attempt = "reset";
        printLocked();
        delay(500);
        attempt = "";
        printLocked();
        break;
      default:
        realNumber = x - 48;;
        attempt += realNumber;
        Serial.print("Received: ");
        Serial.println(realNumber);
        Serial.print("attempt: ");
        Serial.println(attempt);
        printLocked();
        delay(50);
    }
  }
  x = 0;
}

void printLocked() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Box is locked");
  lcd.setCursor(0, 1);
  lcd.print("Attempt: ");
  lcd.setCursor(10, 1);
  lcd.print(attempt);
}
void printUnlocked() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Box is unlocked");
  lcd.setCursor(0, 1);
  lcd.print("Press * to lock");
}

