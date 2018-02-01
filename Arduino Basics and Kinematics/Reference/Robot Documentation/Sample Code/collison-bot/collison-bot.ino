// collision-bot
#include <Servo.h>

const int powerPin = 10;    // providing power to ping sensor from pin 10
const int pingPin = 11;     // pin we're sending the trigger/ping on
const int echoPin = 12;     // pin we're reading back the echo on
const int gnd1Pin = 13;     // simulated ground so we can safely plug the module into our arduinos

long dist = 0;

Servo servoL;  // create servo object to control a servo
Servo servoR;  // create servo object to control a servo

// 0 full speeed one direction - 180 full speed opposite direction - 90 full stop
const int leftServoForward = 180;   // 135 is Clockwise, full speed (around 90 is stopped)
const int leftServoReverse = 0;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)

const int rightServoForward = 0;    // 45 is Counter Clockwise, full speed (ardound 90 is stopped)
const int rightServoReverse = 180;   // 135 is Clockwise, full speed (around 90 is stopped)

const int leftServoStop = 90;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)
const int rightServoStop = 90;    // 90 is usually "stopped" (you may need to fine tune it for dead stop)

const int delayTime = 3000; // Delay program execution for 3000 ms or 3 seconds


const int turnDelay = 550;  // Delay for turnL() turnR() to achive close to 90 degrees (at full throttle)
const int backDelay = 200;  // Delay for slight back up before turning out of an obstacle

bool paused = true;        // Program starts off in paused mode

int accel = 45;              // acceleration figure for turns (if needed)
const int conaccel = accel;  // constant (if needed)

bool slowed = false;

bool obstacleL = false;
bool obstacleR = false;
bool obstacleC = false;

bool hasStarted = false;
  
// ***********************************************************
// ****************** SETUP BLOCK ****************************
// ***********************************************************
// only runs once at program startup
void setup() {
  pinMode(gnd1Pin, OUTPUT);      // sets up ping module's inner GND pin on a low output, and
  digitalWrite(gnd1Pin, LOW);     // the outter GND pin to hard GND (on most arduinos)
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);  // try to power the module from pin
  // ** US-100 PING SENSOR I/O PINS
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, OUTPUT);    // just to make sure
  digitalWrite(echoPin, LOW);  // we clear any previous settings
  pinMode(echoPin, INPUT);     // and then use it as INPUT
  delay(500);
  servoR.attach(5);  // attaches the left servo on pin 5
  servoL.attach(6);  // attaches the right servo on pin 6
  Serial.begin(9600);
  servoL.write(leftServoStop);
  servoR.write(rightServoStop);
}


// ***********************************************************
// ******************** MAIN LOOP ****************************
// ***********************************************************

void loop() {
  if (!hasStarted) {
    pauseNgo();                    // This uses the sensor as a "pause/start" toggle switch
  }
  
  dist = getdist();             

  // ****** If object detected between 3 and 7 inches away (and the system is not paused),
  // ****** then run stop both servos and scan left and right for obstacles
  if ( (dist > 2 && dist < 8) && !paused ) {
    servoR.write(rightServoStop);
    servoL.write(leftServoStop);
    scanLR();
  }
  // ****** If there is an obstacle to the right, left, or center and not paused then enter this
  // ****** while loop
  while ((obstacleR  || obstacleC  || obstacleL) && !paused ) {  

    // ****** If obstacle in center but none on the right or left, then turn left and continue
    if (!obstacleR && !obstacleL && obstacleC && !paused) {
      reverse();          // back up a little
      delay(backDelay);   //
      turnL();            // turn left
      forward();          // move forward
      obstacleC = false;  // reset 
      obstacleR = false;  // reset
      obstacleL = false;  // reset
      break;              // breaks out of while loop (skipping other checks)
    }

    // ****** If obstacle is on the right only (and system is not paused), turn left and continue
    if (obstacleR && !paused) {
      reverse();          // back up a little
      delay(backDelay);   //
      turnL();            // turn left
      forward();          // go forward
      obstacleC = false;  // reset
      obstacleR = false;  // reset
      obstacleL = false;  // reset
      break;              // breaks out of while loop (skipping other checks)
    }
  
    // ****** If obstacle is on the left only (and system is not paused), turn right and continue
    if (obstacleL && !paused) {   
      reverse();          // back up a little
      delay(backDelay);   //
      turnR();            // turn right
      forward();          // go forward
      obstacleC = false;  // reset
      obstacleR = false;  // reset
      obstacleL = false;  // reset
      break;              // breaks out of while loop (skipping other checks)
    }    
  }
}


