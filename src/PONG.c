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
	printf("Testing PONG v 2.0\n");
	
	//clean the periferies
	int check = disp_setup();
	if (check != SUCCESS) {
		fprintf(stderr, "Unable to access periferies!\n");
		return DISP_ERR;
	}
	clean_slate();
	
	play_game();
	return SUCCESS;
}

