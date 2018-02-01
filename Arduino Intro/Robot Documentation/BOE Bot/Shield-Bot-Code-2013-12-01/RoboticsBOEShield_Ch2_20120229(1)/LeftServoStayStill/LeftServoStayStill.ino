/*
 Robotics with the BOE Shield – LeftServoStayStill
 Generate signal to make the servo stay still for centering.
 */

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left servo

void setup()                                 // Built in initialization block
{ 
  servoLeft.attach(13);                      // Attach left signal to pin 13 
  servoLeft.writeMicroseconds(1500);         // 1.5 ms stay still signal
}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}

