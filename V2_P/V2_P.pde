import processing.serial.*;
Serial myPort; 
float x, y;
float angle1 = 0.0;
float angle2 = 0.0;
float segLength = 100;
float valNum[] = {0.0, 0.0};
float valPrev = 0.00;
float valInter = 0.00; 
float deg;
float dist;

void setup() {
  size(800, 800);

  x = width /2;
  y = height /2;

  myPort = new Serial(this, "/dev/cu.usbserial-DA01MCB5", 9600);
  // myPort = new Serial(this, "/dev/cu.HC-06-DevB", 9600);
}

void draw() {

  if (myPort.available() > 1)
  {
    for (int i = 0; i < 2; i++) {
      valNum[i] = myPort.read();
    }
  }
  deg = valNum[0];
  deg = map(deg, 0, 255, -3.14, 3.14); 
  dist = valNum[1];
  dist = map(valNum[1], 0, 255, 0, 1000);
  valInter = interpolate(valInter, deg, 0.25);
  
  
  
  println(degrees(deg), "|", int(dist));

  
  background(0);
  fill(0);
  stroke(0, 255, 255);
  strokeWeight(3);
  ellipse(x, y, 100, 100);

  pushMatrix();  
  strokeWeight(20);
  segment(x, y, valInter);   
  arc(dist, 0, 10, 100, -PI/2, PI/2);
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