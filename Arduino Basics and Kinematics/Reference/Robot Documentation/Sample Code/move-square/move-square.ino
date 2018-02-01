// move-square.ino

#include <Servo.h>
Servo servoL;  // creates servo object to control a servo
Servo servoR;  // creates servo object to control a servo

// Servo Tuning
// These values are just starting points. Every servo is a little different and so you may need to fine tune each.
// Don't forget that depending n how you have your servos mounted, a value can go "forward" on one servo but 
// "backward" on the other.
// You may need to tune the forward rev values to go in a straight line or turn.
// You will probably need to tune the stopL and stopR values to get to a dead stop on each servo

// 0 full speeed one direction - 180 full speed opposite direction - 90 full stop
const int leftServoForward = 180;   // 135 is Clockwise, full speed (around 90 is stopped)
const int leftServoReverse = 0;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)

const int rightServoForward = 0;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)
const int rightServoReverse = 180;   // 135 is Clockwise, full speed (around 90 is stopped)

const int leftServoStop = 90;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)
const int rightServoStop = 90;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)

const int delayTime = 2000; // Delay program execution for 3000 ms or 3 seconds
const int turnDelay = 550;


void setup() {
  servoR.attach(5);  // attaches the left servo on pin 5
  servoL.attach(6);  // attaches the right servo on pin 6

  // ** initialize serial communication:
  Serial.begin(9600);
}



// ***********************************************************
// *******************MAIN LOOP ******************************
// ***********************************************************
// Runs forever...
void loop() {
  // put your main code here, to run repeatedly:

  forward();    // move forward // RSR LSR
  delay(delayTime);   // got for 500ms (1/2 second)
  stopall();
  delay(delayTime);
  turnR(); 
  stopall();
}


////////////// Everything below this is program functoions called from the main loop

// ***********************************************************
// ***** turnR() *********************************************
// ***********************************************************
void turnR(){
    // turns right approx 90 degrees (may need to be tuned)
    Serial.println("turnR()");
    servoL.write(leftServoForward);           // rotate L servo forward
    servoR.write(rightServoReverse);           // rotate R servo reverse (which turns us right)
    delay(turnDelay);                 // wait for full turn
    servoR.write(rightServoStop);              // stop
    servoL.write(leftServoStop);              // stop 
}


// ***********************************************************
// ***** turnL() *********************************************
// ***********************************************************
void turnL(){
    // turns left approx 90 degrees (may need to be tuned)
  Serial.println("turnL()");
    servoL.write(rightServoForward);           // rotate R servo forward
    servoR.write(leftServoReverse);           // rotate L servo reverse (which turns us left)
    delay(delayTime);                       // wait for full turn
    servoR.write(rightServoStop);              // stop
    servoL.write(leftServoStop);              // stop
}


// ***********************************************************
// ***** forward() *********************************************
// ***********************************************************
void forward(){
    // goes forward, forever
    Serial.println("forward()");
    servoL.write(rightServoReverse);           // rotate R servo forward
    servoR.write(leftServoReverse);           // rotate L servo forward
}

// ***********************************************************
// ***** backward() *********************************************
// ***********************************************************
void backward(){
    // goes backwards, forever
    Serial.println("backward()");
    servoL.write(rightServoForward);           // rotate R servo forward
    servoR.write(leftServoForward);           // rotate L servo forward
}

// ***********************************************************
// ***** stopall() *********************************************
// ***********************************************************
void stopall(){
    // stops
    Serial.println("stopall()");
    servoR.write(rightServoStop);              // stop
    servoL.write(leftServoStop);              // stop
}