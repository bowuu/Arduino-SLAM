


#include "Chooser.h"


unsigned int programSelector = 0;
bool choosingProgram = true;

Adafruit_RGBLCDShield* cLcd;

#define BLUE 0x4
#define RED 0x1

void initChooser(Adafruit_RGBLCDShield* _lcd){
  cLcd = _lcd;
}

bool chooseProgram(){

  static bool titleShown = false;

  if(!titleShown){
    cLcd->clear();
    cLcd->setBacklight(BLUE);
    cLcd->setCursor(1,0);
    cLcd->print("Choosing...");
    cLcd->setCursor(1,1);
    cLcd->print(programNames[programSelector]);
    titleShown = true;
    delay(1000); //avoid old buttons still being pressed
  }

  uint8_t buttons = cLcd->readButtons();

  if (  buttons & BUTTON_SELECT ){
    
    cLcd->setCursor(0,0);
    cLcd->print("Starting...");
    cLcd->setBacklight(RED);
    delay(1000);
    titleShown = false;

    //program chosen, execute setup function if not null
    if(setupProgramList[programSelector] != 0 ) setupProgramList[programSelector]();

    cLcd->setBacklight(BLUE);
    cLcd->setCursor(0,0);
    cLcd->print("Running....");
    return false; //indicate finished choosing program
    
  } else if (  buttons & (BUTTON_LEFT  | BUTTON_RIGHT )) {
    
    programSelector += (buttons & BUTTON_LEFT ? numPrograms-1 : 1 ) ;
    programSelector %= numPrograms;

    cLcd->setCursor(0,1);
    cLcd->print("                ");
    cLcd->setCursor(1,1);
    cLcd->print(programNames[programSelector]);
    delay(100);

    
  } 

  return true; // I'm still choosing the program
}

void execProgram(){
  choosingProgram = choosingProgram ? chooseProgram() : programList[programSelector]();  
}


