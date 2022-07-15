// deck.cpp
// a deck of cards all spades for spider solitaire
#ifndef DECKSPADES_CPP 
#define DECKSPADES_CPP 

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <DeckSpades.hpp>


void Deck::createDeck() {
    // create front images
    std::vector<std::string> INameVec{"../allSpades/aceOfSpades.png", "../allSpades/twoOfSpades.png", 
    "../allSpades/threeOfSpades.png", "../allSpades/fourOfSpades.png", "../allSpades/fiveOfSpades.png", 
    "../allSpades/sixOfSpades.png", "../allSpades/sevenOfSpades.png",
    "../allSpades/eightOfSpades.png", "../allSpades/nineOfSpades.png", "../allSpades/tenOfSpades.png", 
    "../allSpades/jackOfSpades.png", "../allSpades/queenOfSpades.png", "../allSpades/kingOfSpades.png"};
    // load 13 images 4 times 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            std::shared_ptr<sf::Image> p_image = std::make_shared<sf::Image>();
            p_image->loadFromFile(INameVec[j]);
            pImageVec.push_back(p_image);
        }
    }
    // create front textures
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Texture> p_texture = std::make_shared<sf::Texture>();
        p_texture->loadFromImage(*pImageVec[i]);
        pTextureVec.push_back(p_texture);
    }
    // create front sprites
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Sprite> p_sprite = std::make_shared<sf::Sprite>();
        p_sprite->setTexture(*pTextureVec[i]);
        p_sprite->setScale(scaleX, scaleY);
        pFrontSpriteVec.push_back(p_sprite);
    }
    //create back image
    std::shared_ptr<sf::Image> p_back_image = std::make_shared<sf::Image>();
    p_back_image->loadFromFile("../allSpades/backOfCard.png"); //add backOfCard.png here
    pBackImageVec.push_back(p_back_image);
    // create back texture
    std::shared_ptr<sf::Texture> p_back_texture = std::make_shared<sf::Texture>();
    p_back_texture->loadFromImage(*pBackImageVec[0]);
    pBackTextureVec.push_back(p_back_texture);
    // create back sprites
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Sprite> p_back_sprite = std::make_shared<sf::Sprite>();
        p_back_sprite->setTexture(*pBackTextureVec[0]);
        p_back_sprite->setScale(scaleX, scaleY);
        pBackSpriteVec.push_back(p_back_sprite);
    }
    // create cards
    std::vector<std::string> symbolVec{"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    // spades
    // create 13 cards 4 times
    for (int h = 0; h < 4; h++) {
        for (int i = 1; i < 14; i++) {
            std::shared_ptr<Card> card = std::make_shared<Card>(symbolVec[i - 1], "S", "B", i, 
                pFrontSpriteVec[i - 1 + 13 * h], pBackSpriteVec[i - 1 + 13 * h]);
            deckOfCards.push_back(card);
        }
    }
    
    
    

}
void Deck::shuffleDeck() {
    //create vector and copy to it
    std::vector<std::shared_ptr<Card>> copyVec;
    while (!deckOfCards.empty()) {
        copyVec.push_back(deckOfCards.back());
        deckOfCards.pop_back();
    }
    //put back at random
    srand(time(NULL));
    while (!copyVec.empty()) {
        int num = rand() % copyVec.size();
        deckOfCards.push_back(copyVec[num]);
        copyVec.erase(copyVec.begin() + num);
    }
    
}
Deck::Deck() {
    createDeck();
    shuffleDeck();
}

Deck::~Deck() {
    deckOfCards.clear();
    pImageVec.clear();
    pBackImageVec.clear();
    pTextureVec.clear();
    pBackTextureVec.clear();
    pFrontSpriteVec.clear();
    pBackSpriteVec.clear();
}
bool Deck::isEmpty() {
    if (deckOfCards.empty()) {
        return true;
    }
    return false;
}
int Deck::dealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!deckOfCards.empty()) {
        std::shared_ptr<Card> p_card = deckOfCards.back();
        p_card->setFaceUp(false);
        pile->push_back(p_card);
        deckOfCards.pop_back();
        return 1;
    }
    return -1;
}

void Deck::returnCards(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    while (!pile->empty()) {
        std::shared_ptr<Card> p_card = pile->back();
        p_card->setFaceUp(false);
        deckOfCards.push_back(p_card);
        pile->pop_back();
    }
    return;
}
std::shared_ptr<sf::Sprite> Deck::getTopSprite() {
    return deckOfCards.back()->getPSprite();
}


#endif