//header file for pause.c

#include <stdbool.h>

#include "game.h"

typedef struct {
	char tab;
	bool end;
	int last_knob_pos;
} pause_data_t;


bool init_perifs_pause(void);

void back_to_menu(void);

void pause_graphics(void);

void wrong_key_pause(void);

void info_pause(void);

void light_leds_pause(void);

void tab_pressed_pause(void);

//operations to be done on pause
void pause_oper(game_struct * game);

void tab_pressed_pause(void);

void pause_loop(void);

