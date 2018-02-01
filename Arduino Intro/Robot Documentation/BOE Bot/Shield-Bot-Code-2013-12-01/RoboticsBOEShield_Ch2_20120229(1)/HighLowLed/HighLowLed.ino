/*
 Robotics with the BOE Shield - HighLowLed
 Turn LED connected to digital pin 13 on/off once every second.
 */ 

void setup()                                 // Built-in initialization block
{ 
  pinMode(13, OUTPUT);                       // Set digital pin 13 -> output
}  
 
void loop()                                  // Main loop auto-repeats
{                                         
  digitalWrite(13, HIGH);                    // Pin 13 = 5 V, LED emits light
  delay(500);                                // ..for 0.5 seconds
  digitalWrite(13, LOW);                     // Pin 13 = 0 V, LED no light
  delay(500);                                // ..for 0.5 seconds
}  

