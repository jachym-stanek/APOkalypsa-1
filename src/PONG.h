//header file for PONG.c

//global "error" codes
#define SUCCESS 0
#define DISP_ERR 100
#define MEM_ERR 101
#define KNOBS_ERR 102

typedef enum {
	GAME,
	A_SCORED,
	B_SCORED,
	PAUSE,
	A_WON,
	B_WON
} status;

