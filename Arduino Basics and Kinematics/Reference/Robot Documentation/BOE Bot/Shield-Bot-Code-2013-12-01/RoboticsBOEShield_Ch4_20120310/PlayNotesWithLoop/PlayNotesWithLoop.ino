// Robotics with the BOE Shield – PlayNotesWithLoop
// Displays and plays another element from note array. 

int note[] = {1047, 1147, 1319, 1397, 1568, 1760, 1976, 2093};

void setup() 
{
  
  Serial.begin(9600);

  for(int index = 0; index < 8; index++)
  {
    Serial.print("index = ");
    Serial.println(index);

    Serial.print("note[index] = ");
    Serial.println(note[index]);

    tone(4, note[index], 500);               
    delay(750);                                
  }
}

void loop() 
{
}

