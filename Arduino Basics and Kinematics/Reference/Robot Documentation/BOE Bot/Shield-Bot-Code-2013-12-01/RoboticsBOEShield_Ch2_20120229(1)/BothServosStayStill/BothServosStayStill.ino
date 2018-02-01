/*
 Robotics with the BOE Shield – BothServosStayStill
 Generate signals to make the servos stay still for centering.
 */

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left servo signal
Servo servoRight;                            // Declare right servo signal

void setup()                                 // Built in initialization block
{ 
  servoLeft.attach(13);                      // Attach left signal to P13 
  servoRight.attach(12);                      // Attach left signal to P12 

  servoLeft.writeMicroseconds(1500);         // 1.5 ms stay still sig, pin 13
  servoRight.writeMicroseconds(1500);        // 1.5 ms stay still sig, pin 12
}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}

