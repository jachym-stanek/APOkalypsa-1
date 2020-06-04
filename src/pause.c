#include <stdio.h>
#include "knobs.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "pause.h"
#include "text_plot_lib.h"
#include "colors.h"
#include "main_menu.h"
#include "menu_utils.h"
#include "non_block.h"


// LCD and LED memory bases
unsigned char *parlcd_mem_base;
unsigned char *parled_mem_base;

pause_data_t PAUSE_DATA;


bool init_perifs_pause(void){
	parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  	if (parlcd_mem_base == NULL) {
    	return false;
  	}
  
 	parled_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  	if (parled_mem_base == NULL) {
    	return false;
  	}

  	if (!knobs_init()){
  		return false;
  	}
 	return true;
}


void back_to_menu(void){
	printf("Returning back to menu\n");
	menu_startup();
}


void pause_graphics(void){
	// color background
	uint16_t * data = (uint16_t *) malloc(sizeof(uint16_t) * 320 * 480);
	for (int i = 0; i < 320; ++i){
		for (int j = 0; j < 480; ++j){
			if (i > 160 && i < 220 && j > 50 && j < 430){
				if (PAUSE_DATA.tab == '1'){
					data[i*480 + j] = BLACK_COLOR_LCD;
				}
				else{
					data[i*480 + j] = BROWN_COLOR_LCD;
				}				
			}
			else if (i > 240 && i < 300 && j > 50 && j < 430){
				if (PAUSE_DATA.tab == '2'){
					data[i*480 + j] = BLACK_COLOR_LCD;
				}
				else{
					data[i*480 + j] = BROWN_COLOR_LCD;
				}
			}
			else{
				data[i*480 + j] = MENU_BACKGROUND_COLOR_LCD;
			}
		}
	}

	char * t = "GAME PAUSED";
	plot_text(45, 30, 11, t, data, RED_COLOR_LCD, 4);

	t = "RESUME GAME";
	plot_text(86, 166, 11, t, data, WHITE_COLOR_LCD, 3);

	t = "BACK TO MENU";
	plot_text(86, 246, 12, t, data, WHITE_COLOR_LCD, 3);

	light_leds_pause();
	display_data(data, parlcd_mem_base);
}


void wrong_key_pause(void){
	printf("WARNING: unexpected input\n");
	printf("Press 'h' to get help\n");
}


void info_pause(void){
	printf("Press '1' resume game\n");
	printf("Press '2' return to main menu\n");
	printf("Press 'h' to get help\n");
}


void light_leds_pause(void){

	unsigned int color;
	if (PAUSE_DATA.tab == '1'){
		color = BLUE_COLOR;
	}
	else if (PAUSE_DATA.tab == '2'){
		color = RED_COLOR;
	}
	else{
		color = WHITE_COLOR;
	}

	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB1_o) = color;
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB2_o) = color;
}


void pause_oper(void){
	printf("The game has been paused!\n");
	PAUSE_DATA.tab = '1';
	PAUSE_DATA.end = false;
	init_perifs_pause();
	pause_graphics();
	pause_loop();
	printf("The game has been unpaused!\n");
}


void tab_pressed_pause(void){
	switch (PAUSE_DATA.tab){
		case '1':
			break;
		case '2':
			back_to_menu();
			break;
		default:
			break;
	}
	PAUSE_DATA.end = true;
}


void pause_loop(void){
	int t;
	unsigned char in;

	while (!PAUSE_DATA.end){
		// input from keyboard
		t = getc_timeout(STDIN_FILENO, READ_TIMEOUT, &in);

		if (t == 1){
			switch (in) {
				case '1':
				case '2':
					PAUSE_DATA.tab = in;	// tell probram new position to fill
					pause_graphics();
					tab_pressed_pause();
					break;
				case 'h':
					info_pause();
					break;
				case '\n':
					break;
				default:
					wrong_key_pause();
					break;
			}
		}


		// knob turn left = go up in menu
		else if (get_paddle_pos('c') < PAUSE_DATA.last_knob_pos - 15){
			if (PAUSE_DATA.tab != '1'){
				PAUSE_DATA.tab = '1';
				pause_graphics();			
			}
			PAUSE_DATA.last_knob_pos = get_paddle_pos('c');
		}

		// knob turn right = go down in menu
		else if (get_paddle_pos('c') > PAUSE_DATA.last_knob_pos + 15){
			if (PAUSE_DATA.tab != '2'){
				PAUSE_DATA.tab = '2';
				pause_graphics();
			}
			PAUSE_DATA.last_knob_pos = get_paddle_pos('c');
		}

		else if (get_pause()){
			tab_pressed_pause();
		}
		
		else{
			// do nothing
		}
	}
}

