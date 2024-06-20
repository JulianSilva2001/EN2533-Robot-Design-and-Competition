#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

const int XSHUNT_PIN = 2; // Change this to the pin connected to XSHUNT

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  sensor.init();
  sensor.setTimeout(500);
  
  // Start continuous back-to-back mode (the sensor will continuously measure distances)
  sensor.startContinuous();
  
  pinMode(XSHUNT_PIN, OUTPUT); // Set XSHUNT_PIN as an output
  digitalWrite(XSHUNT_PIN, HIGH); // Set XSHUNT_PIN to HIGH
}

void loop() {
  // Check the state of XSHUNT pin
  int xshuntState = digitalRead(XSHUNT_PIN);
  
  if (xshuntState == LOW) {
    Serial.println("TOF sensor is OFF");
    uint16_t distance = sensor.readRangeContinuousMillimeters();
    
    if (sensor.timeoutOccurred()) {
      Serial.println("Timeout occurred! Check wiring and device");
      return;
    }

    Serial.print("Distance(mm): ");
    Serial.println(distance);
    // You can add further actions here if needed when TOF sensor is off
  } else {
    // Read distance from sensor
    uint16_t distance = sensor.readRangeContinuousMillimeters();
    
    if (sensor.timeoutOccurred()) {
      Serial.println("Timeout occurred! Check wiring and device");
      return;
    }

    Serial.print("Distance(mm): ");
    Serial.println(distance);
  }

  // You can add a small delay here if needed
  // delay(100); // adjust delay as needed
}
