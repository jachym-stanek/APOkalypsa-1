//This file handles the game logic
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>

#include "game.h"
#include "gameGraphics.h"
#include "PONG.h"

#include "mzapo_phys.h"
#include "mzapo_regs.h"

//starts the game and handles the end
int play_game() {
	game_struct game;
	setup_data(&game);
	
	mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
	if (mem_base == NULL) {
		return MEM_ERR;
	}
	
	int check = game_loop(&game);
	
	if (check == 1) {
		printf("Player A won\n");
	} else if (check == 2) {
		printf("Player B won\n");
	} else {
		printf("Unforseen outcome\n");
	}
	
	return 0;
}

//main function for playing the game
int game_loop(game_struct *game) {
	game->Aold = get_paddle_pos('a');
	game->Bold = get_paddle_pos('b');
	disp_game(game->Apts, game->Bpts, game->Apos, game->Bpos, game->ballPos);
	
	printf("starting the game loop\n");
	while (!get_pause()) {
		int goal = update(game);
		disp_game(game->Apts, game->Bpts, game->Apos, game->Bpos, game->ballPos);
		if (goal == 1) {
			printf("Player A scored!\n");
			game->Apts++;
		} else if (goal == 2) {
			printf("Player B scored!\n");
			game->Bpts++;
		}
		printf("A: %d B: %d\n", game->Apts, game->Bpts);
		if ((game->Apts+game->Bpts) >= MAX_SCORE_SUM) {
			printf("The game has was won!\n");
			break;
		}
	}
	printf("Ending the loop\n");
	return 0;
}

//This function prepares the game data
void setup_data(game_struct *game) {
	game->Apts = 0;
	game->Bpts = 0;
	
	game->ballPos[0] = 240;
	game->ballPos[1] = 160;
	game->dA = 0;
	game->dB = 0;
	
	game->ballVel[0] = 5;
	game->ballVel[1] = 0;
	
	game->Apos = 160;
	game->Bpos = 160;
}

//update the game state
int update(game_struct *game) {
	update_paddles(game);	
	
	check_collisions(game);
	game->ballPos[0] += game->ballVel[0];
	game->ballPos[1] += game->ballVel[1];
	return check_goals(game);
}

//checks if goal was scored
int check_goals(game_struct *game) {
	if (game->ballPos[0] >= DISP_WIDTH) {
		return 1;
	} else if (game->ballPos[0] <= 0) {
		return 2;
	} else {
		return 0;
	}
}

//returns the knob position for the specified paddle
short get_paddle_pos(char paddle) {
	uint32_t knobs = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
	
	short ret = 0;
	if (paddle == 'a') {
		ret = knobs>>16;
		if ((ret>>8) != 0) {
			ret = ret - ((ret>>8)<<8);
		}
	} else if (paddle == 'b') {
		ret = (knobs<<16)>>16;
		if ((ret>>8) != 0) {
			ret = ret - ((ret>>8)<<8);
		}
	}
	
	return ret;
}

//checks if the middle knob is pressed
bool get_pause() {
	uint32_t knobs = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
	knobs = knobs>>24;
	return (knobs == 2);
}

//change the paddle positions based on the knob input
void update_paddles(game_struct *game) {
	short Anow = get_paddle_pos('a');
	short Bnow = get_paddle_pos('b');
	
	game->dA = game->Aold - Anow;
	game->Aold = Anow;
	game->dB = game->Bold - Bnow;
	game->Bold = Bnow;
	
	if ((game->Apos + (game->dA*PAD_SPEED)) > DISP_HEIGHT-(PAD_HEIGHT/2)) {
		game->Apos = DISP_HEIGHT-(PAD_HEIGHT/2);
	} else if ((game->Apos + (game->dA*PAD_SPEED)) < (PAD_HEIGHT/2)) {
		game->Apos = (PAD_HEIGHT/2);
	} else {
		game->Apos = game->Apos + (game->dA*PAD_SPEED);
	}
	
	if ((game->Bpos + (game->dB*PAD_SPEED)) > DISP_HEIGHT-(PAD_HEIGHT/2)) {
		game->Bpos = DISP_HEIGHT-(PAD_HEIGHT/2);
	} else if ((game->Bpos + (game->dB*PAD_SPEED)) < (PAD_HEIGHT/2)) {
		game->Bpos = (PAD_HEIGHT/2);
	} else {
		game->Bpos = game->Bpos + (game->dB*PAD_SPEED);
	}
}

/*
* Checks for collisions with:
* the paddles and the top and botton edges of the screen
* adjusts the velocity accordingly
*/
void check_collisions(game_struct *game) {
	//pad A
	if ((game->ballPos[0]-BALL_RAD) <= (PAD_OFFSET+PAD_WIDTH) &&
		 game->ballPos[1] > (game->Apos-(PAD_HEIGHT/2)) &&
		 game->ballPos[1] < (game->Apos+(PAD_HEIGHT/2))) {
		 
		game->ballVel[0] *= -1;
		game->ballVel[1] += game->dA;
		 
	//pad B
	} else if ((game->ballPos[0]+BALL_RAD) >= (DISP_WIDTH-(PAD_OFFSET+PAD_WIDTH)) &&
		 		  game->ballPos[1] > (game->Bpos-(PAD_HEIGHT/2)) &&
		 		  game->ballPos[1] < (game->Bpos+(PAD_HEIGHT/2))) {
		game->ballVel[0] *= -1;
		game->ballVel[1] += game->dB;
		 
	// bottom side
	} else if ((game->ballPos[1]-BALL_RAD) <= 0 ||
				  (game->ballPos[1]+BALL_RAD) >= DISP_HEIGHT) {
		game->ballVel[1] *= -1;
	}
}

