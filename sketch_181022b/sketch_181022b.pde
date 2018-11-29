import processing.serial.*;
Serial myPort;
int centerPoint = height/2+250;
String data;
int index1;
String angle = "";
String distance= "";
float lineX, lineY, xLineSegment, yLineSegment, rad, iAngle, iDistance;
float middleY = height-200/2;

void setup(){
  size (1920, 1080);
  myPort = new Serial(this, "COM5", 9600);
  myPort.bufferUntil('.');
}
void draw(){
  background(0);
  textSize(100);
  text("distance:"+iDistance+"   angle:"+iAngle, 500, 1000);
  translate(width/2, height/2+250);
  rotate(PI);
  noFill();
  stroke(124,253,0);
  strokeWeight(10);
  arc(0, 0, 1500, 1500, 0, PI, CHORD);
  strokeWeight(5);
  arc(0, 0, 1250, 1250, 0, PI);
  arc(0, 0, 1000, 1000, 0, PI);
  arc(0, 0, 750, 750, 0, PI);
  arc(0, 0, 500, 500, 0, PI);
  arc(0, 0, 250, 250, 0, PI);
  lineX = -750 * cos(radians(iAngle));
  lineY = 750 * sin(radians(iAngle));
  xLineSegment = lineX/6;
  yLineSegment = lineY/6;
  line(0, middleY, xLineSegment, yLineSegment);
  line(xLineSegment, yLineSegment, xLineSegment*2, yLineSegment*2);
  line(xLineSegment*2, yLineSegment*2, xLineSegment*3, yLineSegment*3);
}
void serialEvent (Serial myPort) {
  data = myPort.readStringUntil('.');
  data = data.substring(0, data.length()-1);
  index1 = data.indexOf(",");
  angle = data.substring(0, index1);
  distance = data.substring(index1+1, data.length());
  iDistance = int(distance);
  iAngle = int(angle);
  rad = radians(iAngle);
}