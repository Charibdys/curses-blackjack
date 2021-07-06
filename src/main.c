#include "include/display.h"
#include "include/game.h"

#define START   1
#define OPTIONS 2
#define LOAD    3
#define QUIT    4

int main(int argc, char *argv[])
{
    MEVENT event;
    int choice = 0;

    // This must go near the start, else we cannot obtain LINES or COLS
    initCurses();
    
    printTitle(&event);
    
    while(1)
    {
        choice = menuLoop();
        switch(choice)
        {
            case START:
                gameLoop();
                break;
            case OPTIONS:
                mvprintw(2, 1, "Choice %d has not been implemented", choice);
                refresh();
                break;
            case LOAD:
                mvprintw(2, 1, "Choice %d has not been implemented", choice);
                refresh();
                break;
            case QUIT:
                endwin();
                return 0;
            default:
                mvprintw(2, 1, "Choice %d is undefined", choice);
                refresh();
                break;
        }
    }

    endwin();
    return 0;
}