import processing.serial.*;
Serial myPort;
int centerPoint = height/2+250;
String data;
int index1;
String angle = "";
String distance= "";
float lineX, lineY, xLineSegment, yLineSegment, rad, iAngle, iDistance;
float middleY = height-200/2;
PGraphics canvas;

void setup() {
  size (1920, 1080);
  myPort = new Serial(this, "COM5", 9600);
  myPort.bufferUntil('.');
  canvas = createGraphics(width, height);
}
void draw() {
  background(0);
  fadeGraphics(canvas, 2);
  canvas.beginDraw();
  canvas.translate(width/2, height/2+250);
  canvas.rotate(PI);
  canvas.noFill();
  canvas.stroke(124, 253, 0);
  canvas.strokeWeight(10);
  canvas.arc(0, 0, 1500, 1500, 0, PI, CHORD);
  canvas.strokeWeight(5);
  canvas.arc(0, 0, 1250, 1250, 0, PI);
  canvas.arc(0, 0, 1000, 1000, 0, PI);
  canvas.arc(0, 0, 750, 750, 0, PI);
  canvas.arc(0, 0, 500, 500, 0, PI);
  canvas.arc(0, 0, 250, 250, 0, PI);
  lineX = -750 * cos(radians(iAngle));
  lineY = 750 * sin(radians(iAngle));
  xLineSegment = lineX/6;
  yLineSegment = lineY/6;
  if (iDistance <= 10) {
    canvas.stroke(124, 253, 0);
    canvas.line(0, middleY, xLineSegment, yLineSegment);
    canvas.stroke(255, 0, 0);
    canvas.line(xLineSegment, yLineSegment, xLineSegment*2, yLineSegment*2);
    canvas.line(xLineSegment*2, yLineSegment*2, xLineSegment*3, yLineSegment*3);
    canvas.line(xLineSegment*3, yLineSegment*3, xLineSegment*4, yLineSegment*4);
    canvas.line(xLineSegment*4, yLineSegment*4, xLineSegment*5, yLineSegment*5);
    canvas.line(xLineSegment*5, yLineSegment*5, xLineSegment*6, yLineSegment*6);
  } else if (iDistance <= 20) {
    canvas.stroke(124, 253, 0);
    canvas.line(0, middleY, xLineSegment, yLineSegment);
    canvas.line(xLineSegment, yLineSegment, xLineSegment*2, yLineSegment*2);
    canvas.stroke(255, 0, 0);
    canvas.line(xLineSegment*2, yLineSegment*2, xLineSegment*3, yLineSegment*3);
    canvas.line(xLineSegment*3, yLineSegment*3, xLineSegment*4, yLineSegment*4);
    canvas.line(xLineSegment*4, yLineSegment*4, xLineSegment*5, yLineSegment*5);
    canvas.line(xLineSegment*5, yLineSegment*5, xLineSegment*6, yLineSegment*6);
  } else if (iDistance <= 30) {
    canvas.stroke(124, 253, 0);
    canvas.line(0, middleY, xLineSegment, yLineSegment);
    canvas.line(xLineSegment, yLineSegment, xLineSegment*2, yLineSegment*2);
    canvas.line(xLineSegment*2, yLineSegment*2, xLineSegment*3, yLineSegment*3);
    canvas.stroke(255, 0, 0);
    canvas.line(xLineSegment*3, yLineSegment*3, xLineSegment*4, yLineSegment*4);
    canvas.line(xLineSegment*4, yLineSegment*4, xLineSegment*5, yLineSegment*5);
    canvas.line(xLineSegment*5, yLineSegment*5, xLineSegment*6, yLineSegment*6);
  } else if (iDistance <= 40) {
    canvas.stroke(124, 253, 0);
    canvas.line(0, middleY, xLineSegment, yLineSegment);
    canvas.line(xLineSegment, yLineSegment, xLineSegment*2, yLineSegment*2);
    canvas.line(xLineSegment*2, yLineSegment*2, xLineSegment*3, yLineSegment*3);
    canvas.line(xLineSegment*3, yLineSegment*3, xLineSegment*4, yLineSegment*4);
    canvas.stroke(255, 0, 0);
    canvas.line(xLineSegment*4, yLineSegment*4, xLineSegment*5, yLineSegment*5);
    canvas.line(xLineSegment*5, yLineSegment*5, xLineSegment*6, yLineSegment*6);
  } else if (iDistance <= 50) {
    canvas.stroke(124, 253, 0);
    canvas.line(0, middleY, xLineSegment, yLineSegment);
    canvas.line(xLineSegment, yLineSegment, xLineSegment*2, yLineSegment*2);
    canvas.line(xLineSegment*2, yLineSegment*2, xLineSegment*3, yLineSegment*3);
    canvas.line(xLineSegment*3, yLineSegment*3, xLineSegment*4, yLineSegment*4);
    canvas.line(xLineSegment*4, yLineSegment*4, xLineSegment*5, yLineSegment*5);
    canvas.stroke(255, 0, 0);
    canvas.line(xLineSegment*5, yLineSegment*5, xLineSegment*6, yLineSegment*6);
  } else {
    canvas.stroke(124, 253, 0);
    canvas.line(0, middleY, xLineSegment, yLineSegment);
    canvas.line(xLineSegment, yLineSegment, xLineSegment*2, yLineSegment*2);
    canvas.line(xLineSegment*2, yLineSegment*2, xLineSegment*3, yLineSegment*3);
    canvas.line(xLineSegment*3, yLineSegment*3, xLineSegment*4, yLineSegment*4);
    canvas.line(xLineSegment*4, yLineSegment*4, xLineSegment*5, yLineSegment*5);
    canvas.line(xLineSegment*5, yLineSegment*5, xLineSegment*6, yLineSegment*6);
  }
  canvas.endDraw();
  image(canvas, 0, 0);
  textSize(100);
  text("distance:"+iDistance+"   angle:"+iAngle, 500, 1000);
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

void fadeGraphics(PGraphics c, int fadeAmount) {
  c.beginDraw();
  c.loadPixels();
  for (int i =0; i<c.pixels.length; i++) {
    int alpha = (c.pixels[i] >> 24) & 0xFF ;
    alpha = max(0, alpha-fadeAmount);
    c.pixels[i] = alpha<<24 | (c.pixels[i]) & 0xFFFFFF ;
  }

  canvas.updatePixels();
  canvas.endDraw();
}