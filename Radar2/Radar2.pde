import processing.serial.*;
import ddf.minim.*;
Serial myPort;
Minim minim;
AudioSample alarm;
AudioSample blip;
int centerPoint = height/2+250;
String data;
int index1;
String angle = "";
String distance= "";
float lineX, lineY, lineX2, lineY2, xLineSegment, yLineSegment, rad, iAngle, iDistance, pixsDistance, m, prevtime;
float middleY = height-200/2;
PGraphics canvas;
PGraphics canvas2;

void setup() {
  minim = new Minim(this);
  blip = minim.loadSample("blipp.mp3", 512);
  alarm = minim.loadSample("Navy Alarm Buzzer.mp3", 512);
  size (1920, 1080);
  myPort = new Serial(this, "COM5", 9600);
  myPort.bufferUntil('.');
  canvas = createGraphics(width, height);
  canvas2 = createGraphics(width, height);

void draw() {
  m = millis();
  background(0);
  fadeGraphics(canvas, 2);
  fadeGraphics(canvas2, 1);
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
  lineX = -pixsDistance * cos(radians(iAngle));
  lineY = pixsDistance * sin(radians(iAngle));
  lineX2 = -750 * cos(radians(iAngle));
  lineY2 = 750 * sin(radians(iAngle));
  canvas.line(0, middleY, lineX, lineY);
  canvas.stroke(255, 0, 0);
  canvas.line(lineX, lineY, lineX2, lineY2);
  canvas.endDraw();
  canvas2.beginDraw();
  if (iDistance<50 && m-prevtime >= 1000) {
    blip.trigger();
    canvas2.textSize(40);
    canvas2.text("Bogey", lineX, lineY);
    prevtime = m;
  }
  canvas2.endDraw();
  image(canvas, 0, 0);
  image(canvas2, 0, 0);
  textSize(100);
  textAlign(CENTER);
  text("distance:"+distance+"cm   angle:"+angle+"°", width/2, 1000);
  if (iDistance<20 && m-prevtime >= 6000) {
    alarm.trigger();
    prevtime = m;
  }
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
  if (iDistance <= 60) {
    pixsDistance = iDistance*12.5;
  } else {
    pixsDistance = 60*12.5;
  }
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