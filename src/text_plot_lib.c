/* definitions of text plotting functions */

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"


/* display data onto LCD 
 * data = array of size 320x480
 */
void display_data(uint16_t * data){
	// map display
	unsigned char *parlcd_mem_base;
	parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
	if (parlcd_mem_base == NULL)
	exit(1);

 	parlcd_hx8357_init(parlcd_mem_base);
 	parlcd_write_cmd(parlcd_mem_base, 0x2c);

 	// display text
 	for (int i = 0; i < 320 ; i++) {
	    for (int j = 0; j < 480 ; j++) {
    	 	parlcd_write_data(parlcd_mem_base, data[i*480 + j]);
	    }
 	}

 	free(data);
}


bool plot_text_grid(int num_chars, uint32_t text[num_chars], int start_pos[2], int size, 
					unsigned int background_color, unsigned int text_color, 
					unsigned int text_background_color) {
	font_descriptor_t font = font_rom8x16;
	uint16_t * text_data = (uint16_t *) malloc(sizeof(uint16_t) * 320 * 480);

	int x = 0;		// how many char cells were done
	int pix = 0;

	// for cell in grid
	for (int i = 0; i < 320/font.height/size; i++) {
		for (int j = 0; j < 480/font.maxwidth/size; j++) {

			// for pixel cell
			bool contains_char = false; 	// does cell contain char
			if ( (x >= 1 && x < num_chars) || (start_pos[0] == i && start_pos[1] == j) ){
				contains_char = true;
				x += 1;
			}

			for (int cell_row = 0; cell_row < font.height; cell_row++) {
		    	for (int cell_col = 0; cell_col < font.maxwidth; cell_col++) {

		    		// for nxn pixel (if size is > 1)
		    		for (int rw = 0; rw < size; ++rw){
		    			for (int cl = 0; cl < size; ++cl){
		    				int offset = (i*font.height*size+cell_row+rw)*480 + j*size*font.maxwidth+cell_col+cl;
		    				printf("Attempting offset %d\n", offset);
		    				// if any xth num should be in this cell
					    	if (contains_char){
					    		// if cell_rowth bit of cell_colth bit map number is 1, color bit 
					    		uint16_t bit_map_num = font.bits[text[x]+cell_row];
					    		if ( (bit_map_num >> (font.maxwidth - 1 - cell_col+8)) & 1 ){
					    			text_data[offset] = text_color;
					    		}
					    		else{
				    				text_data[offset] = text_background_color;
					    		}
					    	}
				    	 	else{
				    	 		text_data[offset] = background_color;
				    	 	}

				    	 	pix += 1;
	    	 			}
	    			}	
	    		}		
		    }
	    }
 	}

 	// could not plot all chars
 	if (x < num_chars){
 		printf("WARNING: Could not plot all chars\n");
 		return false;
 	}

 	printf("Went through %d pixels, display is %d pixels\n", pix, 480*320);
	display_data(text_data);
	return true;
}


