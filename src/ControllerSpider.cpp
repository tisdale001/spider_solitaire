// ControllerSpider.cpp
// Controller for Spider solitaire game
#ifndef CONTROLLERSPIDER_CPP 
#define CONTROLLERSPIDER_CPP 

#include <ControllerSpider.hpp>

//class DealOneRound;

Controller::Controller() {}
Controller::~Controller() {}

// main loop of game
void Controller::playGame() {
    view.initiateView(model.getMainPile(1), model.getMainPile(2), model.getMainPile(3), model.getMainPile(4), model.getMainPile(5),
    model.getMainPile(6), model.getMainPile(7), model.getMainPile(8), model.getMainPile(9), model.getMainPile(10), 
    model.getFoundationPile(1), model.getFoundationPile(2), model.getFoundationPile(3), model.getFoundationPile(4),
    model.getFoundationPile(5), model.getFoundationPile(6), model.getFoundationPile(7), model.getFoundationPile(8),
    model.getDrawPile(1), model.getDrawPile(2), model.getDrawPile(3), model.getDrawPile(4), model.getDrawPile(5),
    model.getMovePile(), model.getDealPile(), model.getDeck());

    // setup random number
    srand((unsigned) time(0));

    sf::RenderWindow window(sf::VideoMode(view.getBoundsWidth(), view.getBoundsHeight()), 
    " Spider Solitaire", sf::Style::Close);

    // deal hand
    model.allDeckCardsToDealPile(model.getDeck());
    this->dealTableau(&window);
    view.draw(&window);

    // main loop
    while (window.isOpen()) {

        sf::Event event;

		while (window.pollEvent(event)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> click = view.getClick(mousePos);
                    if (click.first != nullptr) {
                        // continue with move, setup lastPile
                        if (click.first == model.getCorrectDrawPile()) {
                            // deal out a round of cards if LEGAL DEAL
                            if (this->checkLegalDeal()) {
                                // create DealOneRound, add to undoStack
                                std::shared_ptr<Command> deal = std::make_shared<DealOneRound>(&model, &view, this, &window);
                                undoStack->push(deal);
                                deal->execute();
                                this->clearRedoStack();
                            }
                            else {
                                // print directions if deal not legal
                                std::cout << "There must be at least one card in each pile in order to deal.\n";
                            }
                        }
                        else {
                            // mainPile clicked on
                            if (!click.first->empty()) {
                                if (click.first->at(click.second)->getFaceUp()) {
                                    // check if legal stack
                                    if (this->checkMove(click.first, click.second)) {
                                        // put cards in movePile, set lastPile and lastStackDistance, clearRedoStack()
                                        view.setLastStackDistance(view.getStackDistance(click.first));
                                        model.cardsToMove(click.first, click.second);
                                        view.setLastPile(click.first);
                                        this->clearRedoStack();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> click = view.getRelease(mousePos);
                    if (click.first != nullptr) {
                        if (!model.getMovePile()->empty()) {
                            // continue with move, check lastPile
                            if (model.checkDrawPile(click.first)) {
                                // draw pile clicked on: return to lastPile
                                this->moveToLastPile(&window);
                            }
                            else if (click.first == view.getLastPile()) {
                                // lastPile click-released on: make best move
                                this->makeBestMove(&window);
                            }
                            else {
                                // new pile click-released on: make move or return to lastPile
                                if (this->checkDrop(click.first)) {
                                    // legal move
                                    // create Move command
                                    std::shared_ptr<Command> move = std::make_shared<Move>(&model, &view, this, &window,
                                        view.getLastPile(), (int)view.getLastPile()->size(), click.first, (int)click.first->size());
                                    undoStack->push(move);
                                    move->execute();
                                    
                                }
                                else {
                                    // move is illegal: return to lastPile
                                    // create and execute Move, but do not add to stack
                                    this->moveToLastPile(&window);
                                }
                            }
                        }
                    }
                    else {
                        // null click-released: if movePile not empty, move to lastPile
                        if (!model.getMovePile()->empty()) {
                            this->moveToLastPile(&window);
                        }
                    }
                }
                once = 1;
                pressedLastFrame = false;
            }
            if (event.type == sf::Event::Closed) {
				window.close();
                break;	
			}
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Escape) {
					window.close();
					break;
				}
                else if (event.key.code == sf::Keyboard::D) {
                    // redeal
                    this->redeal(&window);
                }
                else if (event.key.code == sf::Keyboard::Z) {
                    // undo
                    this->Undo();
                }
                else if (event.key.code == sf::Keyboard::Y) {
                    // redo
                    this->Redo();
                }
                else if (event.key.code == sf::Keyboard::M) {
                    int num = rand() % 2;
                    if (num == 0) {
                        view.animateWin(&window);
                    }
                    else {
                        view.animateWin2(&window);
                    }
                }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // drag movePile
            if (!model.getMovePile()->empty()) {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                sf::Vector2f cardPos = model.getMovePile()->back()->getPSprite()->getPosition();
			    if(pressedLastFrame || (mousePos.x > xPos && mousePos.y > yPos
        	    && mousePos.x - view.getBoundsWidth() < xPos && mousePos.y - 
                view.getBoundsHeight() < yPos))
    		    {
        		    if(once)
        		    {
            		    xDiff = mousePos.x - cardPos.x;
            		    yDiff = mousePos.y - cardPos.y;
            	    	once = 0;
        		    }
        		    xPos = mousePos.x - xDiff;
        		    yPos = mousePos.y - yDiff;
				    for (int i = (int)model.getMovePile()->size() - 1; i >= 0; i--) {
					    model.getMovePile()->at(i)->getPSprite()->setPosition(xPos, yPos + 
                        view.getStackDistance(model.getMovePile()) * (model.getMovePile()->size() - 1 - i));
				    }
    		    }
    		    pressedLastFrame = true;
		    }
		    
        }
        
        // draw all cards
        //std::cout << "view.draw() called\n";
        view.draw(&window);
    }
}

// deals Tableau, manages animation
void Controller::dealTableau(sf::RenderWindow* window) {
    // deal 10 cards 5 times
    for (int h = 0; h < 5; h++) {
        // put 10 cards into movePile
        for (int i = 0; i < 10; i++) {
            model.dealOneCardFromPile(model.getDealPile(), model.getMovePile());
        }
        // create animation wrappers for each card
        std::vector<std::shared_ptr<AnimationWrapperST>> ani_vec = std::vector<std::shared_ptr<AnimationWrapperST>>();
        int staggerAmt = 10;
        int numFrames = 40;
        int j = 1;
        int k = 0;
        for (int i = 0; i < 10 * staggerAmt; i += staggerAmt) {
            std::shared_ptr<AnimationWrapperST> animation = std::make_shared<AnimationWrapperST>(
                model.getMovePile()->at(k)->getPSprite(), view.getNextXPos(model.getDrawPile(1)), 
                view.getNextYPos(model.getDrawPile(1)), view.getNextXPos(model.getMainPile(j)),
                view.getNextYPos(model.getMainPile(j)), numFrames
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
            view.draw(window);
        }
        // put cards into correct piles
        for (int i = 0; i < 10; i++) {
            model.getMainPile(i + 1)->push_back(model.getMovePile()->at(i));
        }
        model.getMovePile()->clear();
    }
    // deal last 4 cards
    // put 4 cards into movePile
    for (int i = 0; i < 4; i++) {
        model.dealOneCardFromPile(model.getDealPile(), model.getMovePile());
    }
    // create animation wrappers for each card
    std::vector<std::shared_ptr<AnimationWrapperST>> ani_vec = std::vector<std::shared_ptr<AnimationWrapperST>>();
    int staggerAmt = 10;
    int numFrames = 40;
    int j = 1;
    int k = 0;
    for (int i = 0; i < 4 * staggerAmt; i += staggerAmt) {
        std::shared_ptr<AnimationWrapperST> animation = std::make_shared<AnimationWrapperST>(
            model.getMovePile()->at(k)->getPSprite(), view.getNextXPos(model.getDrawPile(1)), 
            view.getNextYPos(model.getDrawPile(1)), view.getNextXPos(model.getMainPile(j)),
            view.getNextYPos(model.getMainPile(j)), numFrames
        );
        animation->setID(i);
        ani_vec.push_back(animation);
        j++;
        k++;
    }
    // iterate through ani_vec staggering cards according to ID
    for (int i = 0; i < numFrames + 4 * staggerAmt; i++) {
        for (std::shared_ptr<AnimationWrapperST> item : ani_vec) {
            if (item->getID() <= i) {
                item->advance(i - item->getID());
            }
        }
        view.draw(window);
    }
    // put cards into correct piles
    for (int i = 0; i < 4; i++) {
        model.getMainPile(i + 1)->push_back(model.getMovePile()->at(i));
    }
    model.getMovePile()->clear();

    // reveal cards in each pile
    for (int i = 1; i < 11; i++) {
        model.revealCard(model.getMainPile(i));
    }

    // put cards into draw piles
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            model.dealOneCardFromPile(model.getDealPile(), model.getDrawPile(i));
        }
    }
}

// returns cards to deck, shuffles, puts all cards in dealPile, redeals
void Controller::redeal(sf::RenderWindow* window) {
    while (!this->getUndoStack()->empty()) {
        this->getUndoStack()->pop();
    }
    while (!this->getRedoStack()->empty()) {
        this->getRedoStack()->pop();
    }
    model.allCardsReturnToDeck(model.getDeck());
    model.shuffleCards();
    model.allDeckCardsToDealPile(model.getDeck());
    this->dealTableau(window);
}

// if legal deal (all main piles NOT empty): returns true
bool Controller::checkLegalDeal() {
    for (int i = 1; i < 11; i++) {
        if (model.getMainPile(i)->empty()) {
            return false;
        }
    }
    return true;
}

// checks if legal move by checking if all cards in stack are in order
bool Controller::checkMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile, int index) {
    int val = pile->back()->getValue();
    for (int i = pile->size() - 1; i >= index; i--) {
        if (pile->at(i)->getValue() != val) {
            return false;
        }
        val++;
    }
    return true;
}

