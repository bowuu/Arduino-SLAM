#include <Servo.h>
#include "MyEncoders.h"

#ifndef __MY_SERVOS__
#define __MY_SERVOS__

#define L_SERVO_PORT 2
#define R_SERVO_PORT 3

Servo LServo, RServo;                   //initialize servos

float lArray[41], rArray[41];           //initialize array for calibrateSpeeds()

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
// reset count, set speed, delay(time), getCounts
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

void fakeCal() {                            //creates array of fake values for
    int i = 0;                              //testing purposes only
    Serial.println("Calibration Table");
    for (float j = -.8; j <= .81; j += .04) {
        lArray[i] = j;
        rArray[i] = j;
        Serial.print("\ni: ");              //serial confirmation
        Serial.print(i);                    //for set values
        Serial.print("    Left Speed: ");
        Serial.print(lArray[i], 4);
        Serial.print("    Right Speed: ");
        Serial.print(rArray[i], 4);
        i++;
    }
    Serial.println("\nCalibration Done\n");
}

//same as the function setSpeeds, but the inputs now indicate
//the revolutions per secont (rps) at which each wheel should spin
void setSpeedsRPS(float rpsLeft, float rpsRight) {
    int i = 0;
    float lMicrosRPS = 0, rMicrosRPS = 0;

    if (rpsLeft < lArray[0]) {                  //condition for extreme 
        rpsLeft = lArray[0];                    //high/low RPS inputs
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
    setSpeeds(lMicrosRPS, rMicrosRPS);
}

//same as the function setSpeeds, but the inputs now indicate
//the inches per second (ips) at which each wheel should spin
void setSpeedsIPS(float ipsLeft, float ipsRight) {
    float tempLeft = ipsLeft / 8.2;       //circumference = Pi*2.61(diameter) = 8.2;
    float tempRight = ipsRight / 8.2;     //converts IPS to RPS
    setSpeedsRPS(tempLeft, tempRight);    //call setSpeeds
}

//this function should make the robot move with a linear speed of v
//measured in inches per second, and an angular speed of w
//in rads per second. Positive ws should indicate a counterclockwise spin.
void setSpeedsvw(float v, float w) {
    float V = v;
    float W = w;
    float R = V / W;                //various functions obtained from 
    float d = 3.95;                 //slides from lectures on kinematics
    float vR = W * (R + (d / 2));
    float vL = W * (R - (d / 2));
            
    if (W == 0) {                   //prevent divide by zero error
        vL = vR = V;                //only use V
    }
    setSpeedsIPS(vL, vR);

    Serial.print("\n\nvL: ");       //serial confirmation
    Serial.print(vL);               //for vL and vR values
    Serial.print("\tvR: ");
    Serial.print(vR);
    Serial.print("\tW: ");
    Serial.print(W);
}
#endif
