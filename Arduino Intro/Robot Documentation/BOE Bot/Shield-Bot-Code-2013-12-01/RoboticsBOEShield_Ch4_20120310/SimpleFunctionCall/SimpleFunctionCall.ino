// Robotics with the BOE Shield – SimpleFunctionCall
// This sketch demonstrates a simple function call. 

void setup() {                         
  Serial.begin(9600);  
                
  Serial.println("Before example function call.");
  delay(1000);

  example();                              // This is the function call

  Serial.println("After example function call.");
  delay(1000);
}

void loop() {
}

void example()                            // This is the function
{
  Serial.println("During example function call.");
  delay(1000);
}

