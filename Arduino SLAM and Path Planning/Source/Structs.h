#ifndef _STRUCTS_
#define _STRUCTS_

#include "Arduino.h"


struct NodeStruct {
    bool explored = 0, visited = 0;
    unsigned short distance = 16;
    bool walls[4] = {0};
    NodeStruct* prevNode = NULL;
};
typedef struct NodeStruct NodeStruct;

struct ColorStruct {
    int red;
    int blue;
    int green;
};

typedef struct ColorStruct ColorStruct;

struct RobotStateStruct {
    short curNode = 1;
    short params[4] = {15, 16, 3, 0}; // 0 = origin, 1 = goal, 2 = orientation 
    //Orientations
    //0 = n, 1 = e, 2 = s, 3 = w
    const char *orientNames[4] = {"N", "E", "S", "W"};
    NodeStruct nodes[17];
};
typedef struct RobotStateStruct RobotStateStruct;

struct SensorStruct{
    unsigned short sensor;
    float yto;
    float yt;           //distance from robot to goal
    float et = 0;
    float eto = 0;
    float etDelta = 0;
    float etSum;
    float ut;   
    float derivative;        //control signal
    float proportion;
};
typedef struct SensorStruct SensorStruct;

#endif //_STRUCTS_

