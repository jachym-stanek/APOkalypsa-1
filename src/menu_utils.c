#include <stdlib.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "menu_utils.h"



void display_data(uint16_t * data, unsigned char * parlcd_mem_base){
 	for (int i = 0; i < 320 ; i++) {
	    for (int j = 0; j < 480 ; j++) {
    	 	parlcd_write_data(parlcd_mem_base, data[i*480 + j]);
	    }
 	}

 	free(data);
}
