//https://codeshare.io/arLvBz

#ifndef _COLOR_SENSOR_
#define _COLOR_SENSOR_

#include "RobotSetup.h"

#define NUMREADS 5

ColorStruct CS;
void printColors();
// void displayPrint();

bool readColor() {
    //printColors();
    bool linePassed = false;
    int rSum = 0;
    int bSum = 0;
    int gSum = 0;
    int lastColor = 2; //0 == Red, 1 == Blue, 2 == Green

    for (int i = 0; i < NUMREADS; i++) {
        // Setting red filtered photodiodes to be read
        digitalWrite(S2, LOW);
        digitalWrite(S3, LOW);
        rSum += pulseIn(sensorOut, LOW);

        // Setting Green filtered photodiodes to be read
        digitalWrite(S2, HIGH);
        digitalWrite(S3, HIGH);
        gSum += pulseIn(sensorOut, LOW);

        // Setting Blue filtered photodiodes to be read
        digitalWrite(S2, LOW);
        digitalWrite(S3, HIGH);
        bSum += pulseIn(sensorOut, LOW);
    }
    CS.red = rSum / NUMREADS;
    CS.green = gSum / NUMREADS;
    CS.blue = bSum / NUMREADS;

    if (CS.red > 110 && CS.red < 220 && CS.green > 70 && CS.green < 170 && CS.blue > 40 && CS.blue < 180){
        lcd.setBacklight(BLUE);
        if(lastColor != 1){
            if (robotState.params[2] == 0) { //facing north going over red blue line
                robotState.curNode -= 4;
            } 
            if (robotState.params[2] == 2) { //facing south going over blue line
                robotState.curNode += 4;
            }
        //displayPrint();
        linePassed = true;
        lastColor = 1;
        }

    } 
    else if (CS.red > 20 && CS.red < 110 && CS.green > 130 && CS.green < 220 && CS.blue > 90 && CS.blue < 180) {
    lcd.setBacklight(RED);
        if(lastColor != 0)
        {
            if (robotState.params[2] == 1) { //facing east going over red line
                robotState.curNode += 1;
            } 
            if (robotState.params[2] == 3) { //dacing west going over red line
                robotState.curNode -= 1;
            }
                //displayPrint();
                linePassed = true;
                lastColor = 0;
        }

    }     

    else {
        lcd.setBacklight(WHITE);
        linePassed = false;
        lastColor = 2;
    }    
    return linePassed;
}


void displayPrint() {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(robotState.curNode);
    //delay(200);
}

void printColors() {
   lcd.setCursor(0, 1);
   lcd.print("                ");          //This ensures correct LCD output

   lcd.setCursor(0, 1);
   lcd.print("R");
   lcd.print(CS.red);

   lcd.setCursor(6, 1);
   lcd.print("G");
   lcd.print(CS.green);

   lcd.setCursor(12, 1);
   lcd.print("B");
   lcd.print(CS.blue);
}

#endif //_COLOR_SENSOR_
