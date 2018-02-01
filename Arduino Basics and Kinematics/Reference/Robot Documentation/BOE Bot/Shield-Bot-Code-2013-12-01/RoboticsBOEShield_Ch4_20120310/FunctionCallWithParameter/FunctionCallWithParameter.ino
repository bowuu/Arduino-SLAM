// Robotics with the BOE Shield – FunctionCallWithParameter
// This program demonstrates a function call with a parameter. 

void setup() {
  Serial.begin(9600);

  Serial.println("Playing higher pitch tone...");

  pitch(3500);         // pitch function call passes 3500 to Hz parameter

  delay(1000);

  Serial.println("Playing lower pitch tone...");

  pitch(2000);         // pitch function call passes 2000 to Hz parameter

  delay(1000);
}

void loop() 
{
}

void pitch(int Hz)     // pitch function with Hz declared as a parameter
{                    
  Serial.print("Frequency = ");
  Serial.println(Hz);
  tone(4, Hz, 1000);
  delay(1000);
}

