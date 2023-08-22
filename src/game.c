#include "include/game.h"

#define DEAL    1
#define BET     2
#define EXIT    3

#define HIT     1
#define D_DOWN  2
#define STAND   3
#define FOLD    4

void gameLoop(pcg32_random_t *randSeed)
{
    struct Card deck[52];
    struct Card *deckPtr = 0;
    deckPtr = deck;

    initDeck(deckPtr);

    bool gameInPlay = true;
    int gameChoice = 0;

    unsigned int bet = 0;

    struct Dealer dealer = {16, NULL};
    struct Player player = {45, NULL};

    while(gameInPlay){

        vegasShuffle(deckPtr, randSeed);
        gameBoard(dealer.limit);
        statsWindow(player.money, bet, 0, 0, "");
        gameChoice = gameMenuLoop();
        switch(gameChoice)
        {
            case DEAL:
                handleDeal(bet, &player, &dealer, deckPtr);
                inGameLoop(bet, &player, &dealer, deckPtr);
                break;

            case BET:
                bet = handleBet(bet, &player);
                break;

            case EXIT:
                gameInPlay = false;
                break;
        }
        
    }

    refresh();
}


// In game loop where player gets cards
void inGameLoop(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    int subGameChoice = 0;
    bool subGameInPlay = true;

    while(subGameInPlay){
        subGameChoice = inGameMenuLoop();
        switch (subGameChoice)
        {
        case HIT:
            subGameInPlay = handleHit(bet, player, dealer, deckPtr);
            break;

        case D_DOWN:
            bet = handleDoubleDown(bet, player, dealer, deckPtr);
            break;

        case STAND:
            dealerTurn(dealer->limit, dealer->hand, deckPtr);
            statsWindow(player->money, bet, sumHand(player->hand), sumHand(dealer->hand), "");
            break;

        case FOLD:
            subGameInPlay = false;
            break;
        }
    }
}

void handleDeal(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    player->hand = initHead(deckPtr);
    dealer->hand = initHead(deckPtr);
    appendCard(deckPtr, player->hand);
    appendCard(deckPtr, dealer->hand);

    printHand(dealer->hand, true, true);
    printHand(player->hand, false, false);

    statsWindow(player->money, bet, sumHand(player->hand), sumObscuredHand(dealer->hand), "");
}

unsigned int handleBet(unsigned int bet, struct Player *player)
{
    int tempMoney = player->money;
    int betMenuChoice = 0;

    while(betMenuChoice != 3){
        betMenuChoice = betMenu(bet, betMenuChoice);
        if(betMenuChoice == 1){
            if(bet < 100 && tempMoney > bet){
                player->money -= 1;
                bet += 1;
            }
        }
        else if(betMenuChoice == 2){
            if(bet > 0){
                player->money += 1;
                bet -= 1;
            }
        }
    }

    return bet;
}

bool handleHit(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    appendCard(deckPtr, player->hand);
    printHand(player->hand, false, false);
    statsWindow(player->money, bet, sumHand(player->hand), sumObscuredHand(dealer->hand), "");

    if(sumHand(player->hand) > 21){
        dealerTurn(dealer->limit, dealer->hand, deckPtr);
        statsWindow(player->money, bet, sumHand(player->hand), sumHand(dealer->hand), "");
        alert("BUST!", 6, 16, LINES/2 - 3, COLS/2 - 8);
        closeBets(checkResult(dealer->hand, player->hand), bet, dealer, player);
        delHand(dealer->hand, player->hand, deckPtr);
        return false;
    }

    return true;
}

unsigned int handleDoubleDown(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    if(bet*2 <= player->money){
        bet *= 2;
        appendCard(deckPtr, player->hand);
        printHand(player->hand, false, false);
        dealerTurn(dealer->limit, dealer->hand, deckPtr);
        statsWindow(player->money, bet, sumHand(player->hand), sumHand(dealer->hand), "");
    }
    else{
        statsWindow(player->money, bet, sumHand(player->hand), sumObscuredHand(dealer->hand), "Not enough money");
        alert("Can't do that", 6, 18, LINES/2 - 3, COLS/2 - 9);
    }

    return bet;
}

void printHand(struct Hand *hand, bool hideFirstCard, bool isDealer)
{
    struct Hand *temp = hand;
    int cardNumber = 1;

    while(temp != NULL){
        printCard(temp->card.suit, temp->card.value, cardNumber, hideFirstCard, isDealer);
        temp = temp->next;
        cardNumber++;
    }
}

struct Card drawCard(struct Card *deckPtr)
{
    struct Card tempCard = {.value = deckPtr->value, .suit = deckPtr->suit};
    shiftDeck(deckPtr, 1);
    return tempCard;
}

