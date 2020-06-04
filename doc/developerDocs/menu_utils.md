### READ_TIMEOUT

How long (miliseconds) should program wait for input before timeout

## void display_data(uint16_t * data, unsigned char * parlcd_mem_base)

Plots data arrays with pixel map to LCD, frees the data array
data must be uint16_t array of size 320x480 (to match LCD resolution)

