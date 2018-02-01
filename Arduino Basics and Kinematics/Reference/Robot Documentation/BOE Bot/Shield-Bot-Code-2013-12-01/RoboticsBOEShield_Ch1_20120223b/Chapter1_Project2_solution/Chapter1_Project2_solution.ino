// Robotics with the BOE Shield - Chapter 1, Project 2

void setup()
{
  Serial.begin(9600);

  int a = 20;

  if(a % 2 == 0)
  {
    Serial.print("a is even");
  }
  else
  {
    Serial.print("a is odd");
  }
}

void loop()
{
  // Empty, no repeating code.
}
