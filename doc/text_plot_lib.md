
## int char_width(font_descriptor_t* fdes, int ch)

Function for getting the char width (for char from font_prop14x16 mainly)
Inputs: font type and char
Return: font width for the char input char

## void plot_char(int x, int y, font_descriptor_t* fdes, char ch, uint16_t *data, uint16_t color, int size)

Function for drawing a char into pixel data array
Input: start position for drawing (x, y), font type, char ch = char to be drawn,
data = pixel array to be drawn into, color = color of text, size = size of text
Output: Will change color of pixels in data to match the shape of char, changed color will
be the input color, no background gets added

## void plot_text(int x, int y, int num_chars, char text[num_chars], uint16_t *data, uint16_t color, int size)

Function for drawing text to pixel array
Input: takes text start positions (x, y), num_chars = length of text, text = char array/string
data = pixel array to be drawn into, color = color of text, size = size of text
text array must be either char array or string (in this case num_chars should not count '\0')
text array can contain '\n' character, this character will not be drawn but will cause
following txt to be drawn on new line
Output: Will perform plot_char() for each char in text array, see function above

