/*
 * Robotics with the BOE Shield - LeftLightSensor
 * Measures and displays microsecond decay time for left light sensor.
 */

void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  Serial.begin(9600);                        // Set data rate to 9600 bps 
}  
 
void loop()                                  // Main loop auto-repeats
{
  long tLeft = rcTime(8);                    // Left rcTime -> tLeft
  
  Serial.print("tLeft = ");                  // Display tLeft label
  Serial.print(tLeft);                       // Display tLeft value
  Serial.println(" us");                     // Display tLeft units + newline

  delay(1000);                               // 1 second delay
} 
                                             // rcTime function at pin  
long rcTime(int pin)                         // ..returns decay time
{                                            
  pinMode(pin, OUTPUT);                      // Charge capacitor 
  digitalWrite(pin, HIGH);                   // ..by setting pin ouput-high
  delay(1);                                  // ..for 5 ms
  pinMode(pin, INPUT);                       // Set pin to input
  digitalWrite(pin, LOW);                    // ..with no pullup
  long time  = micros();                     // Mark the time
  while(digitalRead(pin));                   // Wait for voltage < threshold
  time = micros() - time;                    // Calculate decay time
  return time;                               // Return decay time
}  

