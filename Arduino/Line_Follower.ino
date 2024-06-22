#include <QTRSensors.h>

#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENA 11
#define ENB 3

int defaultSpeed = 100;

QTRSensors qtr;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

void setup()
{
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, SensorCount);
  qtr.setEmitterPin(2);

  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}


void loop()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, defaultSpeed);
  analogWrite(ENB, defaultSpeed);
  // read raw sensor values
  qtr.read(sensorValues);
/*
  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();
*/

  if(sensorValues[0]>2300){
    while(sensorValues[0]>1000){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      analogWrite(ENA, 200);
      analogWrite(ENB, 0);
      qtr.read(sensorValues);
    } 
  }

  if(sensorValues[5]>2300){
    while(sensorValues[5]>1000){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

      analogWrite(ENA, 0);
      analogWrite(ENB, 200);
      qtr.read(sensorValues);
    }
  }

}
