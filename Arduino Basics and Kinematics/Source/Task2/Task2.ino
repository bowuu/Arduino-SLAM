#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "MyEncoders.h"
#include "MyServos.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define RED    0x1      //RGB SHIELD
#define GREEN  0x2      //color codes
#define YELLOW 0x3
#define BLUE   0x4
#define VIOLET 0x5
#define TEAL   0x6
#define WHITE  0x7

void setup() {
    Serial.begin(9600);
    LServo.attach(L_SERVO_PORT);
    RServo.attach(R_SERVO_PORT);
    setSpeeds(0, 0);

    lcd.begin(16, 2);                     //SET UP LCD DISPLAY
    lcd.print("Lab 1-Kinematics");
    lcd.setCursor(1, 6);
    lcd.print("Blaine - Boyang");
    lcd.setBacklight(WHITE);
    
    initEncoders();
    
    calibrateSpeeds();
    delay(1000);
    setSpeeds(0, 0);
}

void loop() {
}

