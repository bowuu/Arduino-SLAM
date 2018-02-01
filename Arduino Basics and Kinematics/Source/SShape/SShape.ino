#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "MyEncoders.h"
#include "MyServos.h"
#include "SShapeParams.h"

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
    initEncoders();

    lcd.setBacklight(WHITE);
    lcd.begin(16, 2);
    lcd.print("Task 4 - SShape");
    lcd.setCursor(0, 1);
    lcd.print("R:");
    lcd.print(PARAM_R1);
    lcd.print(" Sec:");
    lcd.print(PARAM_Y);

    fakeCal();
}

void loop() {
    float R = (float)PARAM_R1;
    float T = (float)PARAM_Y;
    float V = (float) PI * R / T;
    float vMax = 0.8 * (float) PI * 2.61;
    float W = V / R;

    float dist = (float) PI * 2.0 * R;
    float tmpLeft = 0, tmpRight = 0;

    uint8_t buttons = lcd.readButtons();

    setSpeedsIPS(0, 0);
    lcd.setCursor(0, 0);

    switch (buttons) {
        case BUTTON_SELECT: {
                if (V <= vMax) {
                    lcd.print("Semicircle 1    ");

                    Serial.print("\nV: ");
                    Serial.print(V);
                    Serial.print("\tvMax: ");
                    Serial.print(vMax);

                    while (tmpLeft <= dist || tmpRight <= dist) {
                        setSpeedsvw(V, -W);
                        tmpLeft = (float)lEncCount / 32.0 *  8.2;       //calculate from encoder to inch
                        tmpRight =  (float)rEncCount / 32.0 * 8.2;
                        Serial.print("\ntmpLeft: ");
                        Serial.print(tmpLeft);
                        Serial.print("\ttmpRight: ");
                        Serial.print(tmpRight);
                        delay(100);
                        if (tmpLeft > dist || tmpRight > dist) {
                            setSpeedsIPS(0, 0);
                            resetCounts();
                            break;
                        }
                    }
                } else {
                    lcd.print("Speed too fast!!");
                }
                break;
        } case BUTTON_LEFT: {
                lcd.print("Left: Reset     ");
                resetCounts();
                break;
        } case BUTTON_DOWN: {
                lcd.print("Down: Calibrate ");
                calibrateSpeeds();
                lcd.setCursor(0, 0);
                lcd.print("Calibration Done");
                break;
        } case BUTTON_UP: {
                lcd.print("Up: Fake Cal    ");
                fakeCal();
                lcd.setCursor(0, 0);
                lcd.print("Fake Cal Done   ");
                break;
        } case BUTTON_RIGHT: {
                if (V <= vMax) {
                    lcd.print("Semicircle 2    ");

                    Serial.print("\nV: ");
                    Serial.print(V);
                    Serial.print("\tvMax: ");
                    Serial.print(vMax);

                    while (tmpLeft <= dist || tmpRight <= dist) {
                        setSpeedsvw(V, W);
                        tmpLeft = (float)lEncCount / 32.0 *  8.2;       //calculate from encoder to inch
                        tmpRight =  (float)rEncCount / 32.0 * 8.2;
                        Serial.print("\ntmpLeft: ");
                        Serial.print(tmpLeft);
                        Serial.print("\ttmpRight: ");
                        Serial.print(tmpRight);
                        delay(100);
                        if (tmpLeft > dist || tmpRight > dist) {
                            setSpeedsIPS(0, 0);
                            resetCounts();
                            break;
                        }
                    }
                } else {
                    lcd.print("Speed too fast!!");
                }
                break;
            }
    }
}
