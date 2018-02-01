


#include "ColorSensor.h"
#include <Arduino.h>


int testGlobalVariable = 4;

namespace{ //this is a nameless namespace
  //add variables only visible to this file
  int testVariable = 3;
}

void initColorSensor(){
  
  Serial.println(testVariable);
  
}

//I will assume rgbs in the range 0-1
void getColor(float rgb[3],int samples){
  
  
}

//assume rgb values in the range 0-1
void toHSI(float rgb[3],float hsi[3]){
  /*
   * i = gray level = (r+g+b)/3
   * s = saturation = 1-3*min(r,g,b)/(r+g+b)  // make sure not to divide by 0
   * theta = arccos ( 0.5 *((r-g)+(r-b))/sqrt((r-g)*(r-g)+(r-b)*(g-b)) //make sure not to divide by 0
   * if b > g then : h = 2*pi - theta
   * else:  h = theta
   */

  
  
}
