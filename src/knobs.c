#include "knobs.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "mzapo_phys.h"
#include "mzapo_regs.h"

unsigned char *mem_base;

bool knobs_init() {
	mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
	if (mem_base == NULL) {
		return false;
	}
	return true;
}

//returns the knob position for the specified paddle
short get_paddle_pos(char paddle) {
	uint32_t knobs = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
	
	short ret = 0;
	
	if (paddle == 'a') {
		ret = knobs>>16;
	} else if (paddle == 'b') {
		ret = (knobs<<16)>>16;
	} else if (paddle == 'c'){
		ret = (knobs<<8);
		ret = ret>>8;
	} else {
		return -1;
	}
	
	if ((ret>>8) != 0) {
		ret = ret - ((ret>>8)<<8);
	}
	
	return ret;
}

//checks if the middle knob is pressed
bool get_pause() {
	uint32_t knobs = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);
	knobs = knobs>>24;
	return (knobs == 2);
}

