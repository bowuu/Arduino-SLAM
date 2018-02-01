#ifndef __ROBOT_COMPONENTS__    // Declaration of variables related to the robot
#define __ROBOT_COMPONENTS__

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Servo.h>

// MOTORS
#define L_SERVO_PORT 2
#define R_SERVO_PORT 3
Servo LServo;
Servo RServo;


// RGB SHIELD
#define RED    0x1
#define GREEN  0x2
#define YELLOW 0x3
#define BLUE   0x4
#define VIOLET 0x5
#define TEAL   0x6
#define WHITE  0x7
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// DISTANCE SENSORS
const int SF = A0;  //Sensor Front
const int SL = A1;  //Sensor Left
const int SR = A2;  //Sensor Right
const int SG = A3;  //Sensor lonG(Front)

// COLOR SENSOR
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8


//ENCODERS
int lEncPin = 10;
int rEncPin = 11;


void setUpRobot(){

  //SET SERVOS - initialize them to speed 0
  LServo.attach(L_SERVO_PORT);
  RServo.attach(R_SERVO_PORT);
  LServo.writeMicroseconds(1500); 
  RServo.writeMicroseconds(1500); 

  //SET UP LCD DISPLAY
  lcd.begin(16, 2);
  lcd.print("USF - RoboBulls!");
  lcd.setCursor(1, 6);
  lcd.print("    STOP");
  lcd.setBacklight(WHITE);  

  //SET ENCODERS
  pinMode(lEncPin, INPUT_PULLUP);
  pinMode(rEncPin, INPUT_PULLUP);

  //SET COLOR SENSOR - set frequency scaling to 20% by setting S0 and S1 to 1 0
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);  
}
#endif
