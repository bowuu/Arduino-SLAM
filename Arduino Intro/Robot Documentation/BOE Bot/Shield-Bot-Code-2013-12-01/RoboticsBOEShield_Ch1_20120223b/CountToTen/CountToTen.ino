// Robotics with the BOE Shield - CountToTen

void setup()
{
  Serial.begin(9600);
 
  for(int i = 1; i <= 10; i++)
  {
    Serial.println(i);
    delay(500);
  }
  Serial.println("All done!");
}

void loop()
{
  // Empty, no repeating code.
}
