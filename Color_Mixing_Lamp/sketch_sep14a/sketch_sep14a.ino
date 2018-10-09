const int greenLEDPin = 9;
const int redLEDPin = 10;
const int blueLEDPin = 11;

const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redmodvalue = 0;
int greenmodvalue = 0;
int bluemodvalue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void getValues() {
  blueSensorValue = analogRead(blueSensorPin);
  delay(5);
  greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  redSensorValue = analogRead(redSensorPin);
}

void sendValues() {
//  Serial.print("Raw Sensor Value \t red: ");
//  Serial.print(redSensorValue);
//  Serial.print("\t green: ");
//  Serial.print(greenSensorValue);
//  Serial.print("\t blue: ");
//  Serial.println(blueSensorValue);
//  Serial.print("Mapped Sensor Values \t red: ");
//  Serial.print(redValue);
//  Serial.print("\t green: ");
//  Serial.print(greenValue);
//  Serial.print("\t blue: ");
//  Serial.println(blueValue);
  Serial.print("Final Sensor Values \t red: ");
  Serial.print(redmodvalue);
  Serial.print("\t green: ");
  Serial.print(greenmodvalue);
  Serial.print("\t blue: ");
  Serial.println(bluemodvalue);
}

void setup() {
  Serial.begin(9600);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop() {
  getValues();
  redValue = redSensorValue/4;
  greenValue = greenSensorValue/4;
  blueValue = blueSensorValue/4;
  sendValues();
  
  for (float i=0; i <= 1; i+=0.01){
    redmodvalue = redValue*i;
    greenmodvalue = greenValue*i;
    bluemodvalue = blueValue*i;
    analogWrite(redLEDPin, redmodvalue);
    analogWrite(greenLEDPin, greenmodvalue);
    analogWrite(blueLEDPin, bluemodvalue);
    delay(10);
    getValues();
  }
  sendValues();
  for (float i=1; i >= 0; i-=0.01){
    redmodvalue = redValue*i;
    greenmodvalue = greenValue*i;
    bluemodvalue = blueValue*i;
    analogWrite(redLEDPin, redmodvalue);
    analogWrite(greenLEDPin, greenmodvalue);
    analogWrite(blueLEDPin, bluemodvalue);
    delay(10);
    getValues();
  }
  sendValues();
//  analogWrite(redLEDPin, redValue);
//  analogWrite(greenLEDPin, greenValue);
//  analogWrite(blueLEDPin, blueValue);
}
