/* definitions of text plotting functions */

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#include "text_plot_lib.h"
#include "font_types.h"


int char_width(font_descriptor_t* fdes, int ch){
  int width = 0;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    ch -= fdes->firstchar;
    if (!fdes->width) {
      width = fdes->maxwidth;
    } else {
      width = fdes->width[ch];
    }
  }
  return width;
}


void plot_char(int x, int y, font_descriptor_t* fdes, char ch, uint16_t *data, uint16_t color, int size){
	int w = char_width(fdes, ch);

	for (int i = 0; i < 16; ++i){
		for (int j = 0; j < w; ++j){
			uint16_t bit_num = fdes->bits[(ch-0x20)*16 + i]; 	// bit map off set - char + row
			// if jth bit in bitnum is 1
			if ( (bit_num >> (fdes->maxwidth + 1 - j)) & 1 ){
				// scale pixels by text size
				for (int pix_y = 0; pix_y < size; ++pix_y){
					for (int pix_x = 0; pix_x < size; ++pix_x){
						int x_coord = x+j*size+pix_x;
						int y_coord = y+i*size+pix_y;
						if (x_coord>=0 && x_coord<480 && y_coord>=0 && y_coord<320){
							data[x_coord + 480*y_coord] = color;
						}
					}
				}
			}
		}
	}
}


void plot_text(int x, int y, int num_chars, char text[num_chars], uint16_t *data, uint16_t color, int size){
	font_descriptor_t* fdes = &font_winFreeSystem14x16;
	int line_start = x;

	for (int i = 0; i < num_chars; ++i){
		// new line
		if (text[i] == '\n'){
			x = line_start;
			y += 16*size;
		}
		// draw char
		else{
			plot_char(x, y, fdes, text[i], data, color, size);
			x += char_width(fdes, text[i])*size;
		}
	}
}

