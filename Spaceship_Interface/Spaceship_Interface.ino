int switchState = 0;
void setup() {
  pinMode(3, OUTPUT); // Green LED
  pinMode(4, OUTPUT); // Red LED 1
  pinMode(5, OUTPUT); // Red LED 2
  pinMode(6, OUTPUT); // Red LED 3
  pinMode(2, INPUT); // Button
}

void loop() {
  switchState = digitalRead(2); // Reads the button into a variable
  if (switchState == LOW){
    // Button is not pressed
    digitalWrite(3, HIGH); // Turn on Green LED
    digitalWrite(4, LOW); // Make sure Red LED 1 is off
    digitalWrite(5, LOW); // Make sure Red LED 2 is off
    digitalWrite(6, LOW); // Make sure Red LED 3 is off
  }
  else {
    digitalWrite(3, LOW); // Turn off Green LED
    digitalWrite(4, LOW); // Turn off Red LED 1
    digitalWrite(5, HIGH); // Turn on Red LED 2
    digitalWrite(6, LOW); // Turn off Red LED 3 is off
    delay(250); // Wait for a quarter of a second
    digitalWrite(4, HIGH); // Turn on Red LED 1
    digitalWrite(5, LOW); // Turn off Red LED 2
    digitalWrite(6, LOW); // Turn off Red LED 3 is off
    delay(250);
    digitalWrite(4, LOW); // Turn off Red LED 1
    digitalWrite(5, LOW); // Turn off Red LED 2
    digitalWrite(6, HIGH); // Turn on Red LED 3 is off
    delay(250);
    
  }

}
