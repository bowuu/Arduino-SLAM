#include <PinChangeInt.h>

#define ENCODER_PORT 11

void rising(){
  Serial.println("pin changed from 0 to 1");
}

void falling(){
  Serial.println("pin changed1 to 0");
}

void riseAndFall(){
  Serial.println("pin changed either from 0 to 1 or 1 to 0");
}

void setup(){
  Serial.begin(9600);
  pinMode(ENCODER_PORT,INPUT_PULLUP); // set port as input port

  //Attach interrupt
  //NOTE only function may be attached
  //PCintPort::attachInterrupt(ENCODER_PORT, &rising,RISING); 
  //PCintPort::attachInterrupt(ENCODER_PORT, &falling,FALLING); 
  PCintPort::attachInterrupt(ENCODER_PORT, &riseAndFall,CHANGE); 
}

//useful functions:
//noInterrupts();   //disables interrupts
//interrupts();     //enables interrupts

//remember, beware of race conditions!

void loop(){

}

