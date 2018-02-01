#ifndef _CHOOSER_
#define _CHOOSER_

#include "RobotSetup.h"

//declare functions
bool changeParam();
bool lineDetect();
bool mapping();
bool planning();
bool timer(bool (*f)());

void initChooser(Adafruit_RGBLCDShield* lcd); //this function must be called during the setup
void execProgram();

unsigned int numPrograms = 4; // the number programs
bool (*programList[])() = {&changeParam, &lineDetect, &mapping, &planning}; // array of pointers to functions of length "numPrograms", must return true when done
const char *programNames[] = {"Parameters", "Line Detection", "Mapping", "Planning"}; // array of names of each function
const char *paramNames[] = {"Origin          ", "GOAL!!!!!!!!!!!!", "Orientation     ", "Exit            "}; // array of names of each parameter

unsigned int programSelector = 0;
bool choosingProgram = true;


Adafruit_RGBLCDShield* cLcd;

void initChooser(Adafruit_RGBLCDShield* _lcd) {
    cLcd = _lcd;
}

bool chooseProgram() {
    static bool titleShown = false;

    if (!titleShown) {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Which Program?");
        lcd.setCursor(1, 1);
        lcd.print(programNames[programSelector]);
        titleShown = true;
        delay(DEL_AMT); //avoid old button still being pressed
    }
    button = lcd.readButtons();

    if (button & BUTTON_SELECT) {
        lcd.setCursor(0, 0);
        lcd.print("Start          ");
        lcd.setBacklight(RED);
        delay(DEL_AMT * 5);
        titleShown = false;
        lcd.setBacklight(BLUE);
        lcd.setCursor(0, 0);
        lcd.print("Run       ");
        lcd.setCursor(1, 1);
        lcd.print(programNames[programSelector]);
        return false; //indicate finished choosing program
    } else if (button & (BUTTON_LEFT  | BUTTON_RIGHT)) {
        programSelector += (button & BUTTON_LEFT ? numPrograms - 1 : 1 ) ;
        programSelector %= numPrograms;
        for (int i = 0; i < 16; ++i)
        {
            lcd.setCursor(i, 1);
            lcd.print(" ");
        }
        lcd.setCursor(1, 1);
        lcd.print(programNames[programSelector]);
        delay(DEL_AMT);
    }
    return true;
}

bool changeParam() {
    short low, high, param = 0, value;
    button = 0;
    //Choose which parameter to set
    while (1) {
        lcd.clear();
        lcd.setBacklight(GREEN);
        lcd.setCursor(0, 0);
        lcd.print("Param?");
        while (!(button & BUTTON_SELECT)) {
            button = lcd.readButtons();
            delay(DEL_AMT);
            if (button & BUTTON_LEFT) {
                param == 0 ? param = 3 : param -= 1;
            }
            else if (button & BUTTON_RIGHT) {
                param == 3 ? param = 0 : param += 1;
            }
            lcd.setCursor(0, 1);
            lcd.print(paramNames[param]);
        }
        //Exit Menu
        if (param == 3) return true;
        button = 0;
        delay(DEL_AMT);
        value = robotState.params[param];
        lcd.clear();
        lcd.setBacklight(YELLOW);
        lcd.setCursor(0, 0);
        lcd.print(paramNames[param]);
        //Choose value of parameter
        while (!(button & BUTTON_SELECT)) {
            //if the value is starting or ending location, value = 0-16
            //if it is orientation, value = 0-3
            if(param == 2){
                low = 0;
                high = 3;
            }
            else{
                low = 1;
                high = 16;
            }
            button = lcd.readButtons();
            delay(DEL_AMT);
            if (button & BUTTON_LEFT) {
                value == low ? value = high : value -= 1;
            }
            else if (button & BUTTON_RIGHT) {
                value == high ? value = low : value += 1;
            }
            robotState.params[param] = value;  
            if(param == 0){ //Set curNode to origin
                robotState.curNode = robotState.params[0];
            }          
            lcd.print("  ");
            lcd.setCursor(0, 1);

            param == 2 ? lcd.print(robotState.orientNames[robotState.params[2]]) : lcd.print(value);
        }
        button = lcd.readButtons();
        delay(DEL_AMT);
    }
    return true;
}

void execProgram() {
    lcd.setBacklight(VIOLET);
    choosingProgram = choosingProgram ? chooseProgram() : programList[programSelector]();
}

#endif //_CHOOSER_