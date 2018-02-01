// Robotics with the BOE Shield – PlayAllNotesInArray
// Uses sizeof to determine number of elements int he array
// and then displays and prints each note value in the sequence. 

int note[] = {1047, 1147, 1319, 1397, 1568, 1760, 1976, 2093};

void setup() 
{  
  Serial.begin(9600);
  
  int elementCount = sizeof(note) / sizeof(int);

  Serial.print("Number of elements in array = ");
  Serial.println(elementCount);

  for(int index = 0; index < elementCount; index++)
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

