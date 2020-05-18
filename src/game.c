//This file handles the game logic
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "game.h"
#include "gameGraphics.h"

//starts the game and handles the end
void playGame() {
	gameStruct game;
	setupData(&game);
	
	int check = gameLoop(&game);
	
	if (check == 1) {
		printf("Player A won\n");
	} else if (check == 2) {
		printf("Player B won\n");
	} else {
		printf("Unforseen outcome\n");
	}
}

//main function for playing the game
int gameLoop(gameStruct *game) {
	dispGame(game->Apts, game->Bpts, game->Apos, game->Bpos, game->ballPos);
	printf("Game loop would start now\n");
	return 0;
}

//This function prepares the game data
void setupData(gameStruct *game) {
	game->Apts = 0;
	game->Bpts = 0;
	
	game->ballPos[0] = 240;
	game->ballPos[1] = 160;
	
	game->ballVel[0] = 5;
	game->ballVel[1] = 0;
	
	game->Apos = 160;
	game->Bpos = 160;
}

