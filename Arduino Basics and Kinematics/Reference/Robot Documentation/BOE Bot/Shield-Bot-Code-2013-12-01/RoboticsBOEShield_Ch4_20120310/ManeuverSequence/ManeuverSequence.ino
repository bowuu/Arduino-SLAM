// Robotics with the BOE Shield - ManeuverSequence
// Move forward, left, right, then backward with an array and the
// maneuver function.

#include <Servo.h>                           // Include servo library

//                Forward    left   right   backward    stop
//         index        0       1       2          3       4
int speedsLeft[]  = {200,    -200,    200,      -200,      0};
int speedsRight[] = {200,     200,   -200,      -200,      0};
int times[]       = {2000,    600,    600,      2000,     -1};
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(13);                      // Attach left signal to P13 
  servoRight.attach(12);                     // Attach right signal to P12

  // Determine number of elements in sequence list.
  int elementCount = sizeof(times) / sizeof(int);

  // Fetch successive elements from each sequence list and feed them 
  // to maneuver function.
  for(int index = 0; index < elementCount; index++)
  {
    maneuver(speedsLeft[index], speedsRight[index], times[index]);
  }
}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
}

void maneuver(int speedLeft, int speedRight, int msTime)
{
  // speedLeft, speedRight ranges: Backward  Linear  Stop  Linear   Forward
  //                               -200      -100......0......100       200
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if(msTime==-1)                                   // if msTime = -1
  {                                  
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();   
  }
  delay(msTime);                                   // Delay for msTime
}

