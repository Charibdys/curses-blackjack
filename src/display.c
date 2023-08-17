#include "include/display.h"

#define PLAYER_CARD_HAND 11
#define DEALER_CARD_HAND 3
#define CARD_HEIGHT 5
#define CARD_WIDTH  7
#define CARD_OFFSET 3


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

void gameBoard(int dealerLimit)
{
    WINDOW *topHalf;
    WINDOW *botHalf;

    int width = COLS - (COLS/4);
    int height = LINES/2;

    int startx = 0;

    topHalf = create_win(height, width, 0, 0);
    botHalf = create_win(height, width, LINES/2, 0);

    // Removes gap between top and bottom windows
    //topHalf = create_win(height + 1, width, 0, 0);
    //mvwaddch(botHalf, 0, 0, ACS_LTEE);
    //mvwaddch(botHalf, 0, width - 1, ACS_RTEE);

    mvwprintw(topHalf, 1, (width/2) - 3, "Dealer");
    mvwprintw(topHalf, 2, (width/2) - 19, "Must draw to %d and stand on all %d's", dealerLimit, dealerLimit+1);

    mvwprintw(botHalf, 1, (width/2) - 5, "Your Hand");

    wrefresh(topHalf);
    wrefresh(botHalf);

    delwin(topHalf);
    delwin(botHalf);
}

int gameMenuLoop()
{
    WINDOW *gameMenu;

    int numChoices = sizeof(GameMenuChoices)/sizeof(GameMenuChoices[0]);
    int highlight = 1;
    int choice = 0;
    int c = 0;

    int width = COLS/4;
    int height = LINES/2;

    int startx = COLS - (COLS/4);

    gameMenu = create_win(height, width, LINES/2, startx);
    keypad(gameMenu, TRUE);

    printMenu(gameMenu, numChoices, highlight, GameMenuChoices);

    while(1)
    {
        c = wgetch(gameMenu);
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
        printMenu(gameMenu, numChoices, highlight, GameMenuChoices);
        if(choice != 0)
            break;
    }

    return choice;
}

int inGameMenuLoop()
{
    WINDOW *inGameMenu;

    int numChoices = sizeof(InGameMenuChoices)/sizeof(InGameMenuChoices[0]);
    int highlight = 1;
    int choice = 0;
    int c = 0;

    int width = COLS/4;
    int height = LINES/2;

    int startx = COLS - (COLS/4);

    inGameMenu = create_win(height, width, LINES/2, startx);
    keypad(inGameMenu, TRUE);

    printMenu(inGameMenu, numChoices, highlight, InGameMenuChoices);

    while(1)
    {
        c = wgetch(inGameMenu);
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
        printMenu(inGameMenu, numChoices, highlight, InGameMenuChoices);
        if(choice != 0)
            break;
    }

    return choice;

}

int betMenu(int currentBet, int highlight)
{
    WINDOW *betMenu;

    int numChoices = sizeof(BetMenuChoices)/sizeof(BetMenuChoices[0]);

    int bet = currentBet;
    int choice = 0;
    int c = 0;

    if(highlight == 0)
        highlight = 1;

    int width = COLS/4;
    int height = LINES/2;

    int startx = COLS - (COLS/4);

    betMenu = create_win(height, width, LINES/2, startx);
    keypad(betMenu, TRUE);

    printBetMenu(betMenu, numChoices, bet, highlight);

    while(1)
    {
        choice = 0;
        c = wgetch(betMenu);
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
        printBetMenu(betMenu, numChoices, bet, highlight);
        if(choice != 0)
            break;
    }

    return choice;
}


void printBetMenu(WINDOW *menu, int numChoices, int bet, int highlight)
{
    int xMargin = 2;
    int yMargin = 4;

    mvwprintw(menu, yMargin - 2, xMargin, "Set bet: %d", bet);

    for(int i = 0; i < 3; i++){

        if(highlight == i + 1){
            wattron(menu, A_REVERSE);
            mvwprintw(menu, yMargin, xMargin, "%s", BetMenuChoices[i]);
            wattroff(menu, A_REVERSE);
        }
        else
            mvwprintw(menu, yMargin, xMargin, "%s", BetMenuChoices[i]);
        
        ++yMargin;
    }

    wrefresh(menu);
}

void statsWindow(int money, int bet, int handValue, char *message)
{
    WINDOW *statsWindow;
    int width = COLS/4;
    int height = LINES/2;

    int startx = COLS - (COLS/4);

    statsWindow = create_win(height, width, 0, startx);

    mvwprintw(statsWindow, 1 , 2, "Money = %d", money);
    mvwprintw(statsWindow, 2 , 2, "Bet = %d", bet);

    if(handValue > 0)
        mvwprintw(statsWindow, 3 , 2, "Hand = %d", handValue);

    if(message != ""){
        wattron(statsWindow, A_REVERSE);
        mvwprintw(statsWindow, height - 2, 2, "%s", message);
        wattroff(statsWindow, A_REVERSE);
    }

    wrefresh(statsWindow);
    delwin(statsWindow);
}

