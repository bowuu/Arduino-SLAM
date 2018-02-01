#ifndef _ROBOT_SETUP_
#define _ROBOT_SETUP_

#include <Arduino.h>
#include <Adafruit_RGBLCDShield.h>
#include "MyServos.h"
#include "MySharpSensor.h"

//LCD
#define OFF     0x0
#define RED     0x1     //RGB SHIELD
#define GREEN   0x2     //color codes
#define YELLOW  0x3
#define BLUE    0x4
#define VIOLET  0x5
#define TEAL    0x6
#define WHITE   0x7

// COLOR SENSOR
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

#define IPS_MAX 6
#define DEL_AMT 200
short button;
RobotStateStruct robotState;
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

void robotSetup() {
    //SET SERVOS - initialize them to speed 0
    LServo.attach(L_SERVO_PORT);
    RServo.attach(R_SERVO_PORT);

    //SET UP LCD DISPLAY
    Serial.begin(115200);
    Serial.println("Lab 3 - Maze");
    lcd.setBacklight(WHITE);
    lcd.begin(16, 2);
    lcd.print("  Lab 3 - Maze  ");

    //SET COLOR SENSOR - set frequency scaling to 20% by setting S0 and S1 to 1 0
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    //initEncoders();
    delay(DEL_AMT); //Ensure sensors have stable output.
    frontSS.sensor = 0;
    leftSS.sensor = 1;
    rightSS.sensor = 2;
}

#endif //_ROBOT_SETUP_

