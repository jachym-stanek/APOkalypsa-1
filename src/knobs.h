//the header file for knobs.c
#include <stdbool.h>

unsigned char *mem_base;

//initialize the memory
bool knobs_init();

//returns the knob position for the specified paddle
short get_paddle_pos(char paddle);

//checks if the middle knob is pressed
bool get_pause();
