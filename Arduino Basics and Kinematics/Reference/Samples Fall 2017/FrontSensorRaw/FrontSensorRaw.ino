

const int SFSensor = A0;  

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);  
}

void loop() {
  
  delay(1000);
  int val  = analogRead(SFSensor);
  Serial.println(val);

}

