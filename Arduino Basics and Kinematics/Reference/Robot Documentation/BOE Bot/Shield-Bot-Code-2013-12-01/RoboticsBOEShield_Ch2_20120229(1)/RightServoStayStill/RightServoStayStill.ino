/*
 Robotics with the BOE Shield – RightServoStayStill
 Transmit the center or stay still signal on pin 12 for center adjustment.
 */

#include <Servo.h>                           // Include servo library
 
Servo servoRight;                            // Declare right servo

void setup()                                 // Built-in initialization block
{ 
  servoRight.attach(12);                     // Attach right signal to pin 12
  servoRight.writeMicroseconds(1500);        // 1.5 ms stay still signal
}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}

