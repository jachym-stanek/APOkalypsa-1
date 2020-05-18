//header file for gameGraphics.c

#define DISP_WIDTH 480
#define DISP_HEIGHT 320

#define PAD_HEIGHT 90
#define PAD_WIDTH 20
#define PAD_OFFSET 30

#define BALL_RAD 15

//sets up the memory addresses for displaying
int dispSetup();

//sets the LCD to black and turns off all LEDs
void cleanSlate();

//displays the current game state on the LCD and LED strip
void dispGame(int Apts, int Bpts, int Apad, int Bpad, int ball[]);

//prepares the image to be displayed on the LCD
void prepImage(uint16_t *buffer, int Apad, int Bpad, int ball[]);

//sends the image in buffer to the LCD
void display(uint16_t *buffer);

//checks, if a pixel is part of a paddle
int isPaddle(int Apad, int Bpad, int row, int col);

//checks, if a pixel is part of the ball
int isBall(int ball[], int row, int col);

//shows the score on the LED strip
void showScore(int Apts, int Bpts);

