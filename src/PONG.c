#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "PONG.h"
#include "game.h"
#include "gameGraphics.h"

int main(int argc, char *argv[]) {
/** TODO: The contents of this function are purely for testing purposes.
*	 Things like the function playGame() game will be called in completely different
*   ways, if at all.
**/
	printf("Testing PONG\n");
	
	//clean the periferies
	int check = dispSetup();
	if (check != SUCCESS) {
		fprintf(stderr, "Unable to access periferies!\n");
		return DISP_ERR;
	}
	cleanSlate();
	
	playGame();
	return SUCCESS;
}

