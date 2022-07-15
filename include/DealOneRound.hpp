// DealOneRound.hpp
// header file for DealOneRound in spider solitaire
#ifndef DEALONEROUND_HPP
#define DEALONEROUND_HPP

#include <vector>

#include <Command.hpp>
#include <AnimationWrapperST.hpp>
#include <ModelSpider.hpp>
#include <ViewSpider.hpp>
#include <ControllerSpider.hpp>

class Controller;

class DealOneRound : public Command {
    private:
    Model* model;
    View* view;
    Controller* controller;
    sf::RenderWindow* window;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> correct_draw_pile;
    

    public:
    DealOneRound(Model* model_, View* view_, Controller* controller_, sf::RenderWindow* window_);
    ~DealOneRound();
    void execute();
    void undo();
};

#endif