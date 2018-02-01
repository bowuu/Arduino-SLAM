// move-forward.ino
//
// This is the simple code for the continuous rotation servo wheels for the bot

// this include is what loads the code to talk to the servos on PWN based digital I/O pins
#include <Servo.h>
Servo servoL;  // creates servo object to control a servo
Servo servoR;  // creates servo object to control a servo

// Servo Tuning
// These values are just starting points. Every servo is a little different and so you may need to fine tune each.
// Don't forget that depending on how you have your servos mounted, a value can go "forward" on one servo but 
// "backward" on the other.
// You may need to tune the forward rev values to go in a straight line.
// You will probably need to tune the leftServoStop and rightServoStop values to achieve full stop on each servo

// 0 full speeed one direction - 180 full speed opposite direction - 90 full stop
const int leftServoForward = 180;   // 135 is Clockwise, full speed (around 90 is stopped)
const int leftServoReverse = 0;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)

const int rightServoForward = 0;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)
const int rightServoReverse = 180;   // 135 is Clockwise, full speed (around 90 is stopped)

const int leftServoStop = 90;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)
const int rightServoStop = 90;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)

const int delayTime = 3000; // Delay program execution for 3000 ms or 3 seconds


void setup() {
  servoR.attach(5);  // attaches the left servo on pin 5
  servoL.attach(6);  // attaches the right servo on pin 6

  // ** initialize serial communication:
  Serial.begin(9600);
}


// ***********************************************************
// ********************* MAIN LOOP ***************************
// ***********************************************************
// Runs forever...
void loop() {
  // put your main code here, to run repeatedly

  servoR.write(rightServoForward); // right servo moves forward
  servoL.write(leftServoForward);  // left servo moves forward
  delay(delayTime);                // pause program execution for 3 seconds  
  servoR.write(rightServoStop);    // stop right servo
  servoL.write(leftServoStop);     // stop left servo
  delay(delayTime);                // pause program execution for 3 section
}



// move two servos forward forever
void forward(){
    Serial.println("forward()");
    servoL.write(leftServoForward);      // rotate left servo forward
    servoR.write(rightServoForward);     // rotate right servo forward
}

// move two servos backwards forever
void reverse(){
    Serial.println("backward()");
    servoL.write(leftServoReverse);      // rotate left servo reverse
    servoR.write(rightServoReverse);     // rotate left servo reverse
}

// // **********************************************************
// // ******************* stopall() ****************************
// // **********************************************************
// void stopall(){
//     // stops
//     Serial.println("stopall()");
//     servoR.write(rightServoStop);              // stop
//     servoL.write(leftServoStops);              // stop
// }
