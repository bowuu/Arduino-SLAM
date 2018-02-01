/*
 * Robotics with the BOE Shield - TestWhiskersWithLeds
 * Display left and right whisker states in Serial Monitor.
 * 1 indicates no contact; 0 indicates contact.
 * Display whisker states with LEDs.  LED on indicates contact; 
 * off indicates none.
 */

void setup()                                 // Built-in initialization block
{ 
  pinMode(7, INPUT);                         // Set right whisker pin to input
  pinMode(5, INPUT);                         // Set left whisker pin to input  
  pinMode(8, OUTPUT);                        // Left LED indicator -> output
  pinMode(2, OUTPUT);                        // Right LED indicator -> output   

  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  Serial.begin(9600);                        // Set serial data rate to 9600 
}  
 
void loop()                                  // Main loop auto-repeats
{                                            
  byte wLeft = digitalRead(5);               // Copy left result to wLeft  
  byte wRight = digitalRead(7);              // Copy right result to wRight

  if(wLeft == 0)                             // If left whisker contact
  {
    digitalWrite(8, HIGH);                   // Left LED on
  } 
  else                                       // if no left whisker contact
  {
    digitalWrite(8, LOW);                    // Left LED off
  }

  if(wRight == 0)                            // If right whisker contact
  {
    digitalWrite(2, HIGH);                   // Right LED on
  } 
  else                                       // If no right whisker contact
  {
    digitalWrite(2, LOW);                    // Right LED off
  }
  
  Serial.print(wLeft);                       // Display wLeft 
  Serial.println(wRight);                    // Display wRight
  delay(50);                                 // Pause for 50 ms
}  

