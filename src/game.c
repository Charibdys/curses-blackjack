#include "include/game.h"
#include "include/display.h"


void gameLoop()
{
    struct Card deck[52];
    struct Card *ptr = 0;

    ptr = deck;

    initDeck(ptr);

    refresh();
}