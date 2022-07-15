// ViewSpider.hpp
// this is header file for View for Spider Solitaire game
#ifndef VIEWSPIDER_HPP 
#define VIEWSPIDER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <utility>
#include <memory>
#include <cstdlib>
#include <ctime>

#include <Card.hpp>
#include <DeckSpades.hpp>
#include <AnimationWrapper.hpp>

class View {
    private:
    int bounds_width = 1400;
	int bounds_height = 1000;
	int stackDistance = 30;
    int distBtwPiles = 40;
    int cardHeight = 0; // set cardHeight with sprite.getSize()
    int cardWidth = 0; // set cardWidth with sprite.getSize()
    int startPointX = 100;
    int startPointY = 100;
    sf::Image image; // initiate
    sf::Texture texture; // initiate
    sf::Sprite sprite; // initiate
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile1; // initiate all below
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile2;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile3;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile4;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile5;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile6;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile7;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile8;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile9;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile10;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile1;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile2;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile3;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile4;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile5;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile6;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile7;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile8;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile1;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile2;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile3;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile4;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile5;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> dealPile;
    std::shared_ptr<Deck> deck;

    std::shared_ptr<std::vector<std::shared_ptr<Card>>> lastPile = nullptr;
    int lastStackDistance;

    public:
    View();
    ~View();
    void initiateView(std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile1_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile2_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile3_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile4_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile5_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile6_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile7_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile8_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile9_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile10_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile1_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile2_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile3_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile4_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile5_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile6_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile7_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile8_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile1_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile2_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile3_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile4_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile5_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> dealPile_,
    std::shared_ptr<Deck> deck_);

    std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> getClick(sf::Vector2f mousePos);
    std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> getRelease(sf::Vector2f mousePos);
    void setPosition();
    void draw(sf::RenderWindow* window);

    void animateWin(sf::RenderWindow* window);
    void animateWin2(sf::RenderWindow* window);


    int getBoundsWidth();
    int getBoundsHeight();
    int getLastStackDistance();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getLastPile();
    int getStackDistance(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getMainPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getFoundationPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getDrawPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getMovePile();

    int getNextXPos(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile);
    int getNextYPos(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile);

    void setLastStackDistance(int stk_dist);
    void setLastPile(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile);

};

#endif