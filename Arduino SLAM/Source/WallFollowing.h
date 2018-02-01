#ifndef _WALL_FOLLOWING_
#define _WALL_FOLLOWING_

#include "RobotSetup.h"

#define KP 1.2
#define KD 0.7
#define RT 6.5          //Goal distance
#define SAT 0.6       //works at 1.8 lower runs smoother

float satFunc(float input);
float wallDistance(SensorStruct *SS);
float PID(SensorStruct *SS);
void wallFollowing(SensorStruct* SS);

float satFunc(float input) {
    if (input > SAT) {
        return SAT;
    } else if (input < -SAT) {
        return -SAT;
    } else {
        return input;
    }
}

float PID(SensorStruct *SS) {
    sPollCalc(&lcd);
    SS->yt = inches[SS->sensor]; //left distance
    SS->eto = SS->et; //old error
    SS->et = SS->yt - RT; //new error
    SS->etDelta = SS->et - SS->eto;     //change in error
    SS->proportion = KP * SS->et;
    SS->derivative = KD * SS->etDelta;
    if(SS->sensor == 1){
        SS->ut = satFunc(SS->proportion + SS->derivative);
    }
    else{
        SS->ut = satFunc(-(SS->proportion + SS->derivative));
    }
    return SS->ut;
}

//FUNCTIONS
void wallFollowing(SensorStruct *SS) {
    PID(SS);
    setSpeedsvw(IPS_MAX, leftSS.ut);
}


#endif