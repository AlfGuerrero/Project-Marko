import processing.serial.*;
Serial myPort; 
float x, y;
float angle1 = 0.0;
float angle2 = 0.0;
float segLength = 100;
float valNum;      // Data received from the serial port
int val;
float valPrev = 0.00;
float valInter = 0.00; 
float deg;

void setup() {
  size(800, 800);

  x = width /2;
  y = height /2;

  myPort = new Serial(this, "COM3", 9600);
}

void draw() {

  if (myPort.available() > 0)
  {
    valNum = myPort.read();  
    valNum = map(valNum, 0, 255, -3.14, 3.14); 
    valInter = interpolate(valInter, valNum, 0.25);
    println(degrees(valInter));
  }

  background(0);
  fill(0);
  stroke(0, 255, 255);
  strokeWeight(3);
  ellipse(x, y, 100, 100);

  pushMatrix();  
  strokeWeight(20);
  segment(x, y, valInter);   
  arc(mouseY, 0, 10, 100, -PI/2, PI/2);
  popMatrix();
}

void segment(float x, float y, float a) {
  translate(x, y);
  rotate(a);
  line(0, 0, 10, 0);
}

float interpolate(float a, float b, float amount)
{
  return a + (b - a) * amount;
}