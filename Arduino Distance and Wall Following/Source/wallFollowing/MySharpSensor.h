#ifndef _MY_SHARP_SENSORS_
#define _MY_SHARP_SENSORS_
#include "SensorStruct.h"

#define NREADS 5
#define NUM_SENSORS 4
#define SENS_MOD 14
// DISTANCE SENSORS
const int SF = A0;  //Sensor Short FRONT
const int SL = A1;  //Sensor Short LEFT
const int SR = A2;  //Sensor Short RIGHT
const int SG = A3;  //Sensor Long FRONT


SensorStruct frontSS, rightSS;

float shortToInches(int value);
// MEASUREMENTS 0 = SF, 1 = SL, 2 = SR, 3 = SG
short readings[NUM_SENSORS][NREADS];
void takeNewMeasurement(SensorStruct *SS) {
    for (int i = 0; i < NREADS; i++)
    {
        readings[SS->sensor][i] = analogRead(SS->sensor);
        delay(2);
    }
}

//this function should combine the last N measurement taken with sensor 'sensor'
//and return the result. You are free to chose the value of N
short getCombinedDistance(int sensor) {
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
    }
    if (NREADS % 2 == 0) {     //even number of elements
        med = ((readings[sensor][NREADS / 2] + readings[sensor][NREADS / 2 - 1]) / 2.0);
    }
    else {                //odd number of elements
        med = readings[sensor][NREADS / 2];
    }
    return med;
}

//this function takes as input the value obtained by a short distance sensor,
//and it should return its respective value in inches
float shortToInches(int value) {
    //Divide the number of range(13) by voltage(value returned by analog read multiplied by volts per value)
    //and divide by 2.54 to go from centimeters to inches.
    float inchesShort = 13 / (value * 0.0048828125) / 2.54 - .5;
    return inchesShort;
}

//this function takes as input the value obtained by the long distance sensor,
//and it should return its respective value in inches
float longToInches(int value) {     //neeed to fix this eventually
    //Divide the number of range(13) by voltage(value returned by analog read multiplied by volts per value)
    //and divide by 2.54 to go from centimeters to inches.
    float inchesLong = 13 / (value * 0.0048828125) / 2.54;
    return inchesLong;
}

float sPollCalc(SensorStruct *SS) {
    takeNewMeasurement(SS);
    float temp = shortToInches(getCombinedDistance(SS->sensor));
    if (temp > 12) {
        return 12;
    }
    return temp;
}
#endif //_MY_SHARP_SENSOR_
