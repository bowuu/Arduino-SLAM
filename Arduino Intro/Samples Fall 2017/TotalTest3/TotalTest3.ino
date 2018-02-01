#include "robotBasic.h"
#include "main.h"

void setup(){  
  Serial.begin(9600);
  setUpRobot();
  initChooser(&lcd);
}

void loop(){
  execProgram();
}
