#include <elapsedMillis.h>

elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs



unsigned int interval = 1000; // ON OFF interval
boolean state = false;        // ON OFF state

void setup() 
{                
  Serial.begin(9600);     
}

void loop()
{
  if (timeElapsed > interval) 
  {       
    state = !state;    // switch state
    if(state) Serial.println("ON");
    else      Serial.println("OFF");
    timeElapsed = 0;       // reset the counter to 0 so the counting starts over...
  }
}

