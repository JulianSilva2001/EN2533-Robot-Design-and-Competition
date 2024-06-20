#include "Wire.h"
#include "Adafruit_TCS34725.h"

// Initialize the TCS34725 sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);

  // Initialize the sensor
  if (!tcs.begin()) {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt if the sensor is not found
  }
}

void loop() {
  uint16_t clear, red, green, blue;

  // Enable the sensor LED
  tcs.setInterrupt(false);
  delay(60); // Takes 50ms to read
  
  // Get the RGB values
  tcs.getRawData(&red, &green, &blue, &clear);
  
  // Disable the sensor LED
  tcs.setInterrupt(true);

  // Print the RGB values to the serial monitor
  Serial.print("R:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  Serial.print("\tC:\t"); Serial.print(clear);
  Serial.print("\n");

  delay(1000); // Delay between readings
}
