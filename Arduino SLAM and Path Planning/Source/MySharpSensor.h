#ifndef _MY_SHARP_SENSORS_
#define _MY_SHARP_SENSORS_

#include "Structs.h"

#define NREADS 10
#define NUM_SENSORS 3

// DISTANCE SENSORS
const int SF = A0;  //Sensor Short FRONT
const int SL = A1;  //Sensor Short LEFT
const int SR = A2;  //Sensor Short RIGHT
const int SG = A3;  //Sensor Long FRONT

SensorStruct frontSS, rightSS, leftSS;

float shortToInches(int value);
float inches[NUM_SENSORS+1];
short readings[NUM_SENSORS][NREADS];

void takeNewMeasurement(Adafruit_RGBLCDShield* lcd) {
    for (int i = 0; i < NUM_SENSORS; i++) {//i = sensor
        for (int j = 0; j < NREADS; j++)//j = read number
        {
            readings[i][j] = analogRead(i);
            delay(5);
        }
    }
}

short getCombinedDistance(int sensor) {
    // float average;
    // for (int i = 0; i < NREADS; ++i)
    // {
    //     average += readings[sensor][i];
    // }
    // average /= NREADS;
    float med, temp;
    int i = 0, j = 0;
    for (i = 0; i < NREADS - 1; i++) {
        for (j = i + 1; j < NREADS; j++) {
            if (readings[sensor][j] < readings[sensor][i]) {
                temp = readings[sensor][i];
                readings[sensor][i] = readings[sensor][j];
                readings[sensor][j] = temp;
            }
        }
    } if (NREADS % 2 == 0) {    //even number of elements
        med = ((readings[sensor][NREADS / 2] + readings[sensor][NREADS / 2 - 1]) / 2.0);
    } else {                    //odd number of elements
        med = readings[sensor][NREADS / 2];
    }
    return med;
    //return average;
}

float shortToInches(int value) {
    float inchesShort = 13 / (value * 0.0048828125) / 2.54 - .5;
    return inchesShort;
}

void sPollCalc(Adafruit_RGBLCDShield* lcd){
    takeNewMeasurement(lcd);
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        inches[4] = shortToInches(getCombinedDistance(i));
        if (inches[4] > 13) {
            inches[i] = 14;
        }
        inches[i]= inches[4];
    }

}

#endif //_MY_SHARP_SENSOR_

