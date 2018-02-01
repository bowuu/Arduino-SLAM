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
#define KD 2
#define IPS_MAX 3       //inches/s max speed forward
#define RT 4.0          //Goal distance

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
int i = 2;
float KPArray[] = {.2, .6, .9, 1.2, 1.5, 2.0};
float KP = KPArray[i];
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
    Serial.begin(115200);
    frontSS.sensor = 0;
    rightSS.sensor = 2;
    takeNewMeasurement(&frontSS);
    takeNewMeasurement(&rightSS);
    LServo.attach(L_SERVO_PORT);
    RServo.attach(R_SERVO_PORT);
    initEncoders();
    lcd.setBacklight(WHITE);
    lcd.begin(16, 2, 1);
    lcd.print("Lab 2 - Distance");
    lcd.setCursor(0, 1);
    lcd.print("Mike  --  Boyang");
    setSpeedsIPS(0,0);
}

void loop() {
    menu();
}

void menu() {
    button = lcd.readButtons();
    lcd.setCursor(0, 0);
    lcd.print("Main Menu         ");
    switch (button) {
        case BUTTON_SELECT: {
                button = 0;
                setSpeedsIPS(0, 0);
                calibrateSpeeds();
                break;
            }
        case BUTTON_UP: {
                button = 0;   //ADJUST KP
                while (button != BUTTON_SELECT) {
                    lcd.setCursor(0, 0);
                    lcd.print("KP =         ");
                    lcd.setCursor(13, 0);
                    KP = KPArray[i];
                    lcd.print(KPArray[i]);
                    delay(DELAYAMT);
                    button = lcd.readButtons();
                    if (button == BUTTON_UP)
                        i++;
                    if (i == 6)
                        i = 0;
                }
                break;
            }
        case BUTTON_LEFT: {   //WALL FOLLOWING
                button = 0;
                delay(DELAYAMT);
                rightSS.etSum = 0;
                rightSS.integral = 0;
                rightSS.et = 0;
                rightSS.eto = 0;
                rightSS.yt = 0;
                lcd.setCursor(0, 0);
                lcd.print("Wall Following ");
                while (button != BUTTON_LEFT) {
                    button = lcd.readButtons();
                    PID(&frontSS);
                    PID(&rightSS);
                    wallFollowing();

                }
                delay(DELAYAMT);
                button = 0;
                break;
            }
            case BUTTON_RIGHT: { 
                calibrateSpeeds();
                setSpeedsIPS(0,0);
                break;
            }
    }
}
float satFunc(float input) {
    if (input > 2) {
        return 2;
    } else if (input < -2) {
        return -2;
    } else {
        return input;
    }
}

float PID(SensorStruct *SS) {
    SS->yt = sPollCalc(SS); //actual distance
    SS->eto = SS->et; //old error
    SS->et = SS->yt - rt; //new error
    SS->etDelta = SS->et - SS->eto;     //change in error
    SS->proportion = KP * SS->et;
    SS->integral = KI * SS->etSum;
    SS->derivative = KD * SS->etDelta;
    SS->ut = satFunc(SS->proportion);
    //SS->ut = satFunc(SS->proportion + SS->derivative);
    //SS->ut = satFunc(SS->proportion + SS->integral + SS->derivative);
    return SS->ut;
}

float wallDistance(SensorStruct *SS) {
    float output = PID(SS);
    return output;
}

void wallFollowing() {      //Use right and front short sensors
    //front sensor loop. likely needs changes for out of range distances
    if (frontSS.yt < RT - 1) {
        setSpeedsIPS(-IPS_MAX, IPS_MAX);
        lcd.setBacklight(RED);
    }
    else {
        setSpeedsvw(IPS_MAX, -rightSS.ut);
        lcd.setBacklight(WHITE);
        lcd.setCursor(0, 0);
        lcd.print(rightSS.yt);
    }
}
