**DISP_WIDTH** - the width of the LCD screen
**DISP_HEIGHT** - the height of the LCD screen
**PAD_HEIGHT** - the height of a paddle
**PAD_WIDTH** - the width of a paddle
**PAD_OFFSET** - the distance between a paddle and the edge of the screen
**BALL_RAD** - the radius of the ball

### int dispSetup()

Sets up the memory addresses for printing data to the LCD sreen.

### void cleanSlate()

Turns the LCD sreen black and turns off all LEDs

## void dispGame(int Apts, int Bpts, int Apad, int Bpad, int ball[])

Displays the position of ball and paddles on the LCD screen and the score of each player on the LED strip

## void prepImage(uint16_t *buffer, int Apad, int Bpad, int ball[])

Writes an image of the game state to the `*buffer`.

## void display(uint16_t *buffer)

Displays whatever is in the `*buffer` to the LCD sreen.

## int isPaddle(int Apad, int Bpad, int row, int col)

If pixel in row - `row` and column - `col` is part of an image of a paddle returns 1, othervise returns 0

## int isBall(int ball[], int row, int col);

If pixel in row - `row` and column - `col` is part of the image of the ball returns 1, othervise returns 0

## void showScore(int Apts, int Bpts)

Lights up `Apts` LEDs on the left side and `Bpts` LEDs on the right side of the LED strip.

## void show_goal()

Plays a blinking sequence when a goal is scored

## void right_slide()

4 LEDs slide from right to left on the LED strip

## void left_slide()

4 LEDs slide from left to right on the LED strip

## void blink_both_RGB()

Both RGB LEDs blink red, green and blue

## void countdown()

Flashes the RGB LEDs white as start countdown
