//This file handles the game logic
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "gameGraphics.h"
#include "PONG.h"
#include "knobs.h"
#include "pause.h"

//starts the game and handles the end
int play_game(char * P1_name, char * P2_name) {
	game_struct game;
	setup_data(&game);
	
	bool end = false;
	int status = GAME;
	while (!end) {
		int check = game_loop(&game);
		switch (check) {
			case A_SCORED:
				game.Apts++;
				printf("%s scored!\n", P1_name);
				reset(&game);
				show_goal();
				
				if (game.Apts >= MAX_PTS) {
					end = true;
					status = A_WON;
				}
				break;
				
			case B_SCORED:
				game.Bpts++;
				printf("%s scored!\n", P2_name);
				reset(&game);
				show_goal();
				
				if (game.Bpts >= MAX_PTS) {
					end = true;
					status = B_WON;
				}
				break;
				
			case PAUSE:
				pause_oper();
				break;
			default:
				break;
		}
	}
		
	return status;
}

//main function for playing the game
int game_loop(game_struct *game) {
	disp_game(game->Apts, game->Bpts, game->Apos, game->Bpos, game->ballPos);
	countdown();
	game->Aold = get_paddle_pos('a');
	game->Bold = get_paddle_pos('b');
	int status = GAME;
	struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 500000};
	while (status == GAME) {
		if (get_pause()) {
			status = PAUSE;
			break;
		}
	
		status = update(game);
		disp_game(game->Apts, game->Bpts, game->Apos, game->Bpos, game->ballPos);
		clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
	}
	
	return status;
}

//This function prepares the game data
void setup_data(game_struct *game) {
	game->Apts = 0;
	game->Bpts = 0;
	
	game->ballPos[0] = BALL_INIT_X;
	game->ballPos[1] = BALL_INIT_Y;
	game->dA = 0;
	game->dB = 0;
	
	game->ballVel[0] = INIT_X_VEL;
	game->ballVel[1] = 0;
	
	game->Apos = PAD_INIT_POS;
	game->Bpos = PAD_INIT_POS;
	
	game->rounds = 0;
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
	if ((game->ballPos[0]-BALL_RAD) >= DISP_WIDTH) {
		return A_SCORED;
	} else if ((game->ballPos[0]+BALL_RAD) <= 0) {
		return B_SCORED;
	} else {
		return GAME;
	}
}

//change the paddle positions based on the knob input
void update_paddles(game_struct *game) {
	short Anow = get_paddle_pos('a');
	short Bnow = get_paddle_pos('b');
	
	game->dA = game->Aold - Anow;
	game->dA = game->dA > 200 ? ((255-game->Aold)+Anow) : game->dA; //stabilization of crossing the knob max overflow max->min
	game->dA = game->dA < -200 ? -1*((255-Anow)+game->Aold) : game->dA; //stabilization of crossing the knob max overflow max<-min
 	game->Aold = Anow;
	game->dB = game->Bold - Bnow;
	game->dB = game->dB > 200 ? ((255-game->Bold)+Bnow): game->dB;	//stabilization of crossing the knob max overflow max->min
	game->dB = game->dB < -200 ? -1*((255-Bnow)+game->Bold) : game->dB; //stabilization of crossing the knob max overflow max<-min
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
	//pad A from the front
	if ((game->ballPos[0]-BALL_RAD) <= (PAD_OFFSET+PAD_WIDTH) &&
		 game->ballPos[1] > (game->Apos-(PAD_HEIGHT/2)) &&
		 game->ballPos[1] < (game->Apos+(PAD_HEIGHT/2)) &&
		 game->ballVel[0] < 0 && 
		 (game->ballPos[0]-BALL_RAD) > GOAL_TOLERANCE) {
		 
		game->ballVel[0] *= -1;
		game->ballVel[1] += game->dA;
		 
	//pad B from the font
	} else if ((game->ballPos[0]+BALL_RAD) >= (DISP_WIDTH-(PAD_OFFSET+PAD_WIDTH)) &&
		 		  game->ballPos[1] > (game->Bpos-(PAD_HEIGHT/2)) &&
		 		  game->ballPos[1] < (game->Bpos+(PAD_HEIGHT/2)) &&
		 		  game->ballVel[0] > 0 &&
		 		  (game->ballPos[0]+BALL_RAD) < (DISP_WIDTH-GOAL_TOLERANCE)) {
		game->ballVel[0] *= -1;
		game->ballVel[1] += game->dB;
		 
	// bottom and top sides
	} else if (((game->ballPos[1]-BALL_RAD) <= 0 &&
					game->ballVel[1] < 0) ||
					((game->ballPos[1]+BALL_RAD) >= DISP_HEIGHT &&
					game->ballVel[1] > 0)) {
		game->ballVel[1] *= -1;
		
	}
}

/*
* resets the ball and the paddles to default positions
* increases the ball speed by 2
*/
void reset(game_struct *game) {
	game->rounds++;
	game->Apos = PAD_INIT_POS;
	game->Bpos = PAD_INIT_POS;
	game->ballPos[0] = BALL_INIT_X;
	game->ballPos[1] = BALL_INIT_Y;
	game->ballVel[0] = INIT_X_VEL + 2*game->rounds;
	game->ballVel[1] = 0;
	disp_game(game->Apts, game->Bpts, game->Apos, game->Bpos, game->ballPos);
}

