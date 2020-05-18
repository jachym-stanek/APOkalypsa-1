/* Declarations of functions for ploting text to LCD */


#include <stdbool.h>
#include <stdint.h>

/* displays array of size 480*320 on LCD */ 
void display_data(uint16_t * data);


/* Plots text into grid with cells of maxfondwidth and height 
 * returns true on success otherwise flase
 * num_chars = number of chars in text
 * text = array of chars to plot
 * start_pos = position in grid (e.g. {0,5}) where to start text plotting
 * size = size of text (1... smallest), only include size that can divide 480 and 320!
 */
bool plot_text_grid(int num_chars, uint32_t text[num_chars], int start_pos[2], int size, 
					unsigned int background_color, unsigned int text_color);
