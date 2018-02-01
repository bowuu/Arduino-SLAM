/*
 Robotics with the BOE Shield – Chapter 3, Project 1
*/

#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left servo signal
Servo servoRight;                            // Declare right servo signal

void setup()                                 // Built in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone
  
  Serial.begin(9600);                        // Set data rate to 9600 bps
  servoLeft.attach(13);                      // Attach left signal to P13 
}  
 
void loop()                                  // Main loop auto-repeats
{ 

  // Loop counts with pulseWidth from 1375 to 1625 in increments of 25.

  for(int pulseWidth = 1375; pulseWidth <= 1625; pulseWidth += 25)
  {
    Serial.print("pulseWidth = ");           // Display pulseWidth value
    Serial.println(pulseWidth);
    Serial.println("Press a key and click"); // User prompt
    Serial.println("Send to start servo...");

    while(Serial.available() == 0);          // Wait for character
    Serial.read();                           // Clear character

    Serial.println("Running...");
    servoLeft.writeMicroseconds(pulseWidth);   // Pin 13 servo speed = pulse
    delay(6000);                               // ..for 6 seconds 
    servoLeft.writeMicroseconds(1500);         // Pin 13 servo speed = stop
    tone(4, 4000, 75);                         // Test complete
  }
}