void alert(char *message)
{
    WINDOW *alertBox;

    int height = 7;
    int width = 16;
    int starty = TITLE_LINES + TITLE_INDENT;
    int startx = (COLS - width) / 2;

    int yMargin = 2;  

    alertBox = create_win(height, width, starty, startx);
    keypad(alertBox, TRUE);

    mvwprintw(alertBox, yMargin, (width/2) - (strlen(message))/2, message);

    wattron(alertBox, A_REVERSE);
    mvwprintw(alertBox, height - 2, (width/2) - 1, "OK");
    wattroff(alertBox, A_REVERSE);

    wrefresh(alertBox);

    if(wgetch(alertBox))
        destroy_win(alertBox);
}

// 1 2 3 4 5 6 7 8 9 10 11 12 13
// 2 3 4 5 6 7 8 9 10 J  Q  K  A
void printCard(char suit, int value, int cardCount, bool hideFirstCard, bool isDealer)
{
    WINDOW *card;

    int dealerCardRow = LINES/2 - (LINES/4) - 1;
    int playerCardRow = LINES/2 + (LINES/4) - 1;

    char cardValue = '0';
    switch(value)
    {
        case 10:
            cardValue = 'J';
            break;

        case 11:
            cardValue = 'Q';
            break;

        case 12:
            cardValue = 'K';
            break;

        case 13:
            cardValue = 'A';
            break;
        
        default:
            cardValue = 49 + value;
    }

    if(isDealer){
        if(hideFirstCard && (cardCount == 1))
            card = create_card(CARD_HEIGHT, CARD_WIDTH, dealerCardRow, ((CARD_WIDTH + CARD_OFFSET) * cardCount), '+', '+');
        else
            card = create_card(CARD_HEIGHT, CARD_WIDTH, dealerCardRow, ((CARD_WIDTH + CARD_OFFSET) * cardCount), cardValue, suit);
    }
    else
        card = create_card(CARD_HEIGHT, CARD_WIDTH, playerCardRow, ((CARD_WIDTH + CARD_OFFSET) * cardCount), cardValue, suit);


    wrefresh(card);
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

void printMenu(WINDOW *menu, int numChoices, int highlight, char *choices[])
{
    int xMargin = 2;
    int yMargin = 2;

    for(int i = 0; i < numChoices; i++){
        if(highlight == i + 1){
            wattron(menu, A_REVERSE);
            mvwprintw(menu, yMargin, xMargin, "%s", choices[i]);
            wattroff(menu, A_REVERSE);
        }
        else
            mvwprintw(menu, yMargin, xMargin, "%s", choices[i]);
        
        ++yMargin;
    }

    wrefresh(menu);
}


// Print menu to screen such that each item in choices is center justified.
void printCenterMenu(WINDOW *menu, int numChoices, int highlight, int maxWidth, char *choices[])
{
    int yMargin = Y_MARGIN;

    for(int i = 0; i < numChoices; i++){
        int left_padding = (maxWidth - strlen(choices[i])) / 2;

        if(highlight == i + 1){
            wattron(menu, A_REVERSE);
            mvwprintw(menu, yMargin, left_padding, "%s",choices[i]);
            wattroff(menu, A_REVERSE);
        }
        else
            mvwprintw(menu, yMargin, left_padding, "%s",choices[i]);
        
        ++yMargin;
    }

    wrefresh(menu);
}

int longestStringLength(int numChoices, char *choices[]) {
    if(choices == NULL)
        return -1;

    int longest_length = 0;
    
    for(int i = 0; i < numChoices; i++){
        int length = strlen(choices[i]);
        if(length > longest_length)
            longest_length = length;
    }

    return longest_length;
}

int menuLoop()
{
    int numChoices = sizeof(MenuChoices)/sizeof(MenuChoices[0]);
    int menuWidth = longestStringLength(numChoices, MenuChoices) + X_MARGIN;

    int starty = TITLE_LINES + TITLE_INDENT + 1; // Add another space below title
    int startx = (COLS - menuWidth) / 2;

    int highlight = 1;
    int choice = 0;
    int c = 0;

    WINDOW *menu = create_win(numChoices + 2, menuWidth, starty, startx);
    keypad(menu, TRUE);
    printCenterMenu(menu, numChoices, highlight, menuWidth, MenuChoices);

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
        printCenterMenu(menu, numChoices, highlight, menuWidth, MenuChoices);
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

WINDOW *create_card(int height, int width, int starty, int startx, char value, char suit)
{
    WINDOW *local_card;

    local_card = newwin(height, width, starty, startx);

    // Special case for a 10 card
    if(value == ':'){
        wborder(local_card, '|', '|', '-', '-', suit, '0', '1' , suit);
        mvwaddch(local_card, 0, (width - 2), '1');
        mvwaddch(local_card, (height-1), 1, '0');
        wrefresh(local_card);
        return local_card;
    }

    wborder(local_card, '|', '|', '-', '-', suit, value, value , suit);

    wrefresh(local_card);

    return local_card;
}