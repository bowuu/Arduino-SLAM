/*
 * Robotics with the BOE Shield - HaltUnderBrightLight
 * Display voltage of phototransistor circuit output connected to A3 in
 * the serial monitor.
 */

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
 
void setup()                                 // Built-in initialization block
{
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone
  
  servoLeft.attach(13);                      // Attach left signal to pin 13 
  servoRight.attach(12);                     // Attach right signal to pin 12
 
  servoLeft.writeMicroseconds(1700);         // Full speed forward
  servoRight.writeMicroseconds(1300);
}

void loop()                                  // Main loop auto-repeats
{
  if(volts(A3) > 3.5)                        // If A3 voltage greater than 2
  {
    servoLeft.detach();                      // Stop servo signals
    servoRight.detach();   
  }
}

float volts(int adPin)                       // Measures volts at adPin 
{                                            // Returns floating point voltage
 return float(analogRead(adPin)) * 5.0 / 1024.0; 
}   

