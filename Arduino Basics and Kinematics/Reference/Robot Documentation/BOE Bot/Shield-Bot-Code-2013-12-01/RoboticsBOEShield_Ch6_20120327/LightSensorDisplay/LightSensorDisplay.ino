/*
 * Robotics with the BOE Shield - LightSensorDisplay
 * Displays a scrolling graph of ndShade.  The asterisk positions ranges 
 * from 0 to 40 with 20 (middle of the display) indicating same light on 
 * both sides.
 */

void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  Serial.begin(9600);                        // Set data rate to 9600 bps 
}  
 
void loop()                                  // Main loop auto-repeats
{
  float tLeft = float(rcTime(8));            // Get left light & make float
  float tRight = float(rcTime(6));           // Get right light & make float
  
  float ndShade;                             // Normalized differential shade
  ndShade = tRight / (tLeft+tRight) - 0.5;   // Calculate it and subtract 0.5
  
  for(int i = 0; i<(ndShade * 40) + 20; i++) // Place asterisk in 0 to 40 
  {
    Serial.print(' ');                       // Pad (ndShade * 40) + 20 spaces
  }
  Serial.println('*');                       // Print asterisk and newline

  delay(100);                                // 0.1 second delay
} 

long rcTime(int pin)                         // rcTime measures decay at pin
{
  pinMode(pin, OUTPUT);                      // Charge capacitor 
  digitalWrite(pin, HIGH);                   // ..by setting pin ouput-high
  delay(5);                                  // ..for 5 ms
  pinMode(pin, INPUT);                       // Set pin to input
  digitalWrite(pin, LOW);                    // ..with no pullup
  long time  = micros();                     // Mark the time
  while(digitalRead(pin));                   // Wait for voltage < threshold
  time = micros() - time;                    // Calculate decay time
  return time;                               // Returns decay time
}

