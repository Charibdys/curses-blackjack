#ifndef CARD_H
#define CARD_H

#include <pcg_variants.h>

struct Card{
    int value;
    char suit;
};

void initDeck(struct Card *deckPtr);

void shuffleDeck(struct Card *deckPtr);

void swapCard(struct Card *rCard, struct Card *lCard);

void deckCopy(const struct Card *sourceDeck, struct Card *copyDeck);

// Various shuffle methods
void washShuffle(struct Card *deckPtr, pcg32_random_t *randSeed);

void pokeShuffle(struct Card *deckPtr, pcg32_random_t *randSeed);

void riffleShuffle(struct Card *deckPtr);

void cutShuffle(struct Card *deckPtr);

void boxShuffle(struct Card *deckPtr, pcg32_random_t *randSeed);

void vegasShuffle(struct Card *deckPtr, pcg32_random_t *randSeed);



#endif