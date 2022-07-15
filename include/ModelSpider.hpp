// ModelSpider.hpp
// This is the model for spider one suit solitaire game
#ifndef MODELSPIDER_HPP 
#define MODELSPIDER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>

#include <Card.hpp>
#include <DeckSpades.hpp>

class Model {
    private:
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile1 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile2 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile3 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile4 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile5 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile6 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile7 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile8 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile9 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile10 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile1 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile2 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile3 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile4 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile5 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile6 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile7 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile8 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile1 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile2 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile3 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile4 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile5 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> dealPile = std::make_shared<std::vector<std::shared_ptr<Card>>>();

    std::shared_ptr<Deck> deck1 = std::make_shared<Deck>();
    std::shared_ptr<Deck> deck2 = std::make_shared<Deck>();

    public:
    Model();
    ~Model();
    void allDeckCardsToDealPile(std::shared_ptr<Deck> deck);
    void allCardsReturnToDeck(std::shared_ptr<Deck> deck);
    void shuffleCards();
    void cardsToMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile, int);
    void cardsFromMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile);
    void dealOneCardFromPile(std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile, 
        std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile);
    bool revealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile);

    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getMainPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getFoundationPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getDrawPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getMovePile();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getDealPile();
    std::shared_ptr<Deck> getDeck();

    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getCorrectDrawPile();
    bool checkDrawPile(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getCorrectFoundationPile();

};

#endif