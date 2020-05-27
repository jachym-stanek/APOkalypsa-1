#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "PONG.h"
#include "game.h"
#include "gameGraphics.h"
#include "knobs.h"

int main(int argc, char *argv[]) {
/** TODO: The contents of this function are purely for testing purposes.
*	 Things like the function playGame() game will be called in completely different
*   ways, if at all.
**/
	printf("Testing PONG v 2.0\n");
	
	//clean the periferies
	int check = disp_setup();
	if (check != SUCCESS) {
		fprintf(stderr, "Unable to access LCD and LEDs!\n");
		return DISP_ERR;
	}
	clean_slate();
	
	if (!knobs_init()) {
		fprintf(stderr, "Unable to access the knobs!\n");
		return KNOBS_ERR;
	}
	
	int status = play_game();
	
		
	if (status == A_WON) {
		printf("Player A won!\n");
	} else if (status == B_WON) {
		printf("Player B won!\n");
	} else {
		printf("Unexpected outcome!\n");
	}
	
	return SUCCESS;
}

