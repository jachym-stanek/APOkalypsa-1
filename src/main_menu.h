/* Declarations for main menu library */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define P_NAME_LEN 12

// menu data struct
typedef struct {
	char * Player1_name;
	char * Player2_name;
	char tab; 	// currently selected tab
	int last_knob_pos; 	// last knob position when tab was changed
} menu_data_t;


bool init_perifs(void);

void change_player_name(char player);

void start_game(void);

void exit_program(void);

void wrong_key(void);

void welcome(void);

void info(void);

void menu_text(uint16_t * data);

void tab_pressed(void);

void menu_graphics(void);

void light_leds(void);

void menu_startup(void);
