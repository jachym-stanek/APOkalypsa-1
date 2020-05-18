//This file handles the game logic
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "game.h"
#include "gameGraphics.h"

//starts the game and handles the end
void play_game() {
	game_struct game;
	setup_data(&game);
	
	int check = game_loop(&game);
	
	if (check == 1) {
		printf("Player A won\n");
	} else if (check == 2) {
		printf("Player B won\n");
	} else {
		printf("Unforseen outcome\n");
	}
}

//main function for playing the game
int game_loop(game_struct *game) {
	disp_game(game->Apts, game->Bpts, game->Apos, game->Bpos, game->ballPos);
	printf("Game loop would start now\n");
	return 0;
}

//This function prepares the game data
void setup_data(game_struct *game) {
	game->Apts = 0;
	game->Bpts = 0;
	
	game->ballPos[0] = 240;
	game->ballPos[1] = 160;
	
	game->ballVel[0] = 5;
	game->ballVel[1] = 0;
	
	game->Apos = 160;
	game->Bpos = 160;
}

