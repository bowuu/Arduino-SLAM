/*
 * Robotics with the BOE Shield - IrInterferencesSniffer
 * Test for external sources of infrared interference.  If IR interference is
 * detected: Serial Monitor displays warning, piezospeaker plays alarm, and
 * indicator lights flash.
 */ 

void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  pinMode(10, INPUT);                        // Left IR Receiver
  pinMode(3, INPUT);                         // Right IR Receiver
  pinMode(8, OUTPUT);                        // Left indicator LED
  pinMode(7, OUTPUT);                        // Right indicator LED

  Serial.begin(9600);                        // Set data rate to 9600 bps
}  
 
void loop()                                  // Main loop auto-repeats
{
  int irLeft = digitalRead(10);              // Check for IR on left
  int irRight = digitalRead(3);              // Check for IR on right
  
  if((irLeft == 0) || (irRight == 0))        // If left OR right detects
  {                                         
    Serial.println("IR interference!");    // Display warning
    for(int i = 0; i < 5; i++)               // Repeat 5 times 
    {
      digitalWrite(7, HIGH);                 // Turn indicator LEDs on
      digitalWrite(8, HIGH);
      tone(4, 4000, 10);                     // Sound alarm tone
      delay(20);                             // 10 ms tone, 10 between tones
      digitalWrite(7, LOW);                  // Turn indicator LEDs off
      digitalWrite(8, LOW);
    }
  }  
} 

