/* functions for ploting text to LCD */


#include <stdbool.h>
#include <stdint.h>

#include "font_types.h"


int char_width(font_descriptor_t* fdes, int ch);

void plot_char(int x, int y, font_descriptor_t* fdes, char ch, uint16_t *data, uint16_t color, int size);

void plot_text(int x, int y, int num_chars, char text[num_chars], uint16_t *data, uint16_t color, int size);
