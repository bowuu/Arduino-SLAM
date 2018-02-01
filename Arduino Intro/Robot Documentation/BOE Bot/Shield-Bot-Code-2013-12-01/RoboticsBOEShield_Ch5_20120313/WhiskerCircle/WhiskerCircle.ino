// Robotics with the BOE Shield - Chapter 5, project 2 – WhiskerCircle
// BOE Shield-Bot navigates a circle of 1 yard diameter.
// Tightens turn if right whisker pressed, or reduces turn if left whisker
// is pressed.

#include <Servo.h>                    // Include servo library
 
Servo servoLeft;                      // Declare left and right servos
Servo servoRight;

int turn;
 
void setup()                          // Built-in initialization block
{ 
  pinMode(7, INPUT);                    // Set right whisker pin to input
  pinMode(5, INPUT);                    // Set left whisker pin to input  

  tone(4, 3000, 1000);                // Play tone for 1 second
  delay(1000);                        // Delay to finish tone

  servoLeft.attach(13);               // Attach left signal to Port 13 
  servoRight.attach(12);              // Attach right signal to Port 12
  
  turn = 0;

//  servoLeft.detach();                 // Stop sending servo signals
//  servoRight.detach(); 
}  
 
void loop()                          // Main loop auto-repeats
{                                    // Nothing needs repeating
  int wLeft = digitalRead(5);
  int wRight = digitalRead(7);
  
  if(wLeft == 0)
  {
    turn -= 10;
  }
  else if(wRight == 0)
  {
    turn += 10;
  } 
  
  // Arc to the right
  servoLeft.writeMicroseconds(1600);  // Left wheel counterclockwise
  servoRight.writeMicroseconds(1438 + turn); // Right wheel clockwise slower
  delay(50);                       // ...for 25.5 seconds
}

