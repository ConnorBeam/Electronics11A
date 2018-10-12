#include <LiquidCrystal.h>
#include <Wire.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int x = 0;
int realNumber = 0;
String attempt = "";
boolean locked = false;
void setup() {
  lcd.begin(16, 2);
  Wire.begin(9);
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  lcd.print("Keypad Lock LCD");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(5000);
  lcd.clear();
  printUnlocked();
}

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
}

void loop() {
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
      attempt = "";
      break;
    case 13:
      Serial.println("CORRECT ATTEMPT");
      delay(50);
      attempt = "";
      break;
    case 14:
      Serial.println("COMBO RESET");
      delay(50);
      attempt = "";
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

