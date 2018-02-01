#include <Servo.h>  // Include servo library

#define L_SERVO_PORT 2
#define R_SERVO_PORT 3
Servo LServo;  // Declare Left servo
Servo RServo;  // Declare right servo

void setup() {
  LServo.attach(L_SERVO_PORT);
  RServo.attach(R_SERVO_PORT);
  LServo.writeMicroseconds(1500); 
  RServo.writeMicroseconds(1500);
}

void loop() {      // Main loop auto-repeats
  LServo.writeMicroseconds(1600);     // Set velocity to Left Servo
  RServo.writeMicroseconds(1418);    // Set velocity to Right Servo
  delay(2000);                        

  LServo.writeMicroseconds(1500); 
  RServo.writeMicroseconds(1500);
  delay(2000);                        
}

