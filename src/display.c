#include "include/display.h"


void initCurses()
{
    initscr();
    curs_set(FALSE);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    return;
}

void printTitle(MEVENT *event)
{
    WINDOW *titleScreen;
    int startx = 0;

    titleScreen = create_win(LINES, COLS, 0, 0);
    keypad(titleScreen, TRUE);

    for(int i = 0; i < (sizeof(Title)/sizeof(Title[0])); i++){
        startx = (COLS / 2) - (strlen(Title[i]) / 2);
        mvwprintw(titleScreen, i + TITLE_INDENT, startx, "%s", Title[i]);
    }

    wrefresh(titleScreen);

    /* Remain on title screen until key is pressed */
    if(wgetch(titleScreen) || getmouse(event) == OK);
        destroy_win(titleScreen);
}

void printMenu(WINDOW *menu, int numChoices, int highlight)
{
    int xMargin = 2 ;
    int yMargin = 2;

    for(int i = 0; i < numChoices; i++){

        if(highlight == i + 1){
            wattron(menu, A_REVERSE);
            mvwprintw(menu, yMargin, xMargin, "%s", MenuChoices[i]);
            wattroff(menu, A_REVERSE);
        }
        else
            mvwprintw(menu, yMargin, xMargin, "%s", MenuChoices[i]);
        
        ++yMargin;
    }

    wrefresh(menu);
}

int menuLoop()
{
    WINDOW *menu;
    int numChoices = sizeof(MenuChoices)/sizeof(MenuChoices[0]);
    int starty = TITLE_LINES + TITLE_INDENT;
    int startx = (COLS - 12) / 2;

    int highlight = 1;
    int choice = 0;
    int c = 0;

    menu = create_win(7, 12, starty, startx);
    keypad(menu, TRUE);
    printMenu(menu, numChoices, highlight);

    while(1)
    {
        c = wgetch(menu);
        switch(c)
        {
            case KEY_UP:
                if(highlight == 1)
                    highlight = numChoices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == numChoices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:    //On LF/Enter/Return
                choice = highlight;
                break;
        }
        printMenu(menu, numChoices, highlight);
        if(choice != 0)
            break;
    }

    return choice;

}

WINDOW *create_win(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);

    wrefresh(local_win);

    return local_win;
}

void destroy_win(WINDOW *local_win)
{
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
	delwin(local_win);
}