//header file for gameGraphics.c

#define DISP_WIDTH 480
#define DISP_HEIGHT 320

#define PAD_HEIGHT 90
#define PAD_WIDTH 20
#define PAD_OFFSET 30

#define BALL_RAD 15

//sets up the memory addresses for displaying
int disp_setup();

//sets the LCD to black and turns off all LEDs
void clean_slate();

//displays the current game state on the LCD and LED strip
void disp_game(int Apts, int Bpts, int Apad, int Bpad, int ball[]);

//prepares the image to be displayed on the LCD
void prep_image(uint16_t *buffer, int Apad, int Bpad, int ball[]);

//sends the image in buffer to the LCD
void display(uint16_t *buffer);

//checks, if a pixel is part of a paddle
int is_paddle(int Apad, int Bpad, int row, int col);

//checks, if a pixel is part of the ball
int is_ball(int ball[], int row, int col);

//shows the score on the LED strip
void show_score(int Apts, int Bpts);

//plays the goal sequence
void show_goal();

//move 4 leds from right to left
void right_slide();

//move 4 leds from left to right
void left_slide();

//switch_colors on both RGB LEDs
void blink_both_RGB();

//blink RGB LEDs as start lights
void countdown();
