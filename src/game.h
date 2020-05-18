//header file for game.c

#define MAX_SCORE_SUM 32

//the structure for storing the current state of the game
typedef struct {
	int Apts;
	int Bpts;
	
	int Apos;
	int Bpos;
	
	int ballPos[2];
	int ballVel[2];
} gameStruct;

//starts the game and handles the end
void playGame();

//main function for playing the game
int gameLoop(gameStruct *game);

//sets the gameStruct to the initial state
void setupData(gameStruct *game);

