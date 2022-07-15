// Move.cpp which inherits from Command class
// Move class which represents one undoable move in spider solitaire
#ifndef MOVE_CPP
#define MOVE_CPP

// include header files
#include <Move.hpp>

Move::Move(Model* model_, View* view_, Controller* controller_, sf::RenderWindow* window_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile_, int from_index_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile_, int to_index_) {
        model = model_;
        view = view_;
        controller = controller_;
        window = window_;
        from_pile = from_pile_;
        from_index = from_index_;
        to_pile = to_pile_;
        to_index = to_index_;
    }

Move::~Move() {}

// TODO: add animation
// move card(s) from from_pile or movePile
void Move::execute() {
    int lastStackDistance;
    if (model->getMovePile()->empty()) {
        // movePile empty: first put cards into movePile
        // first get correct stack distance for animation
        lastStackDistance = view->getStackDistance(from_pile);
        model->cardsToMove(from_pile, from_index);
    }
    else {
        if (model->getMovePile()->size() == 1) {
            lastStackDistance = 0;
        }
        else {
            lastStackDistance = (int)(model->getMovePile()->at(0)->getPSprite()->getPosition().y -
                model->getMovePile()->at(1)->getPSprite()->getPosition().y);
        }
    }

    // animate movePile: create ani_vec
    std::vector<std::shared_ptr<AnimationWrapper>> ani_vec = std::vector<std::shared_ptr<AnimationWrapper>>();
    int num_frames = 30;
    int j = 0;
    for (int i = (int)model->getMovePile()->size() - 1; i >= 0; i--) {
        ani_vec.push_back(std::make_shared<AnimationWrapper>(model->getMovePile()->at(i)->getPSprite(), 
        model->getMovePile()->at(i)->getPSprite()->getPosition().x,
        model->getMovePile()->at(i)->getPSprite()->getPosition().y,
        view->getNextXPos(to_pile), view->getNextYPos(to_pile) + lastStackDistance * j, num_frames));
        j++;
    }
    // iterate through ani_vec: calling advance()
    for (int i = 0; i < num_frames; i++) {
        for (std::shared_ptr<AnimationWrapper> item : ani_vec) {
            item->advance(i);
        }
        view->draw(window);
    }

    // move cards into new pile
    model->cardsFromMove(to_pile);
    card_revealed = model->revealCard(from_pile);
    // check if to_pile has full stack (Ace to King) and create and execute FillFoundationPile
    if (controller->checkFullStack(to_pile)) {
        if (!controller->getRedoStack()->empty()) {
            controller->getRedoStack()->pop();
        }
        // create FillFoundationPile command
        std::shared_ptr<Command> fill = std::make_shared<FillFoundationPile>(model, view, controller, 
        window, to_pile);
        // push to undoStack
        controller->getUndoStack()->push(fill);
        // execute fill
        fill->execute();
    }
}

// TODO: add animation
// move card(s) from to_pile to from_pile
void Move::undo() {
    // first check if movePile is empty
    if (model->getMovePile()->empty()) {
        int lastStackDistance = view->getStackDistance(to_pile);
        model->cardsToMove(to_pile, to_index);

        // animate movePile: create ani_vec
        std::vector<std::shared_ptr<AnimationWrapper>> ani_vec = std::vector<std::shared_ptr<AnimationWrapper>>();
        int num_frames = 30;
        int j = 0;
        for (int i = (int)model->getMovePile()->size() - 1; i >= 0; i--) {
            ani_vec.push_back(std::make_shared<AnimationWrapper>(model->getMovePile()->at(i)->getPSprite(), 
            model->getMovePile()->at(i)->getPSprite()->getPosition().x,
            model->getMovePile()->at(i)->getPSprite()->getPosition().y,
            view->getNextXPos(from_pile), view->getNextYPos(from_pile) + lastStackDistance * j, num_frames));
            j++;
        }
        // iterate through ani_vec: calling advance()
        for (int i = 0; i < num_frames; i++) {
            for (std::shared_ptr<AnimationWrapper> item : ani_vec) {
                item->advance(i);
            }
            view->draw(window);
        }
        // if card was revealed, turn to face down
        if (card_revealed) {
            if (!from_pile->empty()) {
                from_pile->back()->setFaceUp(false);
            }
        }
        // move cards into from_pile
        model->cardsFromMove(from_pile);
    }
}


#endif