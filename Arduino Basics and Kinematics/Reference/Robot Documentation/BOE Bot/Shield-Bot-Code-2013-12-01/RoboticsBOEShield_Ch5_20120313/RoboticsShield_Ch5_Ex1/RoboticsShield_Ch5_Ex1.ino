// Robotics with the BOE Shield Chapter 5, Exercise 1
// Value from 0 to 3 indicates whisker states:
// 0 = both, 1 = left, 2 = right, 3 = neither.

void setup()                       // Built-in initialization block
{ 
  tone(4, 3000, 1000);             // Play tone for 1 second
  delay(1000);                     // Delay to finish tone

  pinMode(7, INPUT);               // Set right whisker pin to input
  pinMode(5, INPUT);               // Set left whisker pin to input  

  Serial.begin(9600);              // Set data rate to 9600 bps
}  
 
void loop()                        // Main loop auto-repeats
{                                            
  byte whiskers = 2 * digitalRead(5);
  whiskers += digitalRead(7);

  Serial.println(whiskers);        // Display wLeft

  delay(50);                       // Pause for 50 ms
}            

