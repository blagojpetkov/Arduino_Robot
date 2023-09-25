#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

float accumulatedAngleZ = 0.0;  // Accumulated angle of rotation about the Z-axis

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Serial.println("Initializing I2C devices...");
  mpu.initialize();

  Serial.println("Testing device connections...");
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() {
  static int16_t ax, ay, az;
  static int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);



  // Calculate the bias values by collecting data while the sensor is stationary
  // Then subtract these bias values from gyroX, gyroY, and gyroZ in your real-time application.

  static int16_t gyroX_bias = 0;
  static int16_t gyroY_bias = 0;
  static int16_t gyroZ_bias = 0;
  static int16_t biasFlag = 0;
  // flag to set whether the bias is calculated
  static int sample_count = 0;
  // sample_count is the number of sample values to be collected from the gyroscope to calculate the bias using their average
  if (sample_count < 100) {
    gyroX_bias += gx;
    gyroY_bias += gy;
    gyroZ_bias += gz;
    sample_count++;
  } else {
    if (biasFlag == 0) {
      biasFlag = 1;
      gyroX_bias /= sample_count;
      gyroY_bias /= sample_count;
      gyroZ_bias /= sample_count;
    } else if (biasFlag == 1) {
      // Serial.println("These are the biases for X, Y, Z:");
      // Serial.println(gyroX_bias);
      // Serial.println(gyroY_bias);
      // Serial.println(gyroZ_bias);

      gx -= gyroX_bias;
      gy -= gyroY_bias;
      gz -= gyroZ_bias;





      // //     // Try to fix bias
      // //     accumulatedAngleZ -= 0.1352;

      // Assuming you're using the default sensitivity setting of ±250 dps
      // Convert the raw value to degrees per second
      float rotationRateZ = gz / 131.0;

      // Integrate the rotation rate to get the rotation angle
      // For a 1-second delay, it's just the rate itself.
      // If you change the delay, adjust the multiplication factor accordingly.
      accumulatedAngleZ += rotationRateZ * 0.1;  // Because you're using a delay of 100ms = 0.1s
      if (accumulatedAngleZ >= 90 || accumulatedAngleZ <= -90) {
        Serial.print("Turned 90 degrees");
        accumulatedAngleZ = 0;
      }
      Serial.print("Accumulated Angle Z: ");
      Serial.println(accumulatedAngleZ);
    }
  }



  delay(100);
}