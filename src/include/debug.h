#ifndef DEBUG_H
#define DEBUG_H

#include <pcg_variants.h>
#include "./display.h"
#include "./card.h"

static char *DebugChoices[] = {
    "Print Deck",
    "Shuffle Deck",
    "Back",
};

int debugLoop();

void printCards(struct Card *deckPtr);

void debugCards(pcg32_random_t *randSeed);

void debugShuffle(pcg32_random_t *randSeed);


#endif