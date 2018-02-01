

#ifndef __COLOR_SENSOR__
#define __COLOR_SENSOR__

// COLOR SENSOR
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8


void initColorSensor();

//I will assume rgbs in the range 0-1
void getColor(float rgb[3],int samples);

void toHSI(float rgb[3],float hsi[3]);

#endif
