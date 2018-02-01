#include <Servo.h>
#include "MyEncoders.h"

#ifndef __MY_SERVOS__
#define __MY_SERVOS__
#define STANCE 3.95      //Distance between wheels
#define L_SERVO_PORT 2
#define R_SERVO_PORT 3

Servo LServo, RServo;                   //initialize servos

float lArray[41] = { -0.7813, -0.7813, -0.7813, -0.7813, -0.7813, -0.8125, -0.7813, -0.7500, -0.7813, -0.7500,
                     -0.7188, -0.7188, -0.6563, -0.6563, -0.5625, -0.4688, -0.3750, -0.2813, -0.1562, -0.0313,
                     0.0000,  0.0313,  0.1562,  0.2500,  0.3750,  0.4375,  0.5313,  0.5938,  0.6563, 0.6875,
                     0.7188,  0.7188,  0.7500,  0.7813,  0.7813,  0.7500,  0.7500,  0.7813,  0.7813, 0.7813, 0.7813
                   };

float rArray[41] = { -0.8125, -0.7813, -0.7813, -0.8125, -0.7813, -0.7813, -0.7813, -0.7813, -0.7813, -0.7500,
                     -0.7188, -0.7188, -0.6563, -0.6250, -0.5313, -0.4688, -0.3750, -0.2500, -0.1250, -0.0625,
                     0.0000,  0.0313,  0.1562,  0.2813,  0.3438,  0.5000,  0.5625,  0.6250,  0.6875,  0.7188,
                     0.7500,  0.7500,  0.7813,  0.7813,  0.7813,  0.7813,  0.8125,  0.7813,  0.8125,  0.7813, 0.8125
                   };

//this function should set the left and right speeds of the wheel
//when both inputs are positive the robot should move forward
//when both inputs are negative the robot should move backward
//microsLeft should encode the left wheel velocity and viceversa
void setSpeeds(int microsLeft, int microsRight) {
    LServo.writeMicroseconds(microsLeft + 1500);
    RServo.writeMicroseconds(1500 - microsRight);
}

//this function is meant for doing whatever necessary for the
//functions 'setSpeedsIPS' and 'setSpeedsRPS' to work properly
//reset count, set speed, delay(time), getCounts
void calibrateSpeeds() {
    int i = 0;
    unsigned long speedArray[2];

    Serial.println("Calibration Table");
    Serial.println("\ni\tInput Micros\tLeft Speed\tRight Speed");

    setSpeeds(-200, -200);                  //start motor first
    delay(1000);                            //delay before looping

    for (i = 0; i <= 40; ++i) {
        int inc = -200 + 10 * i;
        setSpeeds(inc, inc);
        resetCounts();
        delay(1000);                        //deltaT = 1000
        getCounts(speedArray);

        float leftSpeed =  (speedArray[0] / 32.0);  //divide by holes
        float rightSpeed = (speedArray[1] / 32.0);

        if (i < 20) {                       //invert values
            leftSpeed = 0 - leftSpeed;      //for negatives
            rightSpeed = 0 - rightSpeed;
        }
        lArray[i] = leftSpeed;
        rArray[i] = rightSpeed;

        Serial.print(i);                    //serial confirmation
        Serial.print("\t");                 //for calibrated values
        Serial.print(inc);
        Serial.print("\t\t");
        Serial.print(lArray[i], 4);
        Serial.print("\t\t");
        Serial.println(rArray[i], 4);
    }
    Serial.println("\nCalibration Done\n");
}

//same as the function setSpeeds, but the inputs now indicate
//the revolutions per secont (rps) at which each wheel should spin
void setSpeedsRPS(float rpsLeft, float rpsRight) {
    int i = 0;
    float lMicrosRPS = 0, rMicrosRPS = 0;

    if (rpsLeft < lArray[0]) {                  //condition for extreme
        rpsLeft = lArray[0];                    //high or low RPS inputs
    } if (rpsLeft > lArray[40]) {
        rpsLeft = lArray[40];
    } if (rpsRight < rArray[0]) {
        rpsRight = rArray[0];
    } if (rpsRight > rArray[40]) {
        rpsRight = rArray[40];
    }

    for (i = 0; lArray[i] <= rpsLeft; i++) {    //interpolation
        float lx = lArray[i];                   //for between intervals
        float ly = lArray[i + 1];
        lMicrosRPS = -200 + 10 * i + 10 * (rpsLeft - lx) / (ly - lx);
    }
    for (i = 0; rArray[i] <= rpsRight; i++) {
        float rx = rArray[i];
        float ry = rArray[i + 1];
        rMicrosRPS = -200 + 10 * i + 10 * (rpsRight - rx) / (ry - rx);
    }
    setSpeeds(lMicrosRPS, rMicrosRPS);          //call setSpeeds
}

//same as the function setSpeeds, but the inputs now indicate
//the inches per second (ips) at which each wheel should spin
void setSpeedsIPS(float ipsLeft, float ipsRight) {
    setSpeedsRPS(ipsLeft / 8.2, ipsRight / 8.2);    //call setSpeedsRPS
}

//this function should make the robot move with a linear speed of v
//measured in inches per second, and an angular speed of w
//in rads per second. Positive ws should indicate a counterclockwise spin.
void setSpeedsvw(float v, float w) {
    float vL, vR;
    vL = v - w*STANCE / 2;
    vR = v + w*STANCE / 2;
    setSpeedsIPS(vL, vR);           //call setSpeedsIPS
}
#endif
