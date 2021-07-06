#include "include/card.h"

void initDeck(struct Card *deckPtr)
{
    int i;

    for(i = 1; i <= 13; i++){
        deckPtr->value = i;
        deckPtr->suit = 'D';
        deckPtr++;
    }

    for(i = 1; i <= 13; i++){
        deckPtr->value = i;
        deckPtr->suit = 'S';
        deckPtr++;
    }

    for(i = 1; i <= 13; i++){
        deckPtr->value = i;
        deckPtr->suit = 'H';
        deckPtr++;
    }

    for(i = 1; i <= 13; i++){
        deckPtr->value = i;
        deckPtr->suit = 'C';
        deckPtr++;
    }

}

void swapCard(struct Card *rCard, struct Card *lCard)
{
    struct Card temp;
    temp.value = rCard->value;
    temp.suit = rCard->suit;

    rCard->value = lCard->value;
    rCard->suit = lCard->suit;

    lCard->value = temp.value;
    lCard->suit = temp.suit;
}