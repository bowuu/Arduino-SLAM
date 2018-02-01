/*
 * Robotics with the BOE Shield - Chapter 6, Project 1
 * Chirp when light is above threshold.  Will require updating value of
 * threshold & retesting under bright light to get to the right value.
 */

void setup()                         // Built-in initialization block
{
  tone(4, 3000, 1000);               // Play tone for 1 second
  delay(1000);                       // Delay to finish tone
}

void loop()                          // Main loop auto-repeats
{
  if(volts(A3) > 3.5)                 // If A3 voltage greater than 3.5
  {
    tone(4, 4000, 50);               // Start chirping
    delay(100);   
  }
}

float volts(int adPin)               // Measures volts at adPin 
{                                    // Returns floating point voltage
 return float(analogRead(adPin)) * 5.0 / 1024.0; 
}    

