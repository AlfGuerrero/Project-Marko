/*
  V2
*/

#include <NewPing.h>
#include <SoftwareSerial.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif


#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 400

SoftwareSerial mySerial(0, 1);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
float euler[3];         // [psi, theta, phi]    Euler angle container
Quaternion q;           // [w, x, y, z]         quaternion container
float xR;
float yR;
float zR;

int mDistance;
int mValue;


volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}

MPU6050 accelgyro;
int16_t gx, gy, gz;

void setup() {

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  Serial.begin(9600);
  mySerial.begin(9600);
  accelgyro.initialize();
  devStatus = accelgyro.dmpInitialize();

  accelgyro.setXGyroOffset(220);
  accelgyro.setYGyroOffset(76);
  accelgyro.setZGyroOffset(-85);
  accelgyro.setZAccelOffset(1788);

  if (devStatus == 0) {
    accelgyro.setDMPEnabled(true);
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = accelgyro.getIntStatus();
    dmpReady = true;
    packetSize = accelgyro.dmpGetFIFOPacketSize();
  }
}

void loop() {

  if (!dmpReady) return;
  while (!mpuInterrupt && fifoCount < packetSize) {
    //mySerial.listen();

  }

  // Distance Mapping
  delay(50);
  mDistance = sonar.ping_cm();
  mValue = map(mDistance, 400, 0 , 255, 0);
  mValue = constrain(mValue , 0, 255);
  
  

  xR = euler[0] * 180 / M_PI; yR = euler[1] * 180 / M_PI; zR = euler[2] * 180 / M_PI;

  xR = map(xR, -180, 180, 0, 255); yR = map(yR, -180, 180, 0, 255); zR = map(zR, -180, 180, 0, 255);

  mpuInterrupt = false;
  mpuIntStatus = accelgyro.getIntStatus();
  fifoCount = accelgyro.getFIFOCount();

  accelgyro.dmpGetQuaternion(&q, fifoBuffer);
  accelgyro.dmpGetEuler(euler, &q);

  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    accelgyro.resetFIFO();
  }

  else if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = accelgyro.getFIFOCount();

    accelgyro.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;
    Serial.write((int)xR);
    Serial.write((int)mValue);
    delay(100);

  }

}
