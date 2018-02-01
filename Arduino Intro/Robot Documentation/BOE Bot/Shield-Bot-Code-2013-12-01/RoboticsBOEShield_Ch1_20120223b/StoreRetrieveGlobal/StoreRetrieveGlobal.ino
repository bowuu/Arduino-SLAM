// Robotics with the BOE Shield - StoreRetrieveGlobal

int a;
char c;
float root2;
    
void setup()
{
  Serial.begin(9600);

  a = 42;
  c = 'm';
  root2 = sqrt(2.0);
}

void loop()
{
  Serial.println(a);
  Serial.println(c);
  Serial.println(root2);
  delay(1000);
}
