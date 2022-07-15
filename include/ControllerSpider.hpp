// ControllerSpider.hpp
// Header file for Controller for Spider solitaire game
#ifndef CONTROLLERSPIDER_HPP 
#define CONTROLLERSPIDER_HPP 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>
#include <stack>
#include <memory>
#include <cstdlib>
#include <ctime>

#include <AnimationWrapperST.hpp>
#include <Card.hpp>
#include <Command.hpp>
#include <Move.hpp>
#include <DealOneRound.hpp>
#include <DeckSpades.hpp>
#include <ViewSpider.hpp>
#include <ModelSpider.hpp>

//class DealOneRound;

class Controller {
    private:
    Model model = Model();
    View view = View();
    bool pressedLastFrame = false;
	int once = 1;
	int xPos = 0;
	int yPos = 0;
	int xDiff = 0;
	int yDiff = 0;
    
    std::shared_ptr<std::stack<std::shared_ptr<Command>>> undoStack = std::make_shared<std::stack<std::shared_ptr<Command>>>();
    std::shared_ptr<std::stack<std::shared_ptr<Command>>> redoStack = std::make_shared<std::stack<std::shared_ptr<Command>>>();
    

    public:
    Controller();
    ~Controller();
    void playGame();
    void dealTableau(sf::RenderWindow* window);
    void redeal(sf::RenderWindow* window);
    bool checkLegalDeal();
    bool checkMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int);
    bool checkDrop(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    bool checkFullStack(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    bool checkWin();
    void makeBestMove(sf::RenderWindow*);
    int getNumUpturnedCards(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    int getSizeOfStack(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    void moveToLastPile(sf::RenderWindow*);
    void Undo();
    void Redo();
    void clearRedoStack();

    std::shared_ptr<std::stack<std::shared_ptr<Command>>> getUndoStack();
    std::shared_ptr<std::stack<std::shared_ptr<Command>>> getRedoStack();
    
};

#endif