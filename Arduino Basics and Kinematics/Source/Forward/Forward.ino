#include <Adafruit_RGBLCDShield.h>
#include "MyEncoders.h"
#include "MyServos.h"
#include "ForwardParams.h"

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
    lcd.print("Task 3 - Forward");
    lcd.setCursor(0, 1);
    lcd.print("Inch:");
    lcd.print(PARAM_X);
    lcd.print(" Sec:");
    lcd.print(PARAM_Y);

    fakeCal();
}

void loop() {
    float ips = (float)PARAM_X / PARAM_Y;
    float ipsMax = 0.8 * PI * 2.61;
    float tmpLeft = 0, tmpRight = 0;

    uint8_t buttons = lcd.readButtons();

    setSpeedsIPS(0, 0);
    lcd.setCursor(0, 0);

    switch (buttons) {
        case BUTTON_SELECT: {
                if (ips <= ipsMax) {
                    lcd.print("Select          ");

                    setSpeedsIPS(ips, ips);
                    Serial.print("\nips: ");
                    Serial.print(ips);
                    Serial.print("\tipsMax: ");
                    Serial.print(ipsMax);

                    while (tmpLeft <= PARAM_X || tmpRight <= PARAM_X) {
                        setSpeedsIPS(ips, ips);
                        tmpLeft = (float)lEncCount / 32.0 * 8.2;        //calculate from encoder to inch
                        tmpRight =  (float)rEncCount / 32.0 * 8.2;

                        Serial.print("\ntmpLeft: ");
                        Serial.print(tmpLeft);
                        Serial.print("\ttmpRight: ");
                        Serial.print(tmpRight);

                        if (tmpLeft > PARAM_X || tmpRight > PARAM_X) {
                            setSpeedsIPS(0, 0);
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
                lcd.print("Right:          ");
                break;
        }
    }
}