void appendCard(struct Card *deckPtr, struct Hand *hand)
{
    if(hand == NULL){
        hand = malloc(sizeof(struct Hand));
        hand->card = drawCard(deckPtr);
        hand->next = NULL;
        return;
    }

    struct Hand *newHand;
    struct Hand *temp = hand;

    newHand = malloc(sizeof(struct Hand));
    newHand->card = drawCard(deckPtr);
    newHand->next = NULL;

    while(temp->next != NULL)
        temp = temp->next;

    temp->next = newHand;
}

void dealerTurn(int limit, struct Hand *hand, struct Card *deckPtr)
{
    printHand(hand, false, true);
    bool finishedTurn = false;
    int dealerHand = sumHand(hand);

    while(finishedTurn == false){
        if(sumHand(hand) < limit){
            appendCard(deckPtr, hand);
            printHand(hand, false, true);
        }
        else
            finishedTurn = true;
    }
}

/*
    When the hands are equal, it's a push and player keeps his bet
    When dealer's hand is greater than player's, dealer wins
    When player's hand is greater than dealer's, playe wins
    TODO: There's a lot more nuance to the winning conditions
        that the function doesn't check for yet.
*/
int checkResult(struct Hand *dealerHand, struct Hand *playerHand)
{
    int dealerSum = sumHand(dealerHand);
    int playerSum = sumHand(playerHand);

    if(dealerSum > playerSum)
        return 1;
    if(dealerSum == playerSum)
        return 0;
    if(dealerSum < playerSum)
        return -1;
}

void closeBets(int result, int bet, struct Dealer *dealer, struct Player *player)
{
    switch(result)
    {   
        case 1:
            break;
        case 0:
            break;
        case -1:
            break;
    }

    return;
}

int sumHand(struct Hand *hand)
{
    if(hand == NULL)
        return -1;

    int sum = 0;
    struct Hand *temp = hand;

    while(temp != NULL){
        if(temp->card.value < 9)
            sum += temp->card.value + 1;
        else if(temp->card.value > 8 && temp->card.value < 13)
            sum += 10;
        else{
            if((sum + 11) <= 21)
                sum += 11;
            else
                sum += 1;
        }

        temp = temp->next;
    }


    return sum;
}

int sumObscuredHand(struct Hand *hand)
{
    if(hand == NULL)
        return -1;

    int sum = 0;
    struct Hand *temp = hand;

    // Skip first/hidden card
    if(temp->next != NULL) {
        temp = temp->next;
    }
    else {
        return -1;
    }

    while(temp != NULL){
        if(temp->card.value < 9)
            sum += temp->card.value + 1;
        else if(temp->card.value > 8 && temp->card.value < 13)
            sum += 10;
        else{
            if((sum + 11) <= 21)
                sum += 11;
            else
                sum += 1;
        }

        temp = temp->next;
    }


    return sum;
}

void delHand(struct Hand *dealerHand, struct Hand *playerHand, struct Card *deckPtr)
{
    if(playerHand == NULL && dealerHand == NULL)
        return;

    // Get total number of played cards so we can put them back into the deck
    int sum = 0;
    struct Hand *temp = playerHand;

    while(temp != NULL){
        sum++;
        temp = temp->next;
    }

    temp = dealerHand;

    while(temp != NULL){
        sum++;
        temp = temp->next;
    }

    // Put cards back at the bottom of the deck

    for(int i = sum; i > 0; i--){
        if(dealerHand != NULL){
            temp = dealerHand;
            dealerHand = dealerHand->next;

            (deckPtr+(52-i))->value = temp->card.value;
            (deckPtr+(52-i))->suit = temp->card.suit;

            free(temp);
        }
        else{
            temp = playerHand;
            playerHand = playerHand->next;

            (deckPtr+(52-i))->value = temp->card.value;
            (deckPtr+(52-i))->suit = temp->card.suit;

            free(temp);
        }
    }
}

struct Hand *initHead(struct Card *deckPtr)
{
    struct Hand *newHand;
    newHand = malloc(sizeof(struct Hand));
    newHand->card = drawCard(deckPtr);
    newHand->next = NULL;

    return newHand;
}

// Shift deck up by an amount (i.e., shift array elements to the left)
void shiftDeck(struct Card *deckPtr, int amount)
{
    if(amount < 0)
        return;

    for(int i = 0; i < amount; i++){
        for(int j = 0; j < 51; j++){
            (deckPtr+j)->value = (deckPtr+(j+1))->value;
            (deckPtr+j)->suit = (deckPtr+(j+1))->suit;
        }
    }

    return;
}