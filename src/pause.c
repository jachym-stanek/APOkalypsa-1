#include <stdio.h>
#include "knobs.h"
#include <unistd.h>

#include "pause.h"

//operations to be done on pause
void pause_oper() {
	printf("The game has been paused!\n");
	sleep(1);
	while (!get_pause()) {}
	printf("The game has been unpaused!\n");
}
