
#include <Wire.h>
#include <Keyboard.h>
#include "SensorFusion.h" //SF

/************************************************************
  MPU9250_DMP_Quaternion
  Quaternion example for MPU-9250 DMP Arduino Library
  Jim Lindblom @ SparkFun Electronics
  original creation date: November 23, 2016
  https://github.com/sparkfun/SparkFun_MPU9250_DMP_Arduino_Library

  The MPU-9250's digital motion processor (DMP) can calculate
  four unit quaternions, which can be used to represent the
  rotation of an object.

  This exmaple demonstrates how to configure the DMP to
  calculate quaternions, and prints them out to the serial
  monitor. It also calculates pitch, roll, and yaw from those
  values.

  Development environment specifics:
  Arduino IDE 1.6.12
  SparkFun 9DoF Razor IMU M0

  Supported Platforms:
  - ATSAMD21 (Arduino Zero, SparkFun SAMD21 Breakouts)
*************************************************************/
#include <SparkFunMPU9250-DMP.h>
#include <SparkFunMPL3115A2.h>

#define SerialPort SerialUSB

MPU9250_DMP imu;
MPL3115A2 myPressure;
SF fusion;

float yaw = 0.0f, pitch =0.0f, roll = 0.0f, height = 0.0f;
float yawInRadians = 0.0f;
double currentTime = 0.0;
double lastTimeUpdate = 0.0f;

void setup()
{
  Serial1.begin(115200);
  SerialPort.begin(115200);
  // Call imu.begin() to verify communication and initialize
  if (imu.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("Unable to communicate with MPU-9250");
      SerialPort.println("Check connections, and try again.");
      SerialPort.println();
      delay(5000);
    }
  }
    imu.setGyroFSR(2000); // Set gyro to 2000 dps
    imu.setAccelFSR(2); // Set accel to +/-2g
    imu.setSampleRate(1000);
    imu.setCompassSampleRate(100);
    imu.setLPF(188);

    myPressure.begin();
    myPressure.setModeAltimeter(); // Measure altitude above sea level in meters
    //myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
    
    myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
    myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 

  
}

void loop()
{
  if ( imu.dataReady() ) // If new IMU data is available
  {
      imu.update(); // Update all sensor's
      float accelX = imu.calcAccel(imu.ax); // accelX is x-axis acceleration in g's
      float accelY = imu.calcAccel(imu.ay); // accelY is y-axis acceleration in g's
      float accelZ = imu.calcAccel(imu.az); // accelZ is z-axis acceleration in g's

      float gyroX = imu.calcGyro(imu.gx) * M_PI / 180.0; // gyroX is x-axis rotation in dps
      float gyroY = imu.calcGyro(imu.gy) * M_PI / 180.0; // gyroY is y-axis rotation in dps
      float gyroZ = imu.calcGyro(imu.gz) * M_PI / 180.0; // gyroZ is z-axis rotation in dps

      float magX = imu.calcMag(imu.mx); // magX is x-axis magnetic field in uT
      float magY = imu.calcMag(imu.my); // magY is y-axis magnetic field in uT
      float magZ = imu.calcMag(imu.mz); // magZ is z-axis magnetic field in uT
      float deltat = fusion.deltatUpdate();
      fusion.MadgwickUpdate(gyroX, gyroY, gyroZ, accelX, accelY, accelZ, magX, magY, magZ, deltat);
      //fusion.MahonyUpdate(gyroX, gyroY, gyroZ, accelX, accelY, accelZ, magX, magY, magZ, deltat);

      pitch = fusion.getPitch();
      roll = fusion.getRoll() + 180.0;    //you could also use getRollRadians() ecc
      yaw = fusion.getYaw();

      updateImu();
      sendState();
  }
}

void sendState(){
  currentTime = imu.time / 1000.0;  
  char time[20] = {'\0'};
  sprintf(time, "%.3f", currentTime);
  
  Serial1.print(",");
  Serial1.print(yaw);
  Serial1.print(" ");
  Serial1.print(pitch);
  Serial1.print(" ");
  Serial1.print(roll);
  Serial1.print(" ");
  Serial1.print(height);
  Serial1.print(" ");
  Serial1.println(String(time));
   
  SerialPort.print(",");
  SerialPort.print(yaw);
  SerialPort.print(" ");
  SerialPort.print(pitch);
  SerialPort.print(" ");
  SerialPort.print(roll);
  SerialPort.print(" ");
  SerialPort.println(height);
}

void updateImu(void)
{
   if (yaw > 180) {
    yaw -= 360;
  }

  if (pitch > 180) {
    pitch -= 360;
  }

  if (pitch < -180) {
    pitch += 360;
  }

  if (roll > 180) {
    roll -= 360;
  }
  
  if (roll < -180) {
    roll += 360;
  }
  
  height = myPressure.readAltitude();
  
}
