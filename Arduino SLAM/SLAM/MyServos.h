#ifndef _MY_SERVOS_
#define _MY_SERVOS_

#include "MyEncoders.h"
#include <Wire.h>
#include <Servo.h>
#include <PinChangeInt.h>

#define STANCE 4.1875         //Distance between wheels
#define WHEELCIRC 8.143
#define L_SERVO_PORT 2
#define R_SERVO_PORT 3
#define SHIFT 10000.0

Servo LServo, RServo;       //Initialize servos

int lArray[41] = { -8129, -8128, -8127, -8126, -8125, -7813, -7812, -7811, -7810, -7500,
                   -7500, -7188, -6875, -6563, -5938, -4688, -4063, -2813, -1562, -0625, 0,
                   0313, 1562, 2500, 3750, 4688, 5625, 6205, 6875, 7188, 7500, 7501, 7813,
                   7814, 7815, 7816, 7817, 8125, 8126, 8127, 8128
                 };

int rArray[41] = { -8129, -8128, -8127, -8126, -8125, -7813, -7812, -7811, -7810, -7500,
                   -7500, -7188, -6875, -6563, -5825, -4688, -4063, -2500, -1875, -0313, 0,
                   0625, 1562, 2813, 4063, 4688, 5938, 6250, 6875, 7188, 7500, 7501, 7813,
                   7814, 7815, 7816, 7817, 8125, 8126, 8127, 8128
                 };

void setSpeeds(float microsLeft, float microsRight) {
    LServo.writeMicroseconds(microsLeft + 1500);
    RServo.writeMicroseconds(1500 - microsRight);
}

void setSpeedsRPS(float rpsLeft, float rpsRight) {
    // Serial.println("rps");
    // Serial.println(rpsLeft);
    // Serial.println(rpsRight);
    int i = 0;    
    float lMicrosRPS = 0, rMicrosRPS = 0;
    float lx, ly, rx, ry;
    int rpsLeftInt = rpsLeft * SHIFT;
    int rpsRightInt = rpsRight * SHIFT;
    
    if (rpsLeftInt < lArray[0]) {                  //condition for extreme
        rpsLeftInt = lArray[0];
        rpsLeft = rpsLeftInt / SHIFT;              //high or low RPS inputs
    }
    if (rpsLeftInt > lArray[39]) {
        rpsLeftInt = lArray[39];
        rpsLeft = rpsLeftInt / SHIFT;
    }
    if (rpsRightInt < rArray[0]) {
        rpsRightInt = rArray[0];
        rpsRight = rpsRightInt / SHIFT;
    }
    if (rpsRightInt > rArray[39]) {
        rpsRightInt = rArray[39];
        rpsRight = rpsRightInt / SHIFT;
    }
    for (i = 0; lArray[i] <= rpsLeftInt; i++) {    //interpolation
        lx = lArray[i] / SHIFT;                 //for between intervals
        ly = lArray[i + 1] / SHIFT;
        lMicrosRPS = -200 + 10 * i + 10 * (rpsLeft - lx) / (ly - lx);
    }
    for (i = 0; rArray[i] <= rpsRightInt; i++) {
        rx = rArray[i] / SHIFT;
        ry = rArray[i + 1] / SHIFT;
        rMicrosRPS = -200 + 10 * i + 10 * (rpsRight - rx) / (ry - rx);
    }
    setSpeeds(lMicrosRPS, rMicrosRPS);          //call setSpeeds
}

void setSpeedsIPS(float ipsLeft, float ipsRight) {
    // Serial.println("ssIPS");
    // Serial.println(ipsLeft);
    // Serial.println(ipsRight);
    setSpeedsRPS(ipsLeft / WHEELCIRC, ipsRight / WHEELCIRC);    //call setSpeedsRPS
}

void setSpeedsvw(float v, float w) {
    float vL, vR;
    vL = v - w * STANCE / 2;
    vR = v + w * STANCE / 2;
    setSpeedsIPS(vL, vR);           //call setSpeedsIPS
}

#endif //_MY_SERVOS_

