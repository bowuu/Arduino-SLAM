#include "MainFunctions.h"

void setup() {
    robotSetup();
    initChooser(&lcd);
    setSpeedsIPS(0, 0);
    delay(1000);
    robotState.params[2] = 2; //for testing
    robotState.params[0] = 4;
}

void loop() {
	//mapCell(&robotState.nodes[robotState.curNode], 1);
    execProgram();

}

