
**PAD_SPEED 8** - the change of the knobs is multiplied by this number when paddle movements are being caluclated

**BALL_INIT_X 240** - the initial horizonal position of the ball

**BALL_INIT_Y 160** - the initial vertical position of the ball

**PAD_INIT_POS 160** - the initial position of the paddles

**INIT_X_VEL 9** - the horizontal velocity of the ball at the start of the game

**MAX_PTS 8** - when one of the players reaches this number, they win

### structure game_struct

This structure contains the current state of the game.

* `int Apts`- player A points
* `int Bpts` - player B points
* `int Apos` - vertical position of player A's paddle
* `int Bpos` - vertical position of player B's paddle
	* the horizontal position of the paddles is fixed and defined in [gameGraphics.h](gameGraphics.md)
* `int Aold` - the position of paddle A in the previous round
* `int Bold` - the position of paddle B in the previous round
* `int dA` - change in paddle A position
* `int dB` - change in paddle B position
* `int ballPos[2]` - two element vector of the position of the ball
* `int ballVel[2]` - two element vector of the velocity of the ball
* `int rounds` - the number of played rounds

## void play_game()

The gameStruct with the initial game data is initialized by calling the setupData function. Then it starts the gameLoop function and hadles its return values - processes goals, pauses and ends the game.

## int game_loop(gameStruct *game)

This function handles the main operation of the game. Periodically calls the function update, until a goal is scored or the pause button is pushed. It returns a value from [status] (Docs.md) enum, based on the event that interrupted its operation.

## void setup_data(gameStruct *game)

This function sets the gameStruct to the initial state

## int update(game_struct *game)

Controlls the game state update - ball and paddle positions, goal detection

## int check_goals(game_struct *game)

Checks if a goal was scored.

## void update_paddles(game_struct *game)

Updates paddle positions based on the knob input

## void check_collisions(game_struct *game)

Checks for collisions of the ball with paddles and the top and bottom of the screen. Adjusts the ball velocity accordingly.

## void reset(game_struct *game)

Resets the ball nad paddles into their starting positions. Adds 2 to the horizontal ball velocity for every round played.
