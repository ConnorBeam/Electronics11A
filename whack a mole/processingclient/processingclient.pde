import processing.serial.*;
Serial myPort = new Serial(this, Serial.list()[0], 9600);
Button[] myButton = new Button[10]; 
color buttonColor = color(255);
int unit = 50;
int space = 50;
int prevTime = 3000;
int delay = 5;
int randint = 1;
String inString;
void setup() {
  size(350, 350);
  int index = 1;
  for (int x = 0; x < 3; x++) {
    myButton[index++] = new Button(50 + x*50, 50, 50, buttonColor);
  }
  for (int x = 0; x < 3; x++) {
    myButton[index++] = new Button(50 + x*50, 100, 50, buttonColor);
  }
  for (int x = 0; x < 3; x++) {
    myButton[index++] = new Button(50 + x*50, 150, 50, buttonColor);
  }
  myButton[0] = new Button(-50, -50, 0, 0);
  prevTime = 1000;
}
void draw() {
  background(0);
  for (int x = 1; x < 10; x++) {
    myButton[x].update(255);
    myButton[randint].update(myButton[randint].active());
  }
  fill(255);
  text(mouseX, 300, 300);
  if (millis() - prevTime > delay*1000) {
    randint = int(random(1, 10));
    prevTime = millis();
    delay = int(random(3, 10));
    myPort.write(randint-1);
  }
  if (myButton[randint].clicked()) {
    randint = 0;
    myPort.write(9);
  }
}

class Button {
  float x, y, s;
  color c;
  Button (float tempx, float tempy, float temps, color tempc) {
    x = tempx;
    y = tempy;
    s = temps;
    c = tempc;
  }
  void update(color cd) {
    if (mouseX < x+s && mouseX > x && mouseY > y && mouseY < y+s) {
      if (mousePressed) {
        fill(50);
      } else {
        fill(150);
      }
    } else {
      fill(0);
    }
    stroke(cd);
    rect(x, y, s, s);
  }
  color active() {
    if (mouseX < x+s && mouseX > x && mouseY > y && mouseY < y+s) {
      if (mousePressed) {
        return color(0, 0, 255);
      } else {
        return color(255, 0, 0);
      }
    } else {
      return color(0, 255, 0);
    }
  }
  boolean clicked() {
    if (mouseX < x+s && mouseX > x && mouseY > y && mouseY < y+s) {
      if (mousePressed) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  }
}

void serialEvent(Serial myPort) { 
  inString = myPort.readString();
  println(inString);
}