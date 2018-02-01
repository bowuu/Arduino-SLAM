/*
 * Robotics with the BOE Shield - StartResetIndicator
 * Test the piezospeaker circuit.
 */ 

void setup()                                 // Built in initialization block
{ 
  Serial.begin(9600);
  Serial.println("Beep!");  

  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone
}  
 
void loop()                                  // Main loop auto-repeats
{         
  Serial.println("Waiting for reset...");
  delay(1000);
}

