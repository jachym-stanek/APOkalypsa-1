//this file handles controlling on the LCD and LEDs for in-game purposes

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "gameGraphics.h"
#include "PONG.h"
#include "colors.h"
#include "game.h"

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"


unsigned char *lcd_mem_base;
unsigned char *led_mem_base;

//sets up the memory addresses for displaying
int disp_setup() {
	lcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  	if (lcd_mem_base == NULL) {
    	return DISP_ERR;
  	}
  
 	led_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  	if (led_mem_base == NULL) {
    	return DISP_ERR;
  	}
  	
  parlcd_hx8357_init(lcd_mem_base);
  parlcd_write_cmd(lcd_mem_base, 0x2c);
  
  return SUCCESS;
}

//sets the LCD to black and turns off all LEDs
void clean_slate() {
	//clear the LEDs
	*(volatile uint32_t*)(led_mem_base + SPILED_REG_LED_LINE_o) = BLACK_COLOR;
  	*(volatile uint32_t*)(led_mem_base + SPILED_REG_LED_RGB1_o) = BLACK_COLOR;
  	*(volatile uint32_t*)(led_mem_base + SPILED_REG_LED_RGB2_o) = BLACK_COLOR;
  	
  	//clear the LCD display
  	for (int i = 0; i < DISP_HEIGHT ; i++) {
    for (int j = 0; j < DISP_WIDTH ; j++) {
      	parlcd_write_data(lcd_mem_base, BLACK_COLOR);
    }
  }
}

//displays the current game state on the LCD and LED strip
void disp_game(int Apts, int Bpts, int Apad, int Bpad, int ball[]) {
	uint16_t *buffer = (uint16_t*)malloc(sizeof(uint16_t) * DISP_WIDTH * DISP_HEIGHT);
	prep_image(buffer, Apad, Bpad, ball);
	display(buffer);
	
	show_score(Apts, Bpts);
}

//prepares the image to be displayed on the LCD
void prep_image(uint16_t *buffer, int Apad, int Bpad, int ball[]) {
	unsigned int c;
	for (int row = 0; row < DISP_HEIGHT; row++) {
		for (int col = 0; col < DISP_WIDTH; col++) {
			if (is_paddle(Apad, Bpad, row, col)) {
				c = WHITE_COLOR;
			} else if (is_ball(ball, row, col)) {
				c = RED_COLOR;
			} else {
				c = LIGHT_BLUE_COLOR;
			}
			
			buffer[(row*DISP_WIDTH)+col] = c;
		}
	}
}

//sends the image in buffer to the LCD
void display(uint16_t *buffer) {
	for (int x = 0; x < (DISP_HEIGHT*DISP_WIDTH); x++) {
    	parlcd_write_data(lcd_mem_base, buffer[x]);
  }
}

//checks, if a pixel is part of a paddle
int is_paddle(int Apad, int Bpad, int row, int col) {
	if (PAD_OFFSET < col && col < (PAD_OFFSET + PAD_WIDTH)) {
		if ((Apad -(PAD_HEIGHT/2)) < row && row < (Apad +(PAD_HEIGHT/2))) {
			return 1;
		}
	} else if ((DISP_WIDTH - (PAD_OFFSET + PAD_WIDTH)) < col && col < (DISP_WIDTH - PAD_OFFSET)) {
		if ((Bpad -(PAD_HEIGHT/2)) < row && row < (Bpad +(PAD_HEIGHT/2))) {
			return 1;
		}
	}
	
	return 0;
}

//checks, if a pixel is part of the ball
int is_ball(int ball[], int row, int col) {
	int pos = (col - ball[0])*(col - ball[0]) + (row - ball[1])*(row - ball[1]);
	return pos <= (BALL_RAD*BALL_RAD);
}

//shows the score on the LED strip
void show_score(int Apts, int Bpts) {
	uint32_t dispVal = 0x0;
	
	for (int x = 1; x <= MAX_SCORE_SUM; x++) {
		if (x <= Apts || x > (MAX_SCORE_SUM-Bpts)) {
			dispVal += 1;
		}
		
		if (x != MAX_SCORE_SUM) {
			dispVal<<=1;
		}
	}
	
	*(volatile uint32_t*)(led_mem_base + SPILED_REG_LED_LINE_o) = dispVal;
}

