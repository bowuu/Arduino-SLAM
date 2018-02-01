// Robotics with the BOE Shield - Circumference

void setup()
{
  Serial.begin(9600);

  float r = 0.75;
  float c = 2.0 * PI * r;
 
  Serial.print("circumference = ");
  Serial.println(c);
}

void loop()
{
  // Empty, no repeating code.
}
