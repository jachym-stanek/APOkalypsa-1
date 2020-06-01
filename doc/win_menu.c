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

  	if (!knobs_init()){
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


void blink_win_leds(void){
	unsigned int color;
	struct timespec delay = {.tv_sec = 0, .tv_nsec = 300*1000*1000};

	color = ORANGE_COLOR;
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB1_o) = color;
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB2_o) = color;
	color = BLUE_COLOR;
	clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB1_o) = color;
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB2_o) = color;
	color = GREEN_COLOR;
	clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB1_o) = color;
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB2_o) = color;
	color = RED_COLOR;
	clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB1_o) = color;
	*(volatile uint32_t*)(parled_mem_base + SPILED_REG_LED_RGB2_o) = color;
	clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
}


void end_game_loop(game_struct * game){
	// setup graphics
	if (!init_perifs_win()){
		fprintf(stderr, "ERROR: Could not initialize memory for periferies!\n");
		exit(-1);
	}
	if (game->Apts > game->Bpts){
		winner = game->Aname;
	}
	else{
		winner = game->Bname;
	}
	win_graphics();

	// wait for signal to leave menu
	int t;
	unsigned char in;


	while (true){
		t = getc_timeout(STDIN_FILENO, READ_TIMEOUT, &in);

		if (get_pause()){
			menu_startup();
		}

		else if (t == 1){
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

		else{
			blink_win_leds();
		}
	}
}
