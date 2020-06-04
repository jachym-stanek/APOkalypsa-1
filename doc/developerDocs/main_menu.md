### P_NAME_LEN

Maximum allowed player name lenght
Is set to 12 to allow names to fil on LCD

### structure menu_data_t

Data holder for main menu instance
Holds Player1 and Player2 custom names,
currently selected menu tab, last knob position (for movement in menu with knob)

## bool init_perifs(void)

Initilizes and maps board periferies into memory
Initializes default player names
Returns false if something went wrong, true otherwise

## void change_player_name(char player)

Changes name for selected player
Takes input from stdin

## void start_game(void)

Starts the game loop, after game loop finishes starts victory screen loop

## void exit_program(void)

Exits program

## void wrong_key(void)

Raises warning to stdout notifying user about unexpected stdin input 

## void welcome(void)

Creates menu startup message, initializes knob position

## void info(void)

Displays info of app control onto stdout

## void menu_text(uint16_t * data)

Updates text to be ploted on LCD

## void menu_graphics(void)

Updates GUI of main menu

## void light_leds(void)

Indicates selected tab by different color on LEDs

## void menu_startup(void)

Main GUI loop, handles user inputs and responds to them

