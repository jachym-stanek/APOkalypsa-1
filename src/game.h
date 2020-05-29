//header file for game.c

#include <stdbool.h>

#define PAD_SPEED 8
#define BALL_INIT_X 240
#define BALL_INIT_Y 160
#define PAD_INIT_POS 160
#define INIT_X_VEL 9

#define MAX_PTS 8

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
	
	int rounds;
} game_struct;

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

//change the paddle positions based on the knob input
void update_paddles(game_struct *game);

/*
* Checks for collisions with:
* the paddles and the top and botton edges of the screen
* adjusts the velocity accordingly
*/
void check_collisions(game_struct *game);

/*
* resets the ball and the paddles to default positions
* increases the ball speed by 2
*/
void reset(game_struct *game);

