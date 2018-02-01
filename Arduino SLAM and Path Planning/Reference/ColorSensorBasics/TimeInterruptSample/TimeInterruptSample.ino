
#include <TimerOne.h>


void my_callback_function()
{
  static unsigned long stamp = 0;
  Serial.print("Time since last call: ");
  Serial.println(millis()-stamp);
  stamp = millis();
} 


 void setup()
 {
   Serial.begin(115200);
   Timer1.initialize();
   Timer1.attachInterrupt(my_callback_function);  
 }
 void loop()
 {

 }
