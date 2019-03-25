
#include <Keyboard.h>

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
#include <SimpleKalmanFilter.h>

#define SerialPort SerialUSB

MPU9250_DMP imu;
MPL3115A2 altimeter;
double errorEstimate = .001;
float a0 = 0;
float a1 = 0;
float v0 = 0;
float v1 = 0;
float p0 = 0;
float p1 = 0;
float time0 = millis() / 1000.0;
float time1 = time0;
float count = 0;

SimpleKalmanFilter pressureKalmanFilter( errorEstimate, errorEstimate, 0.001);


void setup()
{
  Serial1.begin(115200);

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
  //imu.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL); // Enable all sensors

  imu.dmpBegin(DMP_FEATURE_SEND_RAW_ACCEL | 
               DMP_FEATURE_SEND_RAW_ACCEL |// Send accelerometer data
               DMP_FEATURE_GYRO_CAL       | // Calibrate the gyro data
               DMP_FEATURE_SEND_CAL_GYRO  | // Send calibrated gyro data
               DMP_FEATURE_6X_LP_QUAT     , // Calculate quat's with accel/gyro
               10);
  // DMP_FEATURE_LP_QUAT can also be used. It uses the
  // accelerometer in low-power mode to estimate quat's.
  // DMP_FEATURE_LP_QUAT and 6X_LP_QUAT are mutually exclusive

  altimeter.begin();

  altimeter.setModeAltimeter();

  altimeter.setOversampleRate(7);
  altimeter.enableEventFlags();

}

void loop()
{
  // Check for new data in the FIFO
  if ( imu.fifoAvailable() )
  {
    // Use dmpUpdateFifo to update the ax, gx, mx, etc. values
    if ( imu.dmpUpdateFifo() == INV_SUCCESS)
    {
      // computeEulerAngles can be used -- after updating the
      // quaternion values -- to estimate roll, pitch, and yaw
      imu.computeEulerAnglesX();
      printIMUData();
    }
  }
}

void printIMUData(void)
{
  // After calling dmpUpdateFifo() the ax, gx, mx, etc. values
  // are all updated.
  // Quaternion values are, by default, stored in Q30 long
  // format. calcQuat turns them into a float between -1 and 1
  //float q0 = imu.calcGyro(imu.qw);
  float q1 = imu.calcGyro(imu.gx);
  float q2 = imu.calcGyro(imu.gy);
  float q3 = imu.calcGyro(imu.gz);

  //  SerialPort.println("Q: " + String(q0, 4) + ", " +
  //                      String(q1, 4) + ", " + String(q2, 4) +
  //                      ", " + String(q3, 4));
  //   SerialPort.println("R/P/Y: " + String(imu.roll) + ", "
  //                      + String(imu.pitch) + ", " + String(imu.yaw));
  //   SerialPort.println("Time: " + String(imu.time) + " ms");
  //   SerialPort.println();
  double pitch = imu.pitch;
  
  if (pitch > 180) {
    pitch -= 360;
  }

  double yaw = imu.yaw;
  if (yaw > 180) {
    yaw -= 360;
  }

  double roll = imu.roll + 180;
  if (roll > 180) {
    roll -= 360;
  }

  double altitude = altimeter.readAltitude(); //* 1000 - 490000;
  double pressure = altimeter.readPressure();
  
  //roll = (roll*cos(45)) + (pitch*sin(45));
  //pitch  = (roll*sin(45)) + (pitch*cos(45));

  //double altitude2 = (pressure - 0.3) * powf((1 + (.00008422880686 * (altimeter.readAltitude() / powf((pressure - .3), 0.190284)))),5.2553026);

  float a1 = imu.calcAccel(imu.az);
  float a2 = imu.calcAccel(imu.ax);
  float a3 = imu.calcAccel(imu.ay);
  float filter = a1 + 1.03;
  float kalman = pressureKalmanFilter.updateEstimate(a1);
  if(abs(filter) < 0.10)
  {
   filter = 0;
  }
  
  time1 = millis() / 10;
  v1 = (filter * time1) - (filter * time0);

p1 = abs((v1*(time1*time1)/2)) - abs((v1*(time0*time0)/2));

  
  //p1 = (p0 + (v0 * time1) + ((filter * (time1*time1))/2)) - (p0 + (v0 * time0) + ((filter * (time0*time0))/2));
if(abs(yaw) < 1)
{
yaw = 0; 
}

if(abs(pitch) < 2)
{
pitch =0;  
}

if(abs(roll) < 2)
{
roll = 0;  
}

  //SerialPort.print(g0);
  //SerialPort.print(" ");

  /*SerialPort.print(q1);
  SerialPort.print(" ");
  SerialPort.print(q2);
  //SerialPort.println(-filter);
  SerialPort.print(" ");
  SerialPort.print(q3);
  SerialPort.print(" ");
*/
    SerialPort.print(yaw);
  SerialPort.print(" ");

  SerialPort.print(pitch);
  SerialPort.print(" ");
  SerialPort.println(roll);

/*
  if(filter > 0)
  {
  SerialPort.print("Baja");
  SerialPort.print(-filter);

  }
  
  if(filter < 0)
  {
  SerialPort.print("Sube");
  SerialPort.print(-filter);

  }
  
  SerialPort.println(-filter);
*/
  // SerialPort.print(" ");
  //SerialPort.print(roll);
  //SerialPort.println(p1);
  //SerialPort.print(" ");


  time0 = time1;
  a0 = a1;
  v0 = v1;
  p0 = p1;


  Serial1.print(",");
  Serial1.print(yaw);
  Serial1.print(" ");
  Serial1.print(roll);
  Serial1.print(" ");
  Serial1.print(-pitch);
  Serial1.print(" ");
  Serial1.println(kalman);

}
