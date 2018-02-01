/*
 Robotics with the BOE Shield – CountToTenDocumented
 This sketch displays an up-count from 1 to 10 in the Serial Monitor
 */

const int startVal = 1;                      // Staring value for counting
const int endVal = 10;                       // Ending value for counting
const int baudRate = 9600;                   // For setting baud rate

void setup()                                 // Built in initialization block
{
  Serial.begin(baudRate);                    // Set data rate to baudRate
 
  for(int i = startVal; i <= endVal; i++)    // Count from startVal to endVal
  {
    Serial.println(i);                       // Display i in Serial Monitor
    delay(500);                              // Pause 0.5 s between values
  }
  Serial.println("All done!");               // Display message when done
}

void loop()                                  // Main loop auto-repeats
{
  // Empty, no repeating code.
}
