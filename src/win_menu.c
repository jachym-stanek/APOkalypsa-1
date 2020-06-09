#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "win_menu.h"
#include "text_plot_lib.h"
#include "knobs.h"
#include "menu_utils.h"
#include "non_block.h"
#include "main_menu.h"
#include "colors.h"
#include "PONG.h"


char * winner;
// LCD and LED memory bases
unsigned char *parlcd_mem_base;
unsigned char *parled_mem_base;


bool init_perifs_win(void){
	parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  	if (parlcd_mem_base == NULL) {
    	return false;
  	}
  
 	parled_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  	if (parled_mem_base == NULL) {
    	return false;
  	}
 	return true;
}


void win_graphics(void){
	// color background
	uint16_t * data = (uint16_t *) malloc(sizeof(uint16_t) * 320 * 480);
	for (int i = 0; i < 320; ++i){
		for (int j = 0; j < 480; ++j){
			data[i*480 + j] = BLACK_COLOR_LCD;
		}
	}
	plot_text(25, 70, strlen(winner), winner, data, RED_COLOR_LCD, 5);
	char * t = "WON";
	plot_text(25, 160, 3, t, data, RED_COLOR_LCD, 5);

	display_data(data, parlcd_mem_base);
}


void blink_win_leds(int mode){
	unsigned int color;
	struct timespec delay = {.tv_sec = 0, .tv_nsec = 200*1000*1000};

	if (mode == 0){
		color = ORANGE_COLOR;	
	}
	if (mode == 1){
		color = BLUE_COLOR;
	}
	if (mode == 2){
		color = GREEN_COLOR;
	}
	if (mode == 3){
		color = RED_COLOR;
	}

	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB1_o) = color;
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB2_o) = color;
	clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
}


void end_game_loop(char * won){
	// wait for knob button to be released
	struct timespec delay = {.tv_sec = 0, .tv_nsec = 200*1000*1000};
	clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);

	printf("%s won\n", won);
	int mode = 0;

	// setup graphics
	if (!init_perifs_win()){
		fprintf(stderr, "ERROR: Could not initialize memory for periferies!\n");
		exit(-1);
	}
	
	winner = won;
	
	win_graphics();

	// wait for signal to leave menu
	int t;
	unsigned char in;


	while (true){
		t = getc_timeout(STDIN_FILENO, READ_TIMEOUT, &in);

		if (t == 1){
			if (in == 'q'){
				menu_startup();
			}
			else if (in == '\n'){
				// do nothing
			}
			else{
				printf("Press 'q' to return to menu\n");
			}
		}

		else if (get_pause()){
			menu_startup();
		}

		else{
			blink_win_leds(mode);
			mode = (mode + 1) % 4;
		}
	}
}
