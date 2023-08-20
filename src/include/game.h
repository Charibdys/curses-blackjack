#ifndef GAME_H
#define GAME_H

#include <pcg_variants.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./card.h"
#include "./display.h"

struct Hand{
    struct Card card;
    struct Hand *next;
};

struct Dealer{
    // TODO: Add limits
    int limit;
    struct Hand *hand;
};

struct Player{
    unsigned int money;
    struct Hand *hand;
};

void gameLoop(pcg32_random_t *randSeed);

struct Card drawCard(struct Card *deckPtr);

void shiftDeck(struct Card *deckPtr, int amount);

void appendCard(struct Card *deckPtr, struct Hand *hand);

void dealerTurn(int limit, struct Hand *hand, struct Card *deckPtr);

int checkResult(struct Hand *dealerHand, struct Hand *playerHand);

void closeBets(int result, int bet, struct Dealer *dealer, struct Player *player);

int sumHand(struct Hand *hand);

int sumObscuredHand(struct Hand *hand);

void delHand(struct Hand *dealerHand, struct Hand *playerHand, struct Card *deckPtr);

//void initHead(struct Card *deckPtr, struct Hand *hand);

struct Hand *initHead(struct Card *deckPtr);

void printHand(struct Hand *hand, bool hideFirstCard, bool isDealer);

#endif