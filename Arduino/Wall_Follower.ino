#include <QTRSensors.h>

#define trigPin1 10              // define pin connections for sensor and motor
#define echoPin1 9

#define trigPin2 8             // define pin connections for sensor and motor
#define echoPin2 12

#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENA 11
#define ENB 3

int defaultSpeed = 128;

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

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  digitalWrite(trigPin1, LOW);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  digitalWrite(trigPin2, LOW);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

float rangeWall = 0;
float rangeFront = 0;
int wallfoundDistance = 12 ;
//int toCloseWall = 15;           //Initialze and define the values for distance between wall and robot
//int toFarWall = 15;
int NO_OBSTACLE = 0;
int OBSTACLE = 1;
int WF_DISTANCE = 30;
int WF_Left = 0;
int WF_Left_Status = 0;

//Obstacle in Left: Keep Following: PID values
float WF_Kp = 30;
float WF_Ki = 0.003;
float WF_Kd = 8;

float WF_Error = 0;
int WF_Correction = 0;
float WF_Integral = 0;
float WF_Derivative = 0;
float WF_LastError = 0;

int WF_LeftTurnSpeed = 0;
int WF_RightTurnSpeed = 0;

//Here 0 stands for true and 1 stands for false
int rightTurnBegin = 0;
int leftTurnBegin = 0;
int straightLineBegin = 0;

/*void hardturnRight() 
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 75);
  analogWrite(ENB, 75);
  
}

void hardturnLeft() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 75);
  analogWrite(ENB, 75);
  
}
 
void turnRight() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 50);
  analogWrite(ENB, 75);
  
} 

void turnLeft() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 75);
  analogWrite(ENB, 50);
 
} 

void driveForward()                               // function to drive the robot forward
{   
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 75);
  analogWrite(ENB, 75);
}

void driveBackwardWithTurn()                               // function to drive the robot backward
{   
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 75);
  analogWrite(ENB, 75);
}*/


void loop()
{
  //When a the robot starts following the straight line (until there is a obstacle), initialize the flag to true.
    rightTurnBegin = 0;

    WF_Left = readRangeWall();
    WF_Error = WF_Left - WF_DISTANCE;
    WF_Integral = (WF_Error + WF_Integral);
    WF_Derivative = (WF_Error - WF_LastError);

    WF_Correction = WF_Kp * WF_Error + WF_Kd * WF_Derivative + WF_Ki * WF_Integral;

    //if WF_Error is less than 10, means the robot is following the wall correctly, keep continuing
    if (WF_Error < 10) {

      //Initialize the wall, just in the beginning of straight line
      if (straightLineBegin == 0)
        WF_INITIALIZE_WALL();

      if(WF_Correction > 75 && WF_Correction > 0)
        WF_Correction = 75;

      if(WF_Correction < -75 && WF_Correction < 0)
        WF_Correction = -75;

      WF_LeftTurnSpeed = 75 - WF_Correction;
      WF_RightTurnSpeed = 75 + WF_Correction;

      leftTurnBegin = 0;
      straightLineBegin = 1;

    } else {
      
      //if WF_Error is greater than 10, means the robot has to take left turn

      //Initialize the wall and wall front, just in the beginning of left turn
      if (leftTurnBegin == 0) {
        WF_INITIALIZE_WALL();
      }

      //PID for left turn
      int speed = 2.5 * WF_Error + 8 * WF_Derivative;

      if (speed > 75 && speed > 0)
        speed = 75;

      if (speed < -75 && speed < 0)
        speed = -75;

      WF_LeftTurnSpeed = 75 - (speed);
      WF_RightTurnSpeed = 75 + (speed);

      leftTurnBegin = 1;
      straightLineBegin = 0;

    }

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, WF_RightTurnSpeed);
    analogWrite(ENB, WF_LeftTurnSpeed);
    
    WF_LastError = WF_Error;


/*
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, defaultSpeed);
  analogWrite(ENB, defaultSpeed);
  // read raw sensor values
  qtr.read(sensorValues);



rangeWall = readRangeWall();
rangeFront = readRangeFront();

  if (rangeWall < wallfoundDistance) {
    while (rangeWall < 1000000) {

      if (rangeFront < 8)                        //condition to check side wall is close to robot
      {
        while(rangeFront < 8 * 1.41){
          hardturnRight();
          rangeFront = readRangeFront();

        }
      }

      else { 
      
      if(rangeWall > toCloseWall && rangeWall < toFarWall) //condition to check distance measured by front and side sensor is maintained correctly
      {
        driveForward();
        }
      if (rangeWall < toCloseWall)                        //condition to check side wall is close to robot
      {
        while(rangeWall < toCloseWall){
          //delay(100);
          turnRight();
          rangeWall = readRangeWall();
          //rangeFront = readRangeFront();
        }
        //delay(100);
        //delay(300);
        //turnLeft();
        //delay(300);
        //driveForward();
      }
      if (rangeWall > toFarWall && rangeFront > 8)                         //condition to check robot is far from side wall
      {
        while(rangeWall > toFarWall){
          //delay(100);
          turnLeft();
          rangeWall = readRangeWall();
        }
        //delay(100);
        //delay(300);
        //turnRight();
        //delay(300);
        //driveForward();
      } 

      rangeWall = readRangeWall();
      rangeFront = readRangeFront();

      }
      

    }


  }

rangeWall = readRangeWall();

if (rangeWall < wallfoundDistance) {
  while (true) {
    
    if(rangeWall > toCloseWall && rangeWall < toFarWall) //condition to check distance measured by front and side sensor is maintained correctly
      {
        driveForward();
      }
    
    if (rangeWall < toCloseWall) {
      while(rangeWall < toCloseWall+ 90){
        turnRight();
        rangeWall = readRangeWall();
      }
    }
    if (rangeWall > toFarWall) {
      while(rangeWall > toFarWall){
        turnLeft();
        rangeWall = readRangeWall();
      }
    }
    
    if(rangeWall < line) {
      turnRight();
    }
    if(rangeWall > line + 10) {
      turnLeft();
    }
    rangeWall = readRangeWall();
  }
}

  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();


  if(sensorValues[0]>2300){
    while(sensorValues[0]>1000){
      turnLeft();
      qtr.read(sensorValues);
    } 
  }

  if(sensorValues[5]>2300){
    while(sensorValues[5]>1000){
      turnRight();
      qtr.read(sensorValues);
    }
  }
*/
}

float readRangeWall()                                 // function to read the left sensor value

{ digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Read the result:
  int duration = pulseIn(echoPin1, HIGH);
  float  distance = duration / 58;

  //delay(100);
  return distance;
}

float readRangeFront()                                 // function to read the left sensor value

{ digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Read the result:
  int duration = pulseIn(echoPin2, HIGH);
  float  distance = duration / 58;

  //delay(100);
  return distance;
}

void WF_INITIALIZE_WALL(void) {
  WF_Integral = 0;
  WF_Derivative = 0;
  WF_LastError = 0;
}

int WF_GET_LEFT_US_STATUS(void) {
     if(readRangeWall() < WF_DISTANCE)
       return OBSTACLE;
     else
      return NO_OBSTACLE;
}