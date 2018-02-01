#include <Adafruit_RGBLCDShield.h>
#include <Arduino.h>
#include "MyServos.h"
#include "MySharpSensor.h"

#define RED    0x1      //RGB SHIELD
#define GREEN  0x2      //color codes
#define YELLOW 0x3
#define BLUE   0x4
#define VIOLET 0x5
#define TEAL   0x6
#define WHITE  0x7
#define DELAYAMT 150    //for button
#define KI .1
#define KD 2.5
#define IPS_MAX 6.5       //inches/s max speed forward
#define RT 5.0          //Goal distance

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
int i = 3;
float kpArray[] = {.2, .6, .9, 1.2, 1.5, 2.0};
float kp = kpArray[i];
float temp, rt = RT;
//float median;
uint8_t button;
//PROTOTYPES
float satFunc(float input);
float wallDistance(SensorStruct *SS);
float PID(SensorStruct *SS);
void menu();

void setup() {
    delay(50);              //Ensure sensors have stable output.
    frontSS.sensor = 0;
    for(int i=0; i < 5; i++){
        takeNewMeasurement(&frontSS);
        takeNewMeasurement(&rightSS);
    }
    LServo.attach(L_SERVO_PORT);
    RServo.attach(R_SERVO_PORT);
    initEncoders();
    lcd.setBacklight(WHITE);
    lcd.begin(16, 2, 1);
    lcd.print("Lab 2 - Distance");
    lcd.setCursor(0, 1);
    lcd.print("Mike  --  Boyang");
}

void loop() {
    menu();
}

void menu() {
    button = lcd.readButtons();
    lcd.setCursor(0, 0);
    lcd.print("Wall");
    switch (button) {
        case BUTTON_SELECT: {
            button = 0;   
            setSpeedsIPS(0, 0);
        }
        case BUTTON_UP: {
            button = 0;   //ADJUST KP
            while (button != BUTTON_SELECT) {
                lcd.setCursor(0, 0);
                lcd.print("kp =         ");
                lcd.setCursor(13, 0);
                kp = kpArray[i];
                lcd.print(kpArray[i]);
                delay(DELAYAMT);
                button = lcd.readButtons();
                if (button == BUTTON_UP)
                    i++;
                if (i == 6)
                    i = 0;
            }
            break;
        }
        case BUTTON_DOWN: {  //WALL DISTANCE
            button = 0;
            frontSS.etSum = 0;
            frontSS.integral = 0;
            frontSS.et = 0;
            frontSS.eto = 0;
            frontSS.yt = 0;
            rt = RT;
            lcd.setCursor(0, 0);
            lcd.print("Wall Distance  ");
            int output;
            int count;
            frontSS.past = millis();
            while (button != BUTTON_SELECT) {
                button = lcd.readButtons();
                wallDistance();
            }
            break;
        }
    }
}

float satFunc(float input) {
    if (input > 6) {
        return 6;
    } else if (input < -6) {
        return -3;
    } else {
        return input;
    }
}

float PID(SensorStruct *SS) {
    SS->yt = sPollCalc(SS); //actual distance
    SS->et = SS->yt - rt; //error
    SS->proportion = kp * SS->et;
    SS->ut = satFunc(SS->proportion);
    return SS->ut;
}

float wallDistance(SensorStruct *SS) {
    float output = PID(SS);
    return output;
}

void wallFollowing() {      //Use right and front short sensors
    //front sensor loop. likely needs changes for out of range distances
    if(frontSS.yt < RT) {
        setSpeedsIPS(-IPS_MAX, IPS_MAX);
    }   
    else{
        setSpeedsvw(IPS_MAX, -rightSS.ut);
    }
}
