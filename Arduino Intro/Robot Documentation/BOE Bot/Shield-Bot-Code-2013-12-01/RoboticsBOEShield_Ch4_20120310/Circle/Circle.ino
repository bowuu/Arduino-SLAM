// Robotics with the BOE Shield - Chapter 4, project 2 - Circle
// BOE Shield-Bot navigates a circle of  1 yard diameter.

#include <Servo.h>                    // Include servo library
 
Servo servoLeft;                      // Declare left and right servos
Servo servoRight;
 
void setup()                          // Built-in initialization block
{ 
  servoLeft.attach(2);               // Attach left signal to pin 13 
  servoRight.attach(3);              // Attach right signal to pin 12

  // Arc to the right
  servoLeft.writeMicroseconds(1600);  // Left wheel counterclockwise
  servoRight.writeMicroseconds(1438); // Right wheel clockwise slower
  delay(2000);                       // ...for 25.5 seconds
}  
 
void loop()                          // Main loop auto-repeats
{                                    // Nothing needs repeating
}

