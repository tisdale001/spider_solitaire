// FillFoundationPile.cpp
// Command that fills next Foundation pile in spider solitaire
#ifndef FILLFOUNDATIONPILE_CPP
#define FILLFOUNDATIONPILE_CPP

#include <FillFoundationPile.hpp>

FillFoundationPile::FillFoundationPile(Model* model_, View* view_, Controller* controller_, 
sf::RenderWindow* window_, std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile_) {
    model = model_;
    view = view_;
    controller = controller_;
    window = window_;
    from_pile = from_pile_;
    // get correct to_pile (foundation pile)
    to_pile = model->getCorrectFoundationPile();
}
FillFoundationPile::~FillFoundationPile() {}

// move stack from from_pile into correct foundation pile, animate
void FillFoundationPile::execute() {
    // movePile will be empty
    // get stack distance from from_pile
    int lastStackDistance = view->getStackDistance(from_pile);
    // move 13 cards from from_pile into movePile
    for (int i = 0; i < 13; i++) {
        model->getMovePile()->push_back(from_pile->back());
        from_pile->pop_back();
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
    // create second animation which shrinks the pile
    std::vector<std::shared_ptr<AnimationWrapperST>> ani_vec2 = std::vector<std::shared_ptr<AnimationWrapperST>>();
    num_frames = 8;
    int count = 0;
    for (int i = (int)model->getMovePile()->size() - 1; i >= 0; i--) {
        ani_vec2.push_back(std::make_shared<AnimationWrapperST>(model->getMovePile()->at(i)->getPSprite(), 
        model->getMovePile()->at(i)->getPSprite()->getPosition().x,
        model->getMovePile()->at(i)->getPSprite()->getPosition().y,
        view->getNextXPos(to_pile), view->getNextYPos(to_pile), count));
        count += num_frames;
    }
    // iterate through ani_vec2: calling advance()
    for (int i = 0; i < count; i++) {
        for (std::shared_ptr<AnimationWrapperST> item : ani_vec2) {
            item->advance(i);
        }
        view->draw(window);
    }
    // move cards into new pile
    model->cardsFromMove(to_pile);
    // reveal card if necessary
    card_revealed = model->revealCard(from_pile);
    if (controller->checkWin()) {
        // setup random number
        srand((unsigned) time(0));
        int num = rand() % 2;
        if (num == 0) {
            view->animateWin(window);
        }
        else {
            view->animateWin2(window);
        }
    }
}

// move full stack back to from_pile; call Controller::Undo() again for previous move
void FillFoundationPile::undo() {
    // flip target card on from_pile if necessary
    if (card_revealed) {
        from_pile->back()->setFaceUp(false);
    }
    // get newStackDistance from from_pile
    int newStackDistance = view->getStackDistance(from_pile);
    // create animation that correctly resizes stack
    while (!to_pile->empty()) {
        model->getMovePile()->push_back(to_pile->back());
        to_pile->pop_back();
    }
    std::vector<std::shared_ptr<AnimationWrapper>> ani_vec = std::vector<std::shared_ptr<AnimationWrapper>>();
    int num_frames = 8;
    int count = 12 * num_frames;
    int ID_num = 0;
    int j = model->getMovePile()->size() - 1;
    for (int i = 0; i < (int)model->getMovePile()->size(); i++) {
        std::shared_ptr<AnimationWrapper> animation = std::make_shared<AnimationWrapper>(
            model->getMovePile()->at(i)->getPSprite(), 
            model->getMovePile()->at(i)->getPSprite()->getPosition().x,
            model->getMovePile()->at(i)->getPSprite()->getPosition().y,
            view->getNextXPos(to_pile), view->getNextYPos(to_pile) + newStackDistance * j, count);
        animation->setID(ID_num);
        ani_vec.push_back(animation);
        j--;
        count -= num_frames;
        ID_num += num_frames;
    }
    // iterate through ani_vec: calling advance(): staggering movement
    for (int i = 0; i <= 12 * num_frames; i++) {
        for (std::shared_ptr<AnimationWrapper> item : ani_vec) {
            if (item->getID() <= i) {
                item->advance(i - item->getID());
            }
        }
        view->draw(window);
    }
    // create second animation that moves stack back to from_pile
    std::vector<std::shared_ptr<AnimationWrapper>> ani_vec2 = std::vector<std::shared_ptr<AnimationWrapper>>();
    num_frames = 30;
    j = 0;
    for (int i = (int)model->getMovePile()->size() - 1; i >= 0; i--) {
        std::shared_ptr<AnimationWrapper> animation = std::make_shared<AnimationWrapper>(
            model->getMovePile()->at(i)->getPSprite(), 
            model->getMovePile()->at(i)->getPSprite()->getPosition().x,
            model->getMovePile()->at(i)->getPSprite()->getPosition().y,
            view->getNextXPos(from_pile), view->getNextYPos(from_pile) + newStackDistance * j, num_frames);
        ani_vec2.push_back(animation);
        j++;
    }
    // iterate through ani_vec2: calling advance
    for (int i = 0; i < num_frames; i++) {
        for (std::shared_ptr<AnimationWrapper> item: ani_vec2) {
            item->advance(i);
        }
        view->draw(window);
    }
    // put cards onto from_pile
    model->cardsFromMove(from_pile);
    // call Undo() for previous move
    controller->Undo();
}

#endif