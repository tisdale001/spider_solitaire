// ModelSpider.cpp
// This is model for one suit spider solitaire game
#ifndef MODELSPIDER_CPP 
#define MODELSPIDER_CPP 

// Include header file
#include <ModelSpider.hpp>

// Constructor puts all 104 cards into deck1
Model::Model() {
    this->allDeckCardsToDealPile(deck2);
    this->allCardsReturnToDeck(deck1);
    this->shuffleCards();
}
Model::~Model() {
    this->allCardsReturnToDeck(deck1);
}

// transfers all card from deck to deal pile
void Model::allDeckCardsToDealPile(std::shared_ptr<Deck> deck) {
    while (!deck->isEmpty()) {
        deck->dealCard(dealPile);
    }
}

// all cards from piles returned to Deck
void Model::allCardsReturnToDeck(std::shared_ptr<Deck> deck) {
    // use deck->returnCards(pile)
    for (int i = 1; i < 11; i++) {
        deck->returnCards(getMainPile(i));
    }
    for (int i = 1; i < 9; i++) {
        deck->returnCards(getFoundationPile(i));
    }
    for (int i = 1; i < 6; i++) {
        deck->returnCards(getDrawPile(i));
    }
    deck->returnCards(movePile);
    deck->returnCards(dealPile);
}

// shuffle cards in deck1
void Model::shuffleCards() {
    deck1->shuffleDeck();
}

// transfer all cards from pile to movePile
void Model::cardsToMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile, int index) {
    int size = (int)from_pile->size() - index;
    for (int i = size; i > 0; i--) {
        movePile->push_back(from_pile->back());
        from_pile->pop_back();
    }
}

// transfer all cards from movePile to to_pile
void Model::cardsFromMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile) {
    while (!movePile->empty()) {
        to_pile->push_back(movePile->back());
        movePile->pop_back();
    }
}

// deals one card from from_pile into to_pile
void Model::dealOneCardFromPile(std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile) {
    if (!from_pile->empty()) {
        to_pile->push_back(from_pile->back());
        from_pile->pop_back();
    }
}

// reveals top card of pile: returns true if card is turned over
bool Model::revealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!pile->empty()) {
        if (pile->back()->getFaceUp() == false) {
            pile->back()->setFaceUp(true);
            return true;
        }
    }
    return false;
}

// getter: returns appropriate mainPile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getMainPile(int num) {
    switch(num) {
        case 1 :
            return mainPile1;
        case 2 :
            return mainPile2;
        case 3 :
            return mainPile3;
        case 4 :
            return mainPile4;
        case 5 :
            return mainPile5;
        case 6 :
            return mainPile6;
        case 7 :
            return mainPile7;
        case 8 :
            return mainPile8;
        case 9 :
            return mainPile9;
        case 10:
            return mainPile10;
        default :
            return nullptr;
    }
}

// getter: returns appropriate foundation pile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getFoundationPile(int num) {
    switch(num) {
        case 1 :
            return foundationPile1;
        case 2 :
            return foundationPile2;
        case 3 :
            return foundationPile3;
        case 4 :
            return foundationPile4;
        case 5 :
            return foundationPile5;
        case 6 :
            return foundationPile6;
        case 7 :
            return foundationPile7;
        case 8 :
            return foundationPile8;
        default :
            return nullptr;
    }
}

// getter: returns appropriate draw pile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getDrawPile(int num) {
    switch(num) {
        case 1 :
            return drawPile1;
        case 2 :
            return drawPile2;
        case 3 :
            return drawPile3;
        case 4 :
            return drawPile4;
        case 5 :
            return drawPile5;
        default:
            return nullptr;
    }
}

// getter: returns movePile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getMovePile() {
    return movePile;
}

// getter: returns dealPile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getDealPile() {
    return dealPile;
}

// getter: returns pointer to deck1
std::shared_ptr<Deck> Model::getDeck() {
    return deck1;
}

// getter: returns the next/correct drawPile or nullptr if all draw piles are empty
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getCorrectDrawPile() {
    for (int i = 5; i > 0; i--) {
        if (!getDrawPile(i)->empty()) {
            return getDrawPile(i);
        }
    }
    return nullptr;
}

// returns true if pile is a draw pile
bool Model::checkDrawPile(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    for (int i = 5; i > 0; i--) {
        if (pile == getDrawPile(i)) {
            return true;
        }
    }
    return false;
}

// getter: returns correct/NEXT foundation pile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getCorrectFoundationPile() {
    for (int i = 8; i > 0; i--) {
        if (this->getFoundationPile(i)->empty()) {
            return this->getFoundationPile(i);
        }
    }
    return nullptr;
}

#endif