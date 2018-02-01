// Robotics with the BOE Shield - Chapter 1, Project 1

void setup()
{
  Serial.begin(9600);
 
  for(char c = ' '; c <= '~'; c++)
  {
    Serial.print("Character = ");
    Serial.print(c);
    Serial.print("   ASCII value = ");
    Serial.println(c, DEC);
  }
  Serial.println("All done!");
}

void loop()
{
  // Empty, no repeating code.
}
