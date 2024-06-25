#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int MPU_addr = 0x68;  // I2C address of MPU-6050

float gyroXangle = 0;
float gyroYangle = 0;
float gyroZangle = 0;

unsigned long timer;
float dt;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  mpu.initialize();
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  timer = micros();
}

void loop() {
  // Calculate delta time
  unsigned long now = micros();
  dt = (float)(now - timer) / 1000000; // Convert microseconds to seconds
  timer = now;

  // Read raw gyro measurements
  mpu.getRotation(&gyroXangle, &gyroYangle, &gyroZangle);

  // Integrate gyro data to obtain angle (using simple integration for demonstration)
  gyroXangle += gyroXangle * dt; // Simplified integration: angle = previous_angle + (angular_velocity * dt)
  gyroYangle += gyroYangle * dt;
  gyroZangle += gyroZangle * dt;

  // Print angles
  Serial.print("X-axis angle: ");
  Serial.print(gyroXangle);
  Serial.print(" | Y-axis angle: ");
  Serial.print(gyroYangle);
  Serial.print(" | Z-axis angle: ");
  Serial.println(gyroZangle);

  delay(100); // Adjust delay as needed for your application
}