// checks if movePile stack can be put on new pile
bool Controller::checkDrop(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (pile->empty()) {
        return true;
    }
    // movePile already checked for empty
    if (model.getMovePile()->back()->getValue() == pile->back()->getValue() - 1) {
        return true;
    }
    return false;
}

// checks if pile contains full stack (Ace through King): return true if full stack
bool Controller::checkFullStack(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!pile->empty()) {
        if (pile->size() >= 13) {
            int j = 1;
            for (int i = (int)pile->size() - 1; i >= (int)pile->size() - 13; i--) {
                if (pile->at(i)->getValue() != j) {
                    return false;
                }
                j++;
            }
            return true;
        }
    }
    return false;
}

// checks if game is won by checking if all foundation piles are full
bool Controller::checkWin() {
    for (int i = 1; i < 9; i++) {
        if (model.getFoundationPile(i)->empty()) {
            return false;
        }
    }
    return true;
}

// executes best move possible or returns stack to lastPile
void Controller::makeBestMove(sf::RenderWindow* window) {
    // no need to check if movePile is empty or not (already checked)
    // first: get vector of possible piles to move to
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<Card>>>> poss_piles;
    for (int i = 10; i >= 1; i--) {
        if (!model.getMainPile(i)->empty()) {
            // check back of mainPile: compare to back of movePile
            if (model.getMovePile()->back()->getValue() + 1 == model.getMainPile(i)->back()->getValue()) {
                poss_piles.push_back(model.getMainPile(i));
            }
        }
        else {
            // mainPile is empty: it is possible move
            poss_piles.push_back(model.getMainPile(i));
        }
    }
    if (poss_piles.empty()) {
        // no possible move: return to lastPile
        this->moveToLastPile(window);
    }
    else if (poss_piles.size() == 1) {
        if (poss_piles.back() == view.getLastPile()) {
            // only possible move is lastPile: return to lastPile
            this->moveToLastPile(window);
        }
        else {
            // only possible move is NOT lastPile: make move
            // create Move command
            std::shared_ptr<Command> move = std::make_shared<Move>(&model, &view, this, window,
                view.getLastPile(), (int)view.getLastPile()->size(), poss_piles.back(), (int)poss_piles.back()->size());
            this->undoStack->push(move);
            move->execute();
        }
    }
    else {
        // poss_piles size > 1: choose largest stack to move to, this is best move
        // if piles are equal: the first is fine
        int max_count = -1;
        std::shared_ptr<std::vector<std::shared_ptr<Card>>> bestPile = nullptr;
        for (std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile : poss_piles) {
            if (this->getSizeOfStack(pile) == max_count && pile != view.getLastPile()) {
                bestPile = pile;
                max_count = this->getSizeOfStack(pile);
            }
            else if (this->getSizeOfStack(pile) > max_count) {
                bestPile = pile;
                max_count = this->getSizeOfStack(pile);
            }
        }
        if (bestPile != view.getLastPile()) {
            // make move into bestPile, execute and add to undoStack
            std::shared_ptr<Command> move = std::make_shared<Move>(&model, &view, this, window,
                view.getLastPile(), (int)view.getLastPile()->size(), bestPile, (int)bestPile->size());
            undoStack->push(move);
            move->execute();
        }
        else {
            // bestPile == lastPile: do not add to undoStack
            model.cardsFromMove(bestPile);
        }
    }

}

