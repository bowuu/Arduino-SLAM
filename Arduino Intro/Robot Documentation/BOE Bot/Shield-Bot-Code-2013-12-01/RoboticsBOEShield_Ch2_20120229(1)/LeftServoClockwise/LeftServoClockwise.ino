/*
 Robotics with the BOE Shield – LeftServoClockwise
 Generate a servo full speed clockwise signal on digital pin 13.
 */

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left servo

void setup()                                 // Built in initialization block
{ 
  servoLeft.attach(13);                      // Attach left signal to pin 13 
  servoLeft.writeMicroseconds(1300);         // 1.3 ms full speed clockwise
}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}

