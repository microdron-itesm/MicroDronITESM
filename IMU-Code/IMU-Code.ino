
#include <Wire.h>


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

#define SerialPort SerialUSB

MPU9250_DMP imu;
MPL3115A2 myPressure;

float yaw = 0.0f, pitch =0.0f, roll = 0.0f, height = 0.0f;
float yawInRadians = 0.0f;
double currentTime = 0.0;
double lastTimeUpdate = 0.0f;

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
    imu.begin(); // Initialize the MPU-9250.

    // Initialize the digital motion processor
    imu.dmpBegin(DMP_FEATURE_SEND_RAW_ACCEL | // Send accelerometer data
                 DMP_FEATURE_GYRO_CAL       | // Calibrate the gyro data
                 DMP_FEATURE_SEND_CAL_GYRO  | // Send calibrated gyro data
                 DMP_FEATURE_6X_LP_QUAT     , // Calculate quat's with accel/gyro
                 100);                        // Set update rate to 100Hz.
    imu.setLPF(5);
    myPressure.begin();
    myPressure.setModeAltimeter(); // Measure altitude above sea level in meters
    //myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
    
    myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
    myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 

  
}

void loop()
{
  
  if ( imu.fifoAvailable() > 0 ) // Check for new data in the FIFO
  {
      // Use dmpUpdateFifo to update the ax, gx, qx, etc. values
      if ( imu.dmpUpdateFifo() == INV_SUCCESS )
      {
          // The following variables will have data from the top of the FIFO:
          // imu.ax, imu.ay, imu.az, -- Accelerometer
          // imu.gx, imu.gy, imu.gz -- calibrated gyroscope
          // and imu.qw, imu.qx, imu.qy, and imu.qz -- quaternions
          imu.computeEulerAnglesX();
          updateImu();
          sendState();
      }
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
 
  yaw = imu.yaw;
  if (yaw > 180) {
    yaw -= 360;
  }

  yawInRadians = yaw * PI / 180.0;
  
   pitch = imu.pitch;
  if (pitch > 180) {
    pitch -= 360;
  }

  if (pitch < -180) {
    pitch += 360;
  }

  roll = imu.roll + 180;
  if (roll > 180) {
    roll -= 360;
  }
  
  if (roll < -180) {
    roll += 360;
  }
  
  height = myPressure.readAltitude();
  
}
