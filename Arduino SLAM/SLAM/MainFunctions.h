#ifndef _MAIN_FUNCTIONS_
#define _MAIN_FUNCTIONS_

#include "ColorSensor.h"
#include "WallFollowing.h"
#include "Chooser.h"
#include "RobotSetup.h"

#define LEFT 0
#define RIGHT 1

//PROTOTYPES
void turn90(bool direction);
short calcLeft(short orient);
short calcRight(short orient);
short calcBack(short orient);
void displayCell(short currentCell);
bool mapCell(short orient);
void moveForward();
void wFWrapper();
void lcdDisplay();

unsigned long start, end, time;
int numMapped = 0;
bool lineDetected = false;

//FUNCTIONS
bool lineDetect() {
    wFWrapper();
    lineDetected = timer(readColor);
    return lineDetected;
}
void pop(int arr[17]){
    int temp[17];
    temp[0] = arr[0];
    for (int i = 2; i < 17; ++i)
    {
        temp[i-1] = arr[i];//delete 1st node
    }
}
bool mapping(){
    lcd.setBacklight(WHITE);
    lcd.setCursor(0, 0);
    lcd.print("OOOOOOOOOOOOOOOO");
    lcd.setCursor(0, 1);
    lcd.print("G   O           ");
    delay(500);
    //Map First Cell
    robotState.curNode = robotState.params[0];
    mapCell(robotState.params[2]);
    //displayCell(robotState.curNode);
    delay(250);
    //Turn 90 degrees to map the other walls in the cell
    turn90(0);
    mapCell(robotState.params[2]);
    //displayCell(robotState.curNode);
    delay(250);
    //Turn back to original orientation
    turn90(1);
    numMapped++;

    //Use left hand following rule to map
    while(numMapped < 16){

        displayCell(robotState.curNode);
        //if no forward wall, go forward
        if(robotState.nodes[robotState.curNode].walls[robotState.params[2]] == 0){ //if no left wall
            moveForward();
            mapCell(robotState.params[2]);
            if(robotState.nodes[robotState.curNode].visited == 0){
                numMapped++;
            }
        }
        //if no left wall, turn left
        else if(robotState.nodes[robotState.curNode].walls[calcLeft(robotState.params[2])] == 0){
            turn90(LEFT);
            mapCell(robotState.params[2]);
        }
        //if no right wall, go right
        else if(robotState.nodes[robotState.curNode].walls[calcRight(robotState.params[2])] == 0){ //if no left wall
            turn90(RIGHT);
            mapCell(robotState.params[2]);
        }
        //dead end, turn around.
        else{
            turn90(LEFT);
            turn90(LEFT);
            mapCell(robotState.params[2]);
        }
    }
    setSpeedsIPS(0,0);
    lcd.setCursor(0,0);
    lcd.print("Finished Mapping.");
    return true;
}

bool planning(){}

   //  Use BFS to plan route
   //  int q[17];
   //  int*qSize = q[0];
   //  int start = robotState.params[0];
   //  int end = robotState.params[1];
   //  int curNode = robotState.params[2];
   //  int orientation = robotState.params[2];
   //  q[*qSize] = start; //origin
   //  *qSize++;
   //  while (*qSize >= 0)
   //  {
   //      curNode = q[*qSize];
   //      robotState.nodes[curNode].visited = true;
   //      pop(q);
   //      *qSize--;
   //      go through neighbors 
   //     for (int i = 0; i < 4; i++)
   //     {
   //          if (robotState.nodes[curNode])
   //          {
                
   //          }
   //     }
   //      if not already visited 
   //      add curNode as successor
   //      if they are the end stop
   //      else, add to the q
   // }
   //  return successors;

           //facing    north                     east                  south                   west
    //front     nodes[curNode - 4]      nodes[curNode + 1]      nodes[curNode + 4]      nodes[curNode - 1]
    //left      nodes[curNode - 1]      nodes[curNode - 4]      nodes[curNode + 1]      nodes[curNode - 4]
    //back      nodes[curNode + 4]      nodes[curNode - 1]      nodes[curNode - 4]      nodes[curNode + 4]
    //right     nodes[curNode + 1]      nodes[curNode + 4]      nodes[curNode - 1]      nodes[curNode - 4]
    

    //add neighbors accordingly
            //other notes
    //if node-5 < 0, cant go north
    //if node%4 = 0, can't go right
    //if node%4 == 1, cant go left
    //if node+4 > 16, cant go down
