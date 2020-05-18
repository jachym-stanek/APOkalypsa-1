The documentation for this project is split into different files. This file contains some general information about the implementation and documentation for some functions, that do not require separate file.

##Contents

Functions from these are in this file:

* [PONG.c](##PONG.c)
* [colors.h](##colors.h)

For description of other functions, please check out the following files:

* [game.c] (game.md)
* [gameGraphics.c] (gameGraphics.md)

#General information

The main game data is stored in the structure [gameStruct](game.md).

Player A has the paddle on the left side of the screen and is controlled with the leftmost knob. Player B has the paddle on the right side of the screen and is controlled with the rightmost knob.

#Desrcription of some functions

Here, you can find descriptions of functions, that did not necessitate their separate file.

##PONG.c

The main file of the project.

**SUCCESS** - return value of succesful run of a function

**DISP_ERR** - return value of function that encountered a displaying error

###int main (int argc, char *argv[])**

The main method of the project. It opens the main menu.

##colors.h

This file contains color templates, so that the coloring of the application is the same throughout.
