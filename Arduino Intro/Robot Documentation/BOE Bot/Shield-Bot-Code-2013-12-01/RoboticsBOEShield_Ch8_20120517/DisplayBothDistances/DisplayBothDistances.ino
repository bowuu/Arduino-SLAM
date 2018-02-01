/*
 * Robotics with the BOE Shield - DisplayBothDistances
 * Display left and right IR states in Serial Monitor.
 * Distance range is from 0 to 5.  Only a small range several centimeters  
 * in front of each detector is measureable.  Most of it will be 0 (too .
 * close) or 5 (too far). 
 */ 

void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  pinMode(10, INPUT);  pinMode(9, OUTPUT);   // Left IR LED & Receiver
  pinMode(3, INPUT);  pinMode(2, OUTPUT);    // Right IR LED & Receiver

  Serial.begin(9600);                        // Set data rate to 9600 bps
}  
 
void loop()                                  // Main loop auto-repeats
{
  int irLeft = irDistance(9, 10);            // Measure left distance
  int irRight = irDistance(2, 3);            // Measure right distance

  Serial.print(irLeft);                      // Display left distance
  Serial.print("  ");                        // Display spaces
  Serial.println(irRight);                   // Display right distance

  delay(100);                                // 0.1 second delay
} 

// IR distance measurement function

int irDistance(int irLedPin, int irReceivePin)
{  
  int distance = 0;
  for(long f = 38000; f <= 42000; f += 1000) {
    distance += irDetect(irLedPin, irReceivePin, f);
  }
  return distance;
}

// IR Detection function

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}     

