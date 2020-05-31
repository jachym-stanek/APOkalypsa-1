
### structure menu_data_t

Data holder for main menu instance
Holds Player1 and Player2 custom names and currently selected menu tab

## bool init_perifs(void)

Initilizes and maps board periferies into memory

## void display_data(uint16_t * data)

Displays data from uint16_t array onto LCD
data must be of size 320x480

## void change_player_name(char player)

Changes name for selected playe
Takes input from stdin

## void start_game(void)

Ends menu instace and starts game loop

## void exit_program(void)

Exits program

## void wrong_key(void)

Raises warning to stdout notifying user about unexpected stdin input 

## void welcome(void)

Creates menu startup message

## void info(void)

Displays info of app control onto stdout

## void menu_text(uint16_t * data)

Updates text to be ploted on LCD

## void menu_graphics(void)

Updates GUI of main menu

## void light_leds(void)

Indicates selected tab by different color on LEDs

## void menu_startup(void)

Main GUI loop