//}
//HELPER FUNCTIONS
bool timer(bool (*f)()) {
    bool linePassed;
    unsigned long prevMillis = 0;
    unsigned long interval = 50;
    unsigned long currMillis = millis();
    if (currMillis - prevMillis > interval) {
        prevMillis = currMillis;
        linePassed = (*f)();
    }
    return linePassed;
}
bool mapCell(short orient){
    setSpeedsIPS(0,0);
    sPollCalc(&lcd);
    //left sensor
    if(inches[1] > 11){
        robotState.nodes[robotState.curNode].walls[calcLeft(orient)] = 0;
        //lcd.setCursor(0,1);
        //lcd.print('|');
    }
    else{
        robotState.nodes[robotState.curNode].walls[calcLeft(orient)] = 1;
        //lcd.setCursor(0,1);
        //lcd.print(' ');

    }
    //front sensor
    if(inches[0] > 11){
        robotState.nodes[robotState.curNode].walls[orient] = 0;
        //lcd.setCursor(1,0);
        //lcd.print(' ');
    }
    else{
        robotState.nodes[robotState.curNode].walls[orient] = 1;
        //lcd.setCursor(1,0);
        //lcd.print('_');
    }
    //right sensor
    if(inches[2] > 9.5){
        robotState.nodes[robotState.curNode].walls[calcRight(orient)] = 0;
        //lcd.setCursor(2,1);
        //lcd.print(' ');
    }
    else{
        robotState.nodes[robotState.curNode].walls[calcRight(orient)] = 1;
        //lcd.setCursor(2,1);
        //lcd.print('|');
    }
    robotState.nodes[robotState.curNode].visited = 1;
    return true;
}

void displayCell(short curNode) {
    if (robotState.nodes[curNode].visited == true) {
        lcd.setCursor(robotState.curNode - 1, 0);
        lcd.print("X");
    }
    lcd.setCursor(1, 1);
    if (robotState.curNode < 10) {
        lcd.print(" ");
        lcd.print(robotState.curNode);
    } else {
        lcd.print(robotState.curNode);
    }
    lcd.setCursor(5, 1);
    lcd.print(robotState.orientNames[robotState.params[2]]);

    //    lcd.clear();
    //    lcd.setCursor(0,0);
    //    lcd.print("CN: ");
    //    lcd.setCursor(4, 0);
    //    lcd.print(curNode);
    //    lcd.setCursor(6, 0);
    //    lcd.print("OR: ");
    //    lcd.setCursor(11, 0);
    //    lcd.print(robotState.params[2]);
    //    lcd.setCursor(0, 1);
    //    lcd.print("N ");
    //    lcd.setCursor(2, 1);
    //    lcd.print(robotState.nodes[curNode].walls[0]);
    //    lcd.setCursor(4, 1);
    //    lcd.print("E ");
    //    lcd.setCursor(6, 1);
    //    lcd.print(robotState.nodes[curNode].walls[1]);
    //    lcd.setCursor(8, 1);
    //    lcd.print("S ");
    //    lcd.setCursor(10, 1);
    //    lcd.print(robotState.nodes[curNode].walls[2]);
    //    lcd.setCursor(12, 1);
    //    lcd.print("W ");
    //    lcd.setCursor(14, 1);
    //    lcd.print(robotState.nodes[curNode].walls[3]);
}
void turn90(bool direction) { //LEFT == 0 RIGHT == 1
    if (direction == LEFT) {
        setSpeedsIPS(-IPS_MAX, IPS_MAX);
        robotState.params[2] = calcLeft(robotState.params[2]);
    } else {
        setSpeedsIPS(IPS_MAX, -IPS_MAX);
        robotState.params[2] = calcRight(robotState.params[2]);
    }
    delay(700);
    setSpeedsIPS(0, 0);
    delay(500);
}

void moveForward(){
    bool lineDetected = false;
    start = millis();
    while(!lineDetected){
        lineDetected = lineDetect();
    }
    end = millis();
    robotState.nodes[robotState.curNode].walls[calcBack(robotState.params[2])] = 0;
    time = (end - start)/1000;
    //go same distance from line
    start = millis();
    while((end - start)/2000 < time){
        wFWrapper();
        end = millis();
    }
    setSpeedsIPS(0,0); 
    delay(1000); //testing
}
short calcLeft(short orient){
    orient == 0 ? orient = 3: orient-= 1;
    return orient;
}
short calcRight(short orient){
    orient == 3 ? orient = 0 : orient+= 1; 
    return orient;
}
short calcBack(short orient){
    if(orient == 0) return 2;
    if(orient == 1) return 3;
    if(orient == 2) return 0;
    if(orient == 3) return 1;
}
void wFWrapper(){
    if(leftSS.yt < 8.5){
        wallFollowing(&leftSS);
    }
    else if(rightSS.yt < 8.5){
        wallFollowing(&rightSS);
    }
    else{
        setSpeedsIPS(IPS_MAX, IPS_MAX);
    }
}

// void lcdDisplay(){  
//     int j = 0;  
//     lcd.setCursor(0, 0);
//     lcd.print("OOOOOOOOOOOOOOOO");
//     lcd.setCursor(0, 1);
//     lcd.print("G  O            ");
//     for(int i = 1; i < 17; i++){
//         if(robotState.nodes[i].visited == true){            
//             lcd.setCursor(i-1, 0);
//             lcd.print("X");
//         }
//         lcd.setCursor(1, 1);
//         lcd.print(robotState.curNode);
//         lcd.setCursor(4, 1);
//         lcd.print(robotState.params[2]); 
//     }
// }
#endif //_MAIN_FUNCTIONS_H_
