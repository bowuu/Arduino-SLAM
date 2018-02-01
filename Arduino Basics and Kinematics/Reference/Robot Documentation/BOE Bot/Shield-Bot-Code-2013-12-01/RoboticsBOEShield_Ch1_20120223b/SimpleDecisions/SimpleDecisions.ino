// Robotics with the BOE Shield - SimpleDecisions

void setup()
{
  Serial.begin(9600);

  int a = 89;
  int b = 42;

  if(a > b)
  {
    Serial.print("a is greater than b");
  }
  else
  {
    Serial.print("a is not greater than b");
  }
}

void loop()
{
  // Empty, no repeating code.
}
