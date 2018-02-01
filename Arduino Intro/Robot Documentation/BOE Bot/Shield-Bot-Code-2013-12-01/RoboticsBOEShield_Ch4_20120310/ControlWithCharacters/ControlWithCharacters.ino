// Robotics with the BOE Shield – ControlWithCharacters
// Move forward, left, right, then backward for testing and tuning.

#include <Servo.h>                           // Include servo library
 
char maneuvers[] = "fffffffffflllrrrbbbbbbbbbbs";

Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(13);                      // Attach left signal to P13 
  servoRight.attach(12);                     // Attach right signal to P12

  // Parse maneuvers and feed each successive character to the go function.
  int index = 0;
  do
  {
    go(maneuvers[index]);
  } while(maneuvers[index++] != 's');}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}

void go(char c)                              // go function
{
  switch(c)                                  // Switch to code based on c
  {
    case 'f':                                // c contains 'f'
      servoLeft.writeMicroseconds(1700);     // Full speed forward
      servoRight.writeMicroseconds(1300);
      break;
    case 'b':                                // c contains 'b' 
      servoLeft.writeMicroseconds(1300);     // Full speed backward
      servoRight.writeMicroseconds(1700);
      break;
    case 'l':                                // c contains 'l' 
      servoLeft.writeMicroseconds(1300);     // Rotate left in place
      servoRight.writeMicroseconds(1300);
      break;
    case 'r':                                // c contains 'r' 
      servoLeft.writeMicroseconds(1700);     // Rotate right in place
      servoRight.writeMicroseconds(1700);
      break;
    case 's':                                // c contains 's' 
      servoLeft.writeMicroseconds(1500);     // Stop
      servoRight.writeMicroseconds(1500);
      break;
  }
  delay(200);                                 // Execute for 0.2 seconds
}

