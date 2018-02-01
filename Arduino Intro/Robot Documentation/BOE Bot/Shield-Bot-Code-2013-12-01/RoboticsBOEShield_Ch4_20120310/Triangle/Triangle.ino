// Robotics with the BOE Shield - Chapter 4, project 2 - Triangle
// BOE Shield-Bot navigates a triangle with 1 yard sides and 120
// degree angles.  Go straight 1 yard, turn 120 degrees, repeat 3 times

#include <Servo.h>                    // Include servo library
 
Servo servoLeft;                      // Declare left and right servos
Servo servoRight;
 
void setup()                          // Built-in initialization block
{ 
  tone(4, 3000, 1000);                // Play tone for 1 second
  delay(1000);                        // Delay to finish tone

  servoLeft.attach(13);               // Attach left signal to P13 
  servoRight.attach(12);              // Attach right signal to P12

  for(int index = 1; index <= 3; index++)
  {
    // Full speed forward
    servoLeft.writeMicroseconds(1700);  // Left wheel counterclockwise
    servoRight.writeMicroseconds(1300); // Right wheel clockwise slower
    delay(5500);                        // ...for 5.5 seconds
    
    // Turn left 120 degrees
    servoLeft.writeMicroseconds(1300);  // Left wheel counterclockwise
    servoRight.writeMicroseconds(1300); // Right wheel clockwise slower
    delay(700);   
  }
  servoLeft.detach();                 // Stop sending servo signals
  servoRight.detach(); 
}  
 
void loop()                          // Main loop auto-repeats
{                                    // Nothing needs repeating
}

