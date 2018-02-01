#ifndef _SENSOR_STRUCT_
#define _SENSOR_STRUCT_
struct SensorStruct{
    unsigned short sensor;
    unsigned short index;
    unsigned long now;
    unsigned long past;
    unsigned short tDelta;
    float yt;           //distance from robot to goal
    float et = 0;
    float eto = 0;
    float etDelta = 0;
    float etSum;
    float ut;           //control signal
    float proportion;
    float integral;
    float derivative;
    float distanceHigh;
    float distanceLow;
};
typedef struct SensorStruct SensorStruct;
#endif //_SENSOR_STRUCT_