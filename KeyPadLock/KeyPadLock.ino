#include <Keypad.h>
#include <Servo.h>
Servo myServo;

const byte ROWS = 4;
const byte COLS = 3;

const int yellowLed = 2;
const int greenLed = 3;
const int redLed = 4;

boolean locked = false;

char* combo = "8923";
String comboattempt = "";
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
  myServo.attach(5);
  unlock();
}

void loop() {
  char customKey = customKeypad.getKey();
  if (locked == false) {
    switch (customKey) {
      case '*':
        lock();
        break;
      default:
        break;
    }
  }
  if (locked == true) {
    switch (customKey) {
      case NO_KEY:
        break;
      case '#':
        Serial.println ();
        if (comboattempt == combo) {
          Serial.print("Correct code entered: ");
          Serial.println(comboattempt);
          unlock();
        } else {
          Serial.print("Incorrect code entered: ");
          Serial.println(comboattempt);
          for (int i = 0; i < 5; i++) {
            delay(100);
            digitalWrite(redLed, LOW);
            delay(100);
            digitalWrite(redLed, HIGH);
          }
          resetCombo();
        }
        break;
      case '*':
        resetCombo();
        break;
      default:
        comboattempt = comboattempt += customKey;
        Serial.print(customKey);
        Serial.println(" entered");
        Serial.print("Current attempt: ");
        Serial.println(comboattempt);
        digitalWrite(yellowLed, HIGH);
        delay(50);
        digitalWrite(yellowLed, LOW);
    }
  }
}

//Custom Functions Below
void unlock() {
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  Serial.println("The box is unlocked!");
  myServo.write(0);
  locked = false;
}
void lock() {
  digitalWrite(greenLed, LOW);
  Serial.println("The box is locked!");
  myServo.write(90);
  digitalWrite(redLed, HIGH);
  locked = true;
}
void resetCombo() {
  comboattempt = "";
  Serial.println("Reset current combination attempt");
}