// helper method: returns number of upturned cards in pile
int Controller::getNumUpturnedCards(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    int count = 0;
    for (std::shared_ptr<Card> card : *pile) {
        if (card->getFaceUp()) {
            count++;
        }
    }
    return count;
}

// helper method: returns size of stack at base of pile
int Controller::getSizeOfStack(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    int pile_size = this->getNumUpturnedCards(pile);
    if (pile_size <= 1) {
        return pile_size;
    }
    else {
        // pile size is greater than 1
        int count = 1;
        for (int i = (int)pile->size() - 1; i > 0; i--) {
            // if card at i - 1 is face down: return count
            if (!pile->at(i - 1)->getFaceUp()) {
                return count;
            }
            // cards must be increasing in value by 1
            if (pile->at(i)->getValue() + 1 != pile->at(i - 1)->getValue()) {
                return count;
            }
            count++;
        }
        return count;
    }
    return 0;
}

void Controller::moveToLastPile(sf::RenderWindow* window) {
    // create and execute Move, but do not add to stack
    std::shared_ptr<Command> move = std::make_shared<Move>(&model, &view, this, window,
        view.getLastPile(), (int)view.getLastPile()->size(), view.getLastPile(), 
        (int)view.getLastPile()->size());
    move->execute();
}

// Undo one item on undoStack and push to redoStack
// Making a change here: push to redoStack first, then undo():
// This allows for FillFoundationPile to be called next
void Controller::Undo() {
    if (!undoStack->empty()) {
        if (model.getMovePile()->empty()) {
            redoStack->push(undoStack->top());
            undoStack->pop();
            redoStack->top()->undo();

        }
    }
}

// Redo one item on redoStack and push to undoStack
// Making a change here: push to undoStack first, then execute():
// This allows for FillFoundationPile to be called next if necessary
void Controller::Redo() {
    if (!redoStack->empty()) {
        if (model.getMovePile()->empty()) {
            undoStack->push(redoStack->top());
            redoStack->pop();
            undoStack->top()->execute();
        }
    }
}

// clears all commands from redoStack
void Controller::clearRedoStack() {
    while (!redoStack->empty()) {
        redoStack->pop();
    }
}

// getter
std::shared_ptr<std::stack<std::shared_ptr<Command>>> Controller::getUndoStack() {
    return undoStack;
}

// getter
std::shared_ptr<std::stack<std::shared_ptr<Command>>> Controller::getRedoStack() {
    return redoStack;
}

#endif