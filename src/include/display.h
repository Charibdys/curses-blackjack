#ifndef DISPLAY_H
#define DISPLAY_H

#define TITLE_LINES     6   // Lines of the splash art
#define TITLE_INDENT    5   // Buffer between the top of the window and splash art

#include <curses.h>
#include <string.h>

// ASCII Art generated on https://www.patorjk.com/software/taag/
// Using the font DOOM by by Frans P. de Vries <fpv@xymph.iaf.nl>  18 Jun 1996
// TODO: Find a better way to display the title
static char const *Title[] = {
    "_____                       ___            _",
    "/  __ \\                     |_  |          | |",
    "| /  \\/_   _ _ __ ___  ___    | | __ _  ___| |",
    "  | |   | | | | '__/ __|/ _ \\   | |/ _` |/ __| |/ /",
    " | \\__/\\ |_| | |  \\__ \\  __/\\__/ / (_| | (__|   <",
    "   \\____/\\__,_|_|  |___/\\___\\____/ \\__,_|\\___|_|\\_\\",
    "",
    "Blackjack in the terminal",
    "Tachyon 2021"
};

//static char *License[]{};

static char *MenuChoices[] = {
    "Start",
    "Options",
    "Load Save",
    "Exit",
};

void initCurses();

void printTitle(MEVENT *event);

void printMenu(WINDOW *menu, int numChoices, int highlight);

int menuLoop();

WINDOW *create_win(int height, int width, int starty, int startx);

void destroy_win(WINDOW *local_win);

#endif