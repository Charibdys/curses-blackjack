#include "include/game.h"
#include "include/display.h"


void gameLoop(pcg32_random_t *randSeed)
{
    struct Card deck[52];
    struct Card *ptr = 0;
    ptr = deck;

    initDeck(ptr);

    refresh();
}