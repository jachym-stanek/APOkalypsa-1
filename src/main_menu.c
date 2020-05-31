/* Main memu functions definitions */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "main_menu.h"
#include "text_plot_lib.h"
#include "colors.h"
#include "knobs.h"
#include "game.h"
#include "PONG.h"
#include "gameGraphics.h"


// global menu data
menu_data_t MENU_DATA = {.tab = '3'};

// LCD and LED memory bases
unsigned char *parlcd_mem_base;
unsigned char *parled_mem_base;


bool init_perifs(void){
	parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  	if (parlcd_mem_base == NULL) {
    	return false;
  	}
  
 	parled_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  	if (parled_mem_base == NULL) {
    	return false;
  	}
  	
  	MENU_DATA.Player1_name = (char*)malloc((P_NAME_LEN+1)*sizeof(char));
  	MENU_DATA.Player2_name = (char*)malloc((P_NAME_LEN+1)*sizeof(char));
  	if (MENU_DATA.Player1_name == NULL ||MENU_DATA.Player2_name == NULL) {
  		return false;
  	}
  	
  	strcpy(MENU_DATA.Player1_name, "Player 1");
  	strcpy(MENU_DATA.Player2_name, "Player 2");
  	
 	return true;
}


void display_data(uint16_t * data){
 	// display text
 	for (int i = 0; i < 320 ; i++) {
	    for (int j = 0; j < 480 ; j++) {
    	 	parlcd_write_data(parlcd_mem_base, data[i*480 + j]);
	    }
 	}

 	free(data);
}


void change_player_name(char player){
	printf("Please enter Player%c's name\n", player);
	printf("No spaces allowed, maximum name length is %d!\n", P_NAME_LEN);
	// 12 is max size that can be displayed
	static char new_name[P_NAME_LEN+1];

	scanf("%12s", new_name);

	if (player == '1'){
		strcpy(MENU_DATA.Player1_name, new_name);
	}
	else if (player == '2'){
		strcpy(MENU_DATA.Player2_name, new_name);
	}
	else{
		fprintf(stderr, "WARNING: Function 'change_player_name' takes wrong argument!\n");
	}
	
	char g;
	while ( (g = getchar()) != '\n') {};	// discard garbage from people who can't read

	printf("Player%c's name changed to %s\n", player, new_name);
	// update name on screen
	menu_graphics();
}


void start_game(void){
	int status = play_game();
	
		
	if (status == A_WON) {
		printf("Player A won!\n");
	} else if (status == B_WON) {
		printf("Player B won!\n");
	} else {
		printf("Unexpected outcome!\n");
	}
}


void exit_program(void){
	printf("Exiting game\n");
	clean_slate();
	free(MENU_DATA.Player1_name);
	free(MENU_DATA.Player2_name);
	exit(0);
}


void wrong_key(void){
	printf("WARNING: unexpected input\n");
	printf("To move in menu, please use '1', '2', '3', '4', 'h' ONLY!\n");
}


void welcome(void){
	info();
	MENU_DATA.last_knob_pos = get_paddle_pos('a');
}


void info(void){
	printf("Press '1' to change Player1 name\n");
	printf("Press '2' to change Player1 name\n");
	printf("Press '3' to start game\n");
	printf("Press '4' to exit game\n");
	printf("Press 'h' to get help\n");
}


void menu_text(uint16_t * data){
	// player1 name
	plot_text(60, 22, strlen(MENU_DATA.Player1_name), MENU_DATA.Player1_name, data, WHITE_COLOR_LCD, 3);
	printf("Pl1 name: %s\n", MENU_DATA.Player1_name);

	// player2 name
	plot_text(60, 98, strlen(MENU_DATA.Player2_name), MENU_DATA.Player2_name, data, WHITE_COLOR_LCD, 3);
	printf("Pl2 name: %s\n", MENU_DATA.Player2_name);

	// start game
	char * text = "Start Game";
	int l = 10;
	plot_text(60, 174, l, text, data, WHITE_COLOR_LCD, 3);

	text = "Exit";
	l = 4;
	// exit
	plot_text(60, 250, l, text, data, WHITE_COLOR_LCD, 3);
}


void menu_graphics(void){
	// plot 4 rectangles
	uint16_t * data = (uint16_t *) malloc(sizeof(uint16_t) * 320 * 480);
	for (int i = 0; i < 320; ++i){
		for (int j = 0; j < 480; ++j){
			if (j > 40 && j < 440){
				// player 1
				if (i > 15 && i < 76){
					if (MENU_DATA.tab == '1'){
						data[i*480 + j] = BLACK_COLOR_LCD;
					}
					else{
						data[i*480 + j] = BROWN_COLOR_LCD;
					}
				}
				// player 2
				else if (i > 91 && i < 152){
					if (MENU_DATA.tab == '2'){
						data[i*480 + j] = BLACK_COLOR_LCD;
					}
					else{
						data[i*480 + j] = BROWN_COLOR_LCD;
					}
				}
				// start game
				else if (i > 167 && i < 228){
					if (MENU_DATA.tab == '3'){
						data[i*480 + j] = BLACK_COLOR_LCD;
					}
					else{
						data[i*480 + j] = BROWN_COLOR_LCD;
					}
				}
				// quit game
				else if (i > 243 && i < 304){
					if (MENU_DATA.tab == '4'){
						data[i*480 + j] = BLACK_COLOR_LCD;
					}
					else{
						data[i*480 + j] = BROWN_COLOR_LCD;
					}
				}
				// space between tabs
				else{
					data[i*480 + j] = MENU_BACKGROUND_COLOR_LCD;
				}
			}
			else{
				data[i*480 + j] = MENU_BACKGROUND_COLOR_LCD;
			}
		}
	}


	menu_text(data);
	display_data(data);
	light_leds();
}


void light_leds(void){

	unsigned int color;
	if (MENU_DATA.tab == '1'){
		color = RED_COLOR;
	}
	else if (MENU_DATA.tab == '2'){
		color = ORANGE_COLOR;
	}
	else if (MENU_DATA.tab == '3'){
		color = BLUE_COLOR;
	}
	else if (MENU_DATA.tab == '4'){
		color = BLACK_COLOR;
	}
	else{
		color = WHITE_COLOR;
	}

	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB1_o) = color;
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB2_o) = color;
}


void tab_pressed(void){
	switch (MENU_DATA.tab){
		case '1':
		case '2':
			change_player_name(MENU_DATA.tab);
			break;
		case '3':
			start_game();
			break;
		case '4':
			exit_program();
			break;
		default:
			break;
	}
}


void menu_startup(void){
	// initialize memory
	if (!init_perifs()){
		fprintf(stderr, "ERROR: Could not initialize memory for preriferals!\n");
		exit(-1);
	}
	// initial protocol
	welcome();
	
	// initialize GUI
	menu_graphics();
	char in;

	// main menu loop
	while (1){
		// input from keyboard
		if ( (in = getchar()) ) {
			printf("Got input: %c\n", in);
			switch (in) {
				case '1':
				case '2':
				case '3':
				case '4':
					MENU_DATA.tab = in;	// tell program new position to fill
					menu_graphics();
					tab_pressed();
					break;
				case 'h':
					info();
					break;
				case '\n':
					break;
				default:
					wrong_key();
					break;
			}
		}


		// knob turn left = go up in menu
		else if (get_paddle_pos('a') < MENU_DATA.last_knob_pos - 15){
			if (MENU_DATA.tab != '1'){
				MENU_DATA.tab -= 1;
				menu_graphics();
				MENU_DATA.last_knob_pos = get_paddle_pos('a');
			}
		}

		// knob turn right = go down in menu
		else if (get_paddle_pos('a') > MENU_DATA.last_knob_pos + 15){
			if (MENU_DATA.tab != '4'){
				MENU_DATA.tab += 1;
				menu_graphics();
				MENU_DATA.last_knob_pos = get_paddle_pos('a');
			}
		}

		else if (get_pause()){
			tab_pressed();
		}
		
		else{
			// do nothing
		}
	}
}

