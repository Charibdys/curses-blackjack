#include <pcg_variants.h>
#include <time.h>
#include "include/display.h"
#include "include/game.h"

#define START   1
#define OPTIONS 2
#define LOAD    3
#define QUIT    4

int main(int argc, char *argv[])
{
    // Init and seed RNG
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&printTitle);

    // This must go near the start, else we cannot obtain LINES or COLS
    initCurses();
    
    int choice = 0;

    while(choice != QUIT)
    {
        refresh();
        printTitle();
        choice = menuLoop();
        switch(choice)
        {
            case START:
                gameLoop(&rng);
                break;
            case OPTIONS:
                alert("OPTIONS has not been implemented yet", 8, 30, TITLE_LINES + TITLE_INDENT, (COLS - 30) / 2);
                break;
            case LOAD:
                alert("LOAD has not been implemented yet", 8, 30, TITLE_LINES + TITLE_INDENT, (COLS - 30) / 2);
                break;
            case QUIT:
                break;
            default:
                alert("That choice has not been implemented yet", 8, 30, TITLE_LINES + TITLE_INDENT, (COLS - 30) / 2);
                break;
        }
    }

    endwin();
    return 0;
}