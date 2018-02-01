bool movementTest();    //declare functions
bool sensorTest();
bool encoderTest();
bool colorSensorTest();

//void movementTestSetup();
void sensorTestSetup();
void encoderTestSetup();
//void colorSensorTestSetup();

#include "Chooser.h"
unsigned int numPrograms     = 4; // the number programs
bool (*programList[])()      = {&movementTest,&sensorTest,&encoderTest,&colorSensorTest}; // array of pointers to functions of length "numPrograms", must return true when done
void (*setupProgramList[])() = {0,&sensorTestSetup,&encoderTestSetup,0}; // array of setup functions for each program, if no setup assign 0
const char * programNames[]  = {"Movement","Sensor","Encoder","colorSensor"}; // array of names of each function

// HW variable declarations
