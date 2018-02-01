// Robotics with the BOE Shield – PlayOneNote
// Displays and plays one element from note array. 

int note[] = {1047, 1147, 1319, 1397, 1568, 1760, 1976, 2093};

void setup() 
{
  Serial.begin(9600);

  Serial.print("note = ");
  Serial.println(note[3]);

  tone(4, note[3], 500);               
  delay(750);                                
}

void loop() 
{
}

