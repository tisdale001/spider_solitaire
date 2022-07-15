// DealOneRound.cpp
// Deals one round in spider solitaire
#ifndef DEALONEROUND_CPP
#define DEALONEROUND_CPP

#include <DealOneRound.hpp>

DealOneRound::DealOneRound(Model* model_, View* view_, Controller* controller_, sf::RenderWindow* window_) {
    model = model_;
    view = view_;
    controller = controller_;
    window = window_;
    correct_draw_pile = model->getCorrectDrawPile();
}

DealOneRound::~DealOneRound() {}

// Deals one round of cards: one for each main pile from correct draw pile
void DealOneRound::execute() {
    if (!correct_draw_pile->empty()) {
        // move all cards into movePile
        while (!correct_draw_pile->empty()) {
            model->getMovePile()->push_back(correct_draw_pile->back());
            correct_draw_pile->pop_back();
        }
        // create animation wrappers for each card
        std::vector<std::shared_ptr<AnimationWrapperST>> ani_vec = std::vector<std::shared_ptr<AnimationWrapperST>>();
        int staggerAmt = 10;
        int numFrames = 30;
        int j = 1;
        int k = 0;
        for (int i = 0; i < 10 * staggerAmt; i += staggerAmt) {
            std::shared_ptr<AnimationWrapperST> animation = std::make_shared<AnimationWrapperST>(
                model->getMovePile()->at(k)->getPSprite(), view->getNextXPos(correct_draw_pile), 
                view->getNextYPos(correct_draw_pile), view->getNextXPos(model->getMainPile(j)),
                view->getNextYPos(model->getMainPile(j)), numFrames
            );
            animation->setID(i);
            ani_vec.push_back(animation);
            j++;
            k++;
        }
        // iterate through ani_vec staggering cards according to ID
        for (int i = 0; i < numFrames + 10 * staggerAmt; i++) {
            for (std::shared_ptr<AnimationWrapperST> item : ani_vec) {
                if (item->getID() <= i) {
                    item->advance(i - item->getID());
                }
            }
            view->draw(window);
        }
        // put cards into correct piles and reveal cards
        for (int i = 0; i < 10; i++) {
            model->getMainPile(i + 1)->push_back(model->getMovePile()->at(i));
            model->revealCard(model->getMainPile(i + 1));
        }
        model->getMovePile()->clear();
        // check for full stacks (every main pile)
        for (int i = 1; i < 11; i++) {
            if (controller->checkFullStack(model->getMainPile(i))) {
                if (!controller->getRedoStack()->empty()) {
                    controller->getRedoStack()->pop();
                }
                // create FillFoundationPile command
                std::shared_ptr<Command> fill = std::make_shared<FillFoundationPile>(model, view, controller, 
                window, model->getMainPile(i));
                // push to undoStack
                controller->getUndoStack()->push(fill);
                // execute fill
                fill->execute();
            }
        }
    }
}

// put cards into movePile, animate to correct draw pile, place all 10 cards into drawPile
void DealOneRound::undo() {
    // put 10 cards face down and put one card from each pile into movePile
    for (int i = 1; i < 11; i++) {
        model->getMainPile(i)->back()->setFaceUp(false);
        model->getMovePile()->push_back(model->getMainPile(i)->back());
        model->getMainPile(i)->pop_back();
    }
    // create animation wrapper (self terminating) for each card
    std::vector<std::shared_ptr<AnimationWrapperST>> ani_vec = std::vector<std::shared_ptr<AnimationWrapperST>>();
    int staggerAmt = 10;
    int numFrames = 30;
    int j = 10;
    int k = 9;
    for (int i = 0; i < 10 * staggerAmt; i += staggerAmt) {
        std::shared_ptr<AnimationWrapperST> animation = std::make_shared<AnimationWrapperST>(
            model->getMovePile()->at(k)->getPSprite(), view->getNextXPos(model->getMainPile(j)),
            view->getNextYPos(model->getMainPile(j)), view->getNextXPos(correct_draw_pile), 
            view->getNextYPos(correct_draw_pile), numFrames
        );
        animation->setID(i);
        ani_vec.push_back(animation);
        j--;
        k--;
    }
    // iterate through ani_vec staggering cards according to ID
    for (int i = 0; i < numFrames + 10 * staggerAmt; i++) {
        for (std::shared_ptr<AnimationWrapperST> item : ani_vec) {
            if (item->getID() <= i) {
                item->advance(i - item->getID());
            }
        }
        view->draw(window);
    }
    // put cards back in draw pile
    model->cardsFromMove(correct_draw_pile);
}

#endif