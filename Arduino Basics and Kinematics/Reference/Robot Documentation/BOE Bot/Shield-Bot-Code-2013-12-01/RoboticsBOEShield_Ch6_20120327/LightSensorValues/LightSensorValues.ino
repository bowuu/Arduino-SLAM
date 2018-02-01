/*
 * Robotics with the BOE Shield - LightSensorValues
 * Displays tLeft, ndShade and tRight in the Serial Monitor.
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
  ndShade = tRight / (tLeft + tRight) - 0.5; // Calculate it and subtract 0.5

  // Display heading 
  Serial.println("tLeft     ndShade     tRight");

  Serial.print(tLeft);                       // Display tLeft value
  Serial.print("   ");                       // Display spaces
  Serial.print(ndShade);                     // Display ndShade value
  Serial.print("     ");                     // Display more spaces
  Serial.println(tRight);                    // Display tRight value
  Serial.println(' ');                       // Add an extra newline

  delay(1000);                                // 1 second delay
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

