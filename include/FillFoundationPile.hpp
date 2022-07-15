// FillFoundationPile.hpp
// Header file for FillFoundationPile, spider solitaire
#ifndef FILLFOUNDATIONPILE_HPP
#define FILLFOUNDATIONPILE_HPP

#include <vector>
#include <memory>

#include <Command.hpp>
#include <AnimationWrapper.hpp>
#include <AnimationWrapperST.hpp>
#include <ModelSpider.hpp>
#include <ViewSpider.hpp>
#include <ControllerSpider.hpp>

class Controller;

class FillFoundationPile : public Command {
    private:
    Model* model;
    View* view;
    Controller* controller;
    sf::RenderWindow* window;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile;
    bool card_revealed = false;
    
    

    public:
    FillFoundationPile(Model* model_, View* view_, Controller* controller_, sf::RenderWindow* window_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile_);
    ~FillFoundationPile();
    void execute();
    void undo();
};

#endif