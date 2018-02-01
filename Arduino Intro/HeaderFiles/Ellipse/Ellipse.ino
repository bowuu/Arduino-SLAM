#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "MyEncoders.h"
#include "MyServos.h"
#include "EllipseParams.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define RED    0x1      //RGB SHIELD
#define GREEN  0x2      //color codes
#define YELLOW 0x3
#define BLUE   0x4
#define VIOLET 0x5
#define TEAL   0x6
#define WHITE  0x7
#define sq(x) ((x)*(x))

void setup() {
    Serial.begin(9600);
    LServo.attach(L_SERVO_PORT);
    RServo.attach(R_SERVO_PORT);
    initEncoders();

    lcd.setBacklight(WHITE);
    lcd.begin(16, 2);
    lcd.print("Task 5 - Ellipse");
    lcd.setCursor(0, 1);
    lcd.print("A:");
    lcd.print(PARAM_a);
    lcd.print(" B:");
    lcd.print(PARAM_b);
    lcd.print(" v:");
    lcd.print(PARAM_V);

    fakeCal();
}

void loop() {
    uint8_t buttons = lcd.readButtons();

    setSpeedsIPS(0, 0);
    lcd.setCursor(0, 0);

    switch (buttons) {
        case BUTTON_SELECT: {
                float v = (float)PARAM_V;
                float vMax = 0.8 * PI * 2.61;

                float x = (float)PARAM_a;
                float y = (float)PARAM_b;
                float k = 2 / (pow((sqrt(1 + 4 * sq(x))), 3));
                float w = k * v;

                setSpeedsvw(v, w);
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
