//this program does the same as the basic program but it uses the provided framework (Chooser.h and Chooser.cpp)

#include <Adafruit_RGBLCDShield.h>
#include "Chooser.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

//define programs:
bool functionA();     //program must be of the form bool NAME(); no arguments
void initFunctionA(); //init function must be of the form void NAME(); no arguments
bool functionB();
//void initFunctionB(); //dont want to define init function for B, OK can be done, just define it as 0 in the variables below
bool functionC();
//void initFunctionC();

//the following 4 variables must be defined to use the framework
unsigned int numPrograms     =   2;                                     // the number programs
bool (*programList[])()      = {&functionA, &functionB, &functionC};    // array of pointers to functions of length "numPrograms", must return true when done
void (*setupProgramList[])() = {&initFunctionA, 0, 0};                  // array of setup functions for each program, if no setup assign 0
const char * programNames[]  = {"Option A", "Option B", "Option C"};    // array of names of each function

void setup() {
    Serial.begin(115200 ); //init serial
    lcd.begin(16, 2); //init lcd
    initChooser(&lcd); //initialize chooser program
}

void loop() {
    //to select or cancel programs use select, use the lcd arrows to switch options
    execProgram();//run the framework, selection process is taken care automatically
}

//now implement the functions, you don't need to worry about program logic
void initFunctionA() {
    Serial.print("This function executes only once! when program selected\n");
    Serial.print("Use it to initialize your program if needed\n");
}

bool functionA() {
    Serial.print(millis());
    Serial.print(" ");
    Serial.print("Function A\n");

    //detect when function is done - here press select to go back to the select menu
    if (lcd.readButtons() == BUTTON_SELECT) {
        return true; //return true when done
    }

    delay(100); //could skip the delay if I wanted
    return false; //false means the program is not done yet
}

bool functionB() {
    Serial.print(millis());
    Serial.print(" ");
    Serial.print("Function B\n");

    //detect when function is done - here press select to go back to the select menu
    if (lcd.readButtons() == BUTTON_SELECT) {
        return true; //return true when done
    }

    delay(100); //could skip the delay if I wanted
    return false; //false means the program is not done yet
}

bool functionC() {
    Serial.print(millis());
    Serial.print(" ");
    Serial.print("Function C\n");

    //detect when function is done - here press select to go back to the select menu
    if (lcd.readButtons() == BUTTON_SELECT) {
        return true; //return true when done
    }

    delay(100); //could skip the delay if I wanted
    return false; //false means the program is not done yet
}
