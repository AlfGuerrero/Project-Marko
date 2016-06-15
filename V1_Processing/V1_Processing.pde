/* Name: Alfrancis Guerrero 
 * Date: 6/2/2016 
 * Notes: Processing file run w/Arduino and Bluetooth Module device. 
 */

import processing.serial.*;
import java.nio.ByteBuffer;

PrintWriter mLogger;

Serial myPort;
float[] mDataRead = {0.0, 0.0}; 
float mPosition;
float mPositionAfter;

float time; 
float prevtime; 

void setup()
{  
  mPosition      = 0;
  mPositionAfter = 0;
  time         = 0.0; 
  prevtime     = 0.0;

  myPort = new Serial(this, "/dev/cu.HC-06-DevB", 9600);

  mLogger = createWriter("DataOutput.csv");
  mLogger.println("Time" + "," + "Distance (m)" + "," + "");
  println("Initialized.");
  size(800, 800, P3D);
}

void draw()
{

  time = millis();
  background(255);
  fill(0);

  while (myPort.available() > 2) 
  {
    for (int i = 0; i < 2; i++) 
    {
      mDataRead[i] = myPort.read();
    }
    mLogger.println( mDataRead[0] + "," + mDataRead[1] + "," + "");

    println("Data Read: " + mDataRead[0] + " " + mDataRead[1] );
  }

  mPosition = (int)mDataRead[0];

  //mPosition = map(mPosition);

  //point(width/2, mPosition);

  ellipse(width/2, height/2, 25, 25);

 /* pushMatrix();
  for (float i = 0.0; i < 3.14 * 2; i++)
  {
    rotateZ(i);
  }
  translate(0, mPosition);
  rect(width/2, height/2, 100, 100);
  popMatrix();*/
  rect(width/2, height/2 + mPosition, 100, 100);

  
}