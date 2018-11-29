import processing.serial.*;
Serial myserial;
String data="";
String angle="";
String distance="";
int index1=0;
int dist;
int iAngle, iDistance;
float pixsDistance;
String noObject;
void setup() {
  myserial = new Serial(this, "COM5", 9600);
  myserial.bufferUntil('.');
  size(1920, 1080);
  background(0);
  textSize(48);
}

void draw() {
  background(0);
  text("Distance:"+iDistance, 10, 100);
  text("Angle:"+iAngle, 30, 150);
  noFill();
  stroke(255);
  arc(width/2, height/2, 200, 200, HALF_PI, HALF_PI);
}

void serialEvent (Serial myserial) {
  data = myserial.readStringUntil('.');
  data = data.substring(0, data.length()-1);
  index1 = data.indexOf(",");
  angle= data.substring(0, index1);
  distance= data.substring(index1+1, data.length());
  iAngle = int(angle);
  iDistance = int(distance);
}