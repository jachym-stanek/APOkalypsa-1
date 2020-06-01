### pause_data_t;

Data holder for main menu instance
Holds Player1 and Player2 custom names and currently selected menu tab


## bool init_perifs_pause(void)

Initilizes memomry and maps periferies to use for pause event

## void back_to_menu(void)

Returns game back to menu

## void pause_graphics(void)

Creates and refreshes GUI for pause menu

## void wrong_key_pause(void)

Notifies user about unexpected stdin input

## void info_pause(void)

Gives user information on how to control pause menu with serial port

## void light_leds_pause(void)

Lights RGB LEDs based on what tab is selected

## void pause_oper(game_struct * game)

Handles pause event logic

## void tab_pressed_pause(void)

Decides what to do when a tab is activated

## void pause_loop(void)

Loop to handle interactions with user during pause sequence

