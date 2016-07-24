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
float dist_1;
void setup() {
  size(800, 800);

  x = width /2;
  y = height /2;

  myPort = new Serial(this, "/dev/cu.usbserial-DA01MCB5", 9600);
  // myPort = new Serial(this, "/dev/cu.HC-06-DevB", 9600);
  //Travis test change
}

void draw() {

  // Port Reading
  if (myPort.available() > 1)
  {
    for (int i = 0; i < 2; i++) {
      valNum[i] = myPort.read();
    }
  }
  
  // Rotations
  deg = valNum[0];
  deg = map(deg, 0, 255, -3.14, 3.14); 
  valInter = interpolate(valInter, deg, 0.25);

  // Distances
  dist = map(valNum[1], 0, 255, 0, 1000);
  if (dist > 0) dist_1 = interpolate(dist_1, dist, 0.25);
  
  // Print Degrees and Distance
  println(degrees(deg), "|", int(dist));
  
  // User Interface
  background(0);
  fill(0);
  stroke(0, 255, 255);
  strokeWeight(3);
  ellipse(x, y, 100, 100);

  pushMatrix();  
  strokeWeight(20);
  segment(x, y, valInter);   
  arc(dist_1, 0, 10, 100, -PI/2, PI/2);
  popMatrix();
}

// Drawing Line
void segment(float x, float y, float a) {
  translate(x, y);
  rotate(a);
  line(0, 0, 10, 0);
}

float interpolate(float a, float b, float amount)
{
  return a + (b - a) * amount;
}