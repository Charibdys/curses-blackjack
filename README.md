# Curses Blackjack

The game of Blackjack implemented in C with a curses interface

## Dependencies

- pcg-random, specifically the [pcg-c](https://github.com/imneme/pcg-c/tree/master/include) library
- ncurses

## Building

Run `make all` to build the binary.

## Features
- [X] PCG Random Number Generation
- [X] Optimized for small terminals (80 column, 24 lines)
- [X] Thorough card shuffling
- [X] Simple game rules
	- [X] Double Down
 	- [X] Surrender 

## Attribution
ASCII art used in the title screen was generated on www.patorjk.com/software/taag/
Using the font 'DOOM' by Frans P. de Vries <fpv@xymph.iaf.nl>, 18 Jun 1996

NCurses, used here to make the text user interface, is currently maintained by Thomas E. Dickey <dickey@invisible-island.net>

The PCG random number generator was sourced from www.pcg-random.org
