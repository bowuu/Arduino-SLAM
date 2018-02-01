/*
 Robotics with the BOE Shield – ServosOppositeDirections
 Generate a servo full speed counterclockwise signal with pin 13 and 
 full speed clockwise signal with pin 12.
 */

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left servo signal
Servo servoRight;                            // Declare right servo signal

void setup()                                 // Built in initialization block
{ 
  servoLeft.attach(13);                      // Attach left signal to P13 
  servoRight.attach(12);                     // Attach right signal to P12 

  servoLeft.writeMicroseconds(1700);         // 1.7 ms -> counterclockwise
  servoRight.writeMicroseconds(1300);        // 1.3 ms -> clockwise
}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}

