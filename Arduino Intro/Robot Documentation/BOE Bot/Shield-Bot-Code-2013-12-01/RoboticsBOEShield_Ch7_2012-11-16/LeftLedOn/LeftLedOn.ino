// Robotics with the BOE Shield - LeftLedOn
// Turn on left LED for brightness testing

void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  pinMode(8, OUTPUT);                        // Left indicator LED
  digitalWrite(8, HIGH);
}  
 
void loop()                                  // Main loop auto-repeats
{
}