// ***********************************************************
// ******************* turnR() *******************************
// ***********************************************************
void turnR(){
    // turns right approx 90 degrees (may need to be tuned)
    servoL.write(leftServoForward);           // rotate L servo forward
    servoR.write(rightServoReverse);          // rotate R servo reverse (which turns us right)
    delay(turnDelay);                         // wait for full turn
    servoR.write(rightServoStop);             // stop
    servoL.write(leftServoStop);              // stop 
}


// ***********************************************************
// ******************* turnL() *******************************
// ***********************************************************
void turnL(){
    // turns left approx 90 degrees (may need to be tuned)
    servoL.write(rightServoForward);           // rotate R servo forward
    servoR.write(leftServoReverse);            // rotate L servo reverse (which turns us left)
    delay(turnDelay);                          // wait for full turn
    servoR.write(rightServoStop);              // stop
    servoL.write(leftServoStop);               // stop
}


// ***********************************************************
// ******************* forward() *****************************
// ***********************************************************
void forward(){
    servoL.write(leftServoForward);      // rotate left servo forward
    servoR.write(rightServoForward);     // rotate right servo forward
}

// ***********************************************************
// ******************* reverse() *****************************
// ***********************************************************
void reverse(){
    servoL.write(leftServoReverse);      // rotate left servo reverse
    servoR.write(rightServoReverse);     // rotate left servo reverse
}



// ***********************************************************
// ******************* scanLR() ******************************
// ***********************************************************
void scanLR() {
  int obstacleThold = 10;
  obstacleC = false;
  obstacleR = false;
  obstacleL = false;
  const int scandelay = 850;

  // Scan forward
  dist = getdist();
  if (dist <= obstacleThold) {
    obstacleC = true;
  }

  // Scan Right
  turnR();
  dist = getdist();
  if (dist <= obstacleThold) {
    obstacleR = true;
  }

  // Scan Left
  turnL();
  turnL();
  dist = getdist();
  if (dist <= obstacleThold) {
    obstacleL = true;
  }
  turnR();    // This recenters the bot
}

// ***********************************************************
// ******************* getdist() *****************************
// ***********************************************************
long getdist()
{
  long duration, inches;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(pingPin, HIGH);      // start the outgoing ping
//  delayMicroseconds(10);            // do the ping for 10uS
  digitalWrite(pingPin, LOW);       // stop doing the ping
  duration = pulseIn(echoPin, HIGH);  // grab the delay of return echo
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  return inches;
}


// ***********************************************************
// ****************** pauseNgo() *****************************
// ***********************************************************
void pauseNgo() {

  // If unpaused, but object less than two inches, go into paused mode
  dist = getdist();
  while (!paused  && dist < 2 ) {
    Serial.println("Not paused and dist less than 2");
    dist = getdist();
    if (dist < 2 ) {
      servoL.write(leftServoStop);                  // stop L servo
      servoR.write(rightServoStop);                  // stop R servo
      paused = true;
      delay(250);
    }
  }
  

  // Paused Loop & Unpausing Detection
  while (paused && !hasStarted) {
    Serial.println("Paused");
    dist = getdist();
    if (dist < 2) {
      Serial.println("dist is less than 2");
      // Start moving forward, full speed
      servoL.write(leftServoForward);                  // forward L servo
      servoR.write(rightServoForward);                  // forward R servo
      paused = false;
      hasStarted = true;
    }
  }
}

// ***********************************************************
// ******************* slowDown() *****************************
// ***********************************************************
void slowDown() {
  int accel = 0;
  for ( int x = 0 ; x < 8 ; x++ ) {
    accel =  accel + 5;
    servoL.write(leftServoForward - accel);                // slow L servo
    servoR.write(rightServoForward - accel);                // slow R servo
    delay(50);
  }
  servoL.write(leftServoStop);                  // stop L servo
  servoR.write(rightServoStop);                  // stop R servo
  accel = conaccel;
  slowed = 1;
}

// Original code from the ping sensor library
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74.0 / 2.0;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29.0 / 2.0;
}