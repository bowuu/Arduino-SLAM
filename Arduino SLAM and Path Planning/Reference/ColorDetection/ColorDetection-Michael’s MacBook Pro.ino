#include "ColorSensor.h"

//int testGlobalVariable=5; //already defined in ColorSensor.cpp uncomment to see error

void setup(){

  Serial.begin(115200);
  initColorSensor(); 
//  Serial.print(testGlobalVariable); //cant access this variable, uncomment to see error
}


void loop(){

  
}

