

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);  
  Serial.print("Hello World");
}

void loop() {
  delay(3000);
  Serial.println("I'm looping once every 3 seconds!");

}
