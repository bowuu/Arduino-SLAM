// Robotics with the BOE Shield - StartAndStopWithRamping
// Ramp up, go forward, ramp down.

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
 
void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(13);                      // Attach left signal to P13 
  servoRight.attach(12);                     // Attach right signal to P12
  
  for(int speed = 0; speed <= 100; speed += 2) // Ramp up to full speed.
  {
    servoLeft.writeMicroseconds(1500+speed);   // us = 1500,1502,...1598,1600
    servoRight.writeMicroseconds(1500-speed);  // us = 1500,1498,...1402,1400
    delay(20);                                 // 20 ms at each speed
  } 
   
  delay(1500);                                 // Full speed for 1.5 seconds

  for(int speed = 100; speed >= 0; speed -= 2) // Ramp from full speed to stop 
  {
    servoLeft.writeMicroseconds(1500+speed);   // us = 1600,1598,...1502,1500
    servoRight.writeMicroseconds(1500-speed);  // us = 1400,1402,...1498,1500
    delay(20);                                 // 20 ms at each speed
  } 
  
  servoLeft.detach();                          // Stop sending servo signals
  servoRight.detach(); 
}

void loop()                                    // Main loop auto-repeats
{                                              // Empty, nothing to repeat
}

