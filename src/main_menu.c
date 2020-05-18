/* Main memu functions definitions */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "text_plot_lib.h"
#include "colors.h"


typedef struct {
	char * Player1_name;
	char * Player2_name;
	char tab_selected;
} menu_data_t;

// global menu data
menu_data_t MENU_DATA = {"Player1", "Player2", 'x'};


void change_player_name(char player){
	printf("Please enter Player%c's name\n", player);
	printf("No spaces allowed, maximum name length is 12!\n");
	// 12 is max size that can be displayed
	char new_name[12];
	scanf("%s", new_name);
	if (player == '1'){
		MENU_DATA.Player1_name = new_name;
	}
	if (player == '2'){
		MENU_DATA.Player2_name = new_name;
	}
	printf("Player%c's name changed to %s\n", player, new_name);
	// update name on screen
	// menu_graphics();
}


void start_game(void){
	// Hynkovo funkce
	printf("Game running\n");
}


void exit_program(void){
	printf("Exiting game\n");

	// change screen to black
	uint16_t * data = (uint16_t *) malloc(sizeof(uint16_t) * 320 * 480);
	for (int i = 0; i < 320; ++i){
		for (int j = 0; j < 480; ++j){
			data[i*480 + j] = BLACK_COLOR;
		}
	}

	display_data(data);
	exit(0);
}


void wrong_key(void){
	printf("WARNING: unexpected input\n");
	printf("To move in menu, please use '1', '2', '3', '4' ONLY!\n");
}


void welcome(void){
	printf("Game started\n");
	printf("Press '1' to change Player1 name\n");
	printf("Press '2' to change Player1 name\n");
	printf("Press '3' to start game\n");
	printf("Press '4' to exit game\n");
}


void menu_graphics(void){
	// plot 4 rectangles
	uint16_t * data = (uint16_t *) malloc(sizeof(uint16_t) * 320 * 480);
	for (int i = 0; i < 320; ++i){
		for (int j = 0; j < 480; ++j){
			if ( (j > 40 && j < 440) && ( (i > 7 && i < 78) || (i > 85 && i < 156)
			|| (i > 161 && i < 232) || (i >= 239 && i < 310) ) ){
				data[i*480 + j] = RED_COLOR;
			}
			else{
				data[i*480 + j] = BLACK_COLOR;
			}
		}
	}

	display_data(data);
}


void menu_startup(void){
	welcome();
	
	// menu gui plot
	// CHANGE THIS LATER TO CONTAIN TEXT //
	menu_graphics();
	char in;

	// main menu loop
	while ( (in = getchar()) ){
		switch (in) {
			case '1':
			case '2':
				change_player_name(in);
				break;
			case '3':
				start_game();
				break;
			case '4':
				exit_program();
				break;
			case '\n':
				break;
			default:
				wrong_key();
				break;
		}
	}

}

