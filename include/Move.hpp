// Move.hpp which inherits from Command class
// Header fils for Move class which represents one move in spider solitaire
#ifndef MOVE_HPP
#define MOVE_HPP

#include <vector>

#include <Command.hpp>
#include <ModelSpider.hpp>
#include <ViewSpider.hpp>
#include <ControllerSpider.hpp>
#include <FillFoundationPile.hpp>

class Controller;

class Move : public Command {
    private:
    Model* model;
    View* view;
    Controller* controller;
    sf::RenderWindow* window;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile;
    int from_index;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile;
    int to_index; // to_index is to_pile->size()
    bool card_revealed = false;

    public:
    Move(Model* model_, View* view_, Controller* controller_, sf::RenderWindow* window_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile_, int from_index_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile_, int to_index_);
    ~Move();
    void execute();
    void undo();
};

#endif