/* Declarations for main menu library */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/* changes Player #x name */
void change_player_name(int player);

/* end menu instace and start game loop */
void start_game(void);

/* exit program */
void exit_program(void);

/* unexpected input warning */
void wrong_key(void);

/* menu startup message */
void welcome(void);

/* creates graphics on LCD for menu */
void menu_graphics(void);

/* starts main menu gui */
void menu_startup(void);
