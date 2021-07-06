#ifndef CARD_H
#define CARD_H

struct Card{
    int value;
    char suit;
};

void initDeck(struct Card *deckPtr);

void swapCard(struct Card *rCard, struct Card *lCard);

#endif