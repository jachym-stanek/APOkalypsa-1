//header file for game.c

#include <stdbool.h>

#define MAX_SCORE_SUM 32
#define PAD_SPEED 8

//the structure for storing the current state of the game
typedef struct {
	int Apts;
	int Bpts;
	
	int Apos;
	int Bpos;
	short Aold;
	short Bold;
	int dA;
	int dB;
	
	int ballPos[2];
	int ballVel[2];
} game_struct;

unsigned char *mem_base;

//starts the game and handles the end
int play_game();

//main function for playing the game
int game_loop(game_struct *game);

//sets the gameStruct to the initial state
void setup_data(game_struct *game);

//update the game state
int update(game_struct *game);

//checks if goal was scored
int check_goals(game_struct *game);

//returns the knob position for the specified paddle
short get_paddle_pos(char paddle);

//checks if the middle knob is pressed
bool get_pause();

//change the paddle positions based on the knob input
void update_paddles(game_struct *game);

/*
* Checks for collisions with:
* the paddles and the top and botton edges of the screen
* adjusts the velocity accordingly
*/
void check_collisions(game_struct *game);

