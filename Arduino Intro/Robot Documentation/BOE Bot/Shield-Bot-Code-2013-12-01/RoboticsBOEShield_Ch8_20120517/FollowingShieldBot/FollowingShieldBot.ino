/*
 * Robotics with the BOE Shield - FollowingShieldBot
 * Use proportional control to maintain a fixed distance between
 * BOE Shield-Bot and object in front of it.
 */ 

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

const int setpoint = 2;                      // Target distances
const int kpl = -50;                         // Proportional control constants 
const int kpr = -50;
 
void setup()                                 // Built-in initialization block
{ 
  pinMode(10, INPUT);  pinMode(9, OUTPUT);   // Left IR LED & Receiver
  pinMode(3, INPUT);  pinMode(2, OUTPUT);    // Right IR LED & Receiver

  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  servoLeft.attach(13);                      // Attach left signal to pin 13 
  servoRight.attach(12);                     // Attach right signal to pin 12
}  
 
void loop()                                  // Main loop auto-repeats
{
  int irLeft = irDistance(9, 10);            // Measure left distance
  int irRight = irDistance(2, 3);            // Measure right distance
  
  // Left and right proportional control calculations
  int driveLeft = (setpoint - irLeft) * kpl;     
  int driveRight = (setpoint - irRight) * kpr;
  
  maneuver(driveLeft, driveRight, 20);       // drive levels set speeds
} 

// IR distance measurement function

int irDistance(int irLedPin, int irReceivePin)
{  
  int distance = 0;
  for(long f = 38000; f <= 42000; f += 1000) {
    distance += irDetect(irLedPin, irReceivePin, f);
  }
  return distance;
}

// IR Detection function

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
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

