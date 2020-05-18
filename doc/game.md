**MAX_SCORE_SUM**

When the sum of both player's scores reaches this number, the game ends.

It is 32, because the score of each player is shown on "his" side of the LED strip which has 32 LEDs on it.

### structure gameStruct

This structure contains the current state of the game.

* `int Apts`- player A points
* `int Bpts` - player B points
* `int Apos` - vertical position of player A's paddle
* `int Bpos` - vertical position of player B's paddle
	* the horizontal position of the paddles is fixed and defined in [gameGraphics.h](gameGraphics.md)
* `int ballPos[2]` - two element vector of the position of the ball
* `int ballVel[2]` - two element vector of the velocity of the ball

## void PlayGame()

The gameStruct with the initial game data is initialized by calling the setupData function. Then it starts the gameLoop function. After it is done, based on the return value it calls the necessary game-ending function.

## int gameLoop(gameStruct *game)

This function handles the main operation of the game. **Will be elaborated upon.**

## void setupData(gameStruct *game)

This function sets the gameStruct to the initial state
