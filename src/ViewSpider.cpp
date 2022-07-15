// ViewSpider.cpp
// View for Spider Solitaire
#ifndef VIEWSPIDER_CPP 
#define VIEWSPIDER_CPP

// Include header file
#include <ViewSpider.hpp>

View::View() {}
View::~View() {}

// initiates view with all pile pointers and member variables
void View::initiateView(std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile1_, 
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
    std::shared_ptr<Deck> deck_) {
    mainPile1 = mainPile1_;
    mainPile2 = mainPile2_;
    mainPile3 = mainPile3_;
    mainPile4 = mainPile4_;
    mainPile5 = mainPile5_;
    mainPile6 = mainPile6_;
    mainPile7 = mainPile7_;
    mainPile8 = mainPile8_;
    mainPile9 = mainPile9_;
    mainPile10 = mainPile10_;
    foundationPile1 = foundationPile1_;
    foundationPile2 = foundationPile2_;
    foundationPile3 = foundationPile3_;
    foundationPile4 = foundationPile4_;
    foundationPile5 = foundationPile5_;
    foundationPile6 = foundationPile6_;
    foundationPile7 = foundationPile7_;
    foundationPile8 = foundationPile8_;
    drawPile1 = drawPile1_;
    drawPile2 = drawPile2_;
    drawPile3 = drawPile3_;
    drawPile4 = drawPile4_;
    drawPile5 = drawPile5_;
    movePile = movePile_;
    dealPile = dealPile_;
    deck = deck_;
    cardHeight = deck->getTopSprite()->getGlobalBounds().height;
    cardWidth = deck->getTopSprite()->getGlobalBounds().width;
    image.create(bounds_width, bounds_height, sf::Color::Black);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    lastStackDistance = stackDistance;
}

// getClick returns pile and index clicked on in view
std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> View::getClick(sf::Vector2f mousePos) {
    // check if clicked on sprites
    // check main piles
    for (int i = 1; i < 11; i++) {
        if (!getMainPile(i)->empty()) {
            for (int j = (int)getMainPile(i)->size() - 1; j >= 0; j--) {
                if (getMainPile(i)->at(j)->getPSprite()->getGlobalBounds().contains(mousePos)) {
                    return std::make_pair(getMainPile(i), j);
                }
            }
        }
    }
    // check draw piles
    for (int i = 5; i > 0; i--) {
        if (!getDrawPile(i)->empty()) {
            if (getDrawPile(i)->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
                return std::make_pair(getDrawPile(i), 0);
            }
        }
    }
    // check if clicked in empty slots (main piles)
    float x = mousePos.x;
    float y = mousePos.y;
    for (int i = 0; i < 10; i++) {
        if (x > startPointX - distBtwPiles / 2 + cardWidth * i + distBtwPiles * i && x < startPointX + distBtwPiles / 2 +
            cardWidth + cardWidth * i + distBtwPiles * i && y > startPointY - distBtwPiles / 2 + cardHeight + distBtwPiles && 
            y < startPointY + distBtwPiles / 2 + cardHeight * 2 + distBtwPiles) {
            return std::make_pair(getMainPile(i + 1), 0);
        }
    }
    return std::make_pair(nullptr, 0);
}

// getRelease returns pile click-released on
std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> View::getRelease(sf::Vector2f mousePos) {
    float x = mousePos.x;
    float y = mousePos.y;
    // check main piles
    for (int i = 0; i < 10; i++) {
        if (!getMainPile(i + 1)->empty()) {
            // main pile not empty: include perimeter around stack
            if (x > startPointX - distBtwPiles / 2 + cardWidth * i + distBtwPiles * i && x < startPointX + distBtwPiles / 2 +
            cardWidth + cardWidth * i + distBtwPiles * i && y > startPointY + cardHeight + distBtwPiles - distBtwPiles / 2 
            && y < startPointY + cardHeight * 2 + distBtwPiles + distBtwPiles / 2 + (getMainPile(i + 1)->size() - 1) * 
            getStackDistance(getMainPile(i + 1))) {
                return std::make_pair(getMainPile(i + 1), 0);
            }
        }
        else {
            // main pile empty: empty space plus perimeter
            if (x > startPointX - distBtwPiles / 2 + cardWidth * i + distBtwPiles * i && x < startPointX + distBtwPiles / 2 +
            cardWidth + cardWidth * i + distBtwPiles * i && y > startPointY + cardHeight + distBtwPiles - distBtwPiles / 2
            && y < startPointY + cardHeight * 2 + distBtwPiles + distBtwPiles / 2) {
                return std::make_pair(getMainPile(i + 1), 0);
            }
        }
    }
    // check draw piles with global bounds
    for (int i = 5; i > 0; i--) {
        if (!getDrawPile(i)->empty()) {
            if (getDrawPile(i)->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
                return std::make_pair(getDrawPile(i), 0);
            }
        }
    }
    return std::make_pair(nullptr, 0);
}

// sets position of each sprite for normal display
void View::setPosition() {
    //std::cout << "setPosition() called\n";
    // set position of all sprites except movePile
    for (int i = 0; i < 10; i++) {
        if (!getMainPile(i + 1)->empty()) {
            for (int j = 0; j < (int)getMainPile(i + 1)->size(); j++) {
                getMainPile(i + 1)->at(j)->getPSprite()->setPosition(startPointX + cardWidth * i + distBtwPiles * i,
                startPointY + cardHeight + distBtwPiles + getStackDistance(getMainPile(i + 1)) * j);
            }
        }
    }
    // back sprites of draw piles
    for (int i = 0; i < 5; i++) {
        if (!getDrawPile(i + 1)->empty()) {
            getDrawPile(i + 1)->back()->getPSprite()->setPosition(startPointX + stackDistance * i, startPointY);
        }
    }
    // back sprites of foundation piles
    for (int i = 0; i < 8; i++) {
        if (!getFoundationPile(i + 1)->empty()) {
            getFoundationPile(i + 1)->back()->getPSprite()->setPosition(startPointX + cardWidth * 2 + distBtwPiles * 2 +
            cardWidth * i + distBtwPiles * i, startPointY);
        }
    }
    // back sprite of dealPile
    if (!dealPile->empty()) {
        dealPile->back()->getPSprite()->setPosition(startPointX, startPointY);
    }
}

// draws all sprites in non empty piles
void View::draw(sf::RenderWindow* window) {
    window->clear();
	// set all sprite positions
    setPosition();

    // main piles
    for (int i = 1; i < 11; i++) {
        if (!getMainPile(i)->empty()) {
            for (int j = 0; j < (int)getMainPile(i)->size(); j++) {
                window->draw(*(getMainPile(i)->at(j)->getPSprite()));
            }
        }
    }
    // draw piles
    for (int i = 1; i < 6; i++) {
        if (!getDrawPile(i)->empty()) {
            window->draw(*(getDrawPile(i)->back()->getPSprite()));
        }
    }
    // foundation piles
    for (int i = 1; i < 9; i++) {
        if (!getFoundationPile(i)->empty()) {
            window->draw(*(getFoundationPile(i)->back()->getPSprite()));
        }
    }
    // deal pile
    if (!dealPile->empty()) {
        window->draw(*(dealPile->back()->getPSprite()));
    }
    // movePile
    for (int i = (int)movePile->size() - 1; i >= 0; i--) {
        window->draw(*(movePile->at(i)->getPSprite()));
    }

    window->display();
}

//void View::animateCards(sf::RenderWindow* window, std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile);

// animates card explosion after a win
void View::animateWin(sf::RenderWindow* window) {
    srand(time(NULL));
    Deck deck1 = Deck();
    Deck deck2 = Deck();
    Deck deck3 = Deck();
    Deck deck4 = Deck();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> card_vec = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    while (!deck1.isEmpty()) {
        deck1.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck2.isEmpty()) {
        deck2.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck3.isEmpty()) {
        deck3.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck4.isEmpty()) {
        deck4.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    // continue while loop till key is pressed or mouse clicked
    bool animation = true;
    while (animation) {
        sf::Event event;
        while (window->pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
				//window->close();
                animation = false;
                break;
			}
            else if (event.type == sf::Event::KeyReleased) {
                animation = false;
                break;
            }
        }
        if (animation == false) {
            break;
        }
        // code card burst here
        // create wrapper vec
        int numFrames = 200;
        std::vector<AnimationWrapper> ani_vec;
        int i = 0;
        for (auto item : *card_vec) {
            AnimationWrapper wrapper = AnimationWrapper(item->getPSprite(), bounds_width / 2 - cardWidth / 2, 
                bounds_height / 2 - cardHeight / 2,
                (rand() % (bounds_width + 200)) - 100, (rand() % (bounds_height + 200)) - 100, numFrames);
            wrapper.setID(i);
            ani_vec.push_back(wrapper);
            i++;
        }
        // iterate through ani_vec, adding one each time
        for (int i = 0; i < (int)ani_vec.size() - 1; i++) {
            window->clear();
            for (int j = 0; j < i + 1; j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
        // keep animating more frames
        for (int i = (int)ani_vec.size(); i < (int)ani_vec.size() + 600; i++) {
            window->clear();
            for (int j = 0; j < (int)ani_vec.size(); j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
    }
}

// animates card explosion after a win
void View::animateWin2(sf::RenderWindow* window) {
    srand(time(NULL));
    Deck deck1 = Deck();
    Deck deck2 = Deck();
    Deck deck3 = Deck();
    Deck deck4 = Deck();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> card_vec = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    while (!deck1.isEmpty()) {
        deck1.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck2.isEmpty()) {
        deck2.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck3.isEmpty()) {
        deck3.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck4.isEmpty()) {
        deck4.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    // continue while loop till key is pressed or mouse clicked
    bool animation = true;
    while (animation) {
        sf::Event event;
        while (window->pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
				//window->close();
                animation = false;
                break;
			}
            else if (event.type == sf::Event::KeyReleased) {
                animation = false;
                break;
            }
        }
        if (animation == false) {
            break;
        }
        // code card burst here
        // create wrapper vec
        int numFrames = 200;
        std::vector<AnimationWrapper> ani_vec;
        int i = 0;
        for (auto item : *card_vec) {
            AnimationWrapper wrapper = AnimationWrapper(item->getPSprite(), 
                (rand() % (bounds_width + 200)) - 100, 
                (rand() % (bounds_height + 200)) - 100,
                (rand() % (bounds_width + 200)) - 100, (rand() % (bounds_height + 200)) - 100, numFrames);
            wrapper.setID(i);
            ani_vec.push_back(wrapper);
            i++;
        }
        // iterate through ani_vec, adding one each time
        for (int i = 0; i < (int)ani_vec.size() - 1; i++) {
            window->clear();
            for (int j = 0; j < i + 1; j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
        // keep animating more frames
        for (int i = (int)ani_vec.size(); i < (int)ani_vec.size() + 600; i++) {
            window->clear();
            for (int j = 0; j < (int)ani_vec.size(); j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
    }
}

// getter
int View::getBoundsWidth() {
    return bounds_width;
}

//getter
int View::getBoundsHeight() {
    return bounds_height;
}

// getter
int View::getLastStackDistance() {
    return lastStackDistance;
}

// getter: returns pointer to last pile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getLastPile() {
    return lastPile;
}

// getter for proper stack distance: shrinks as pile gets larger
int View::getStackDistance(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!pile->empty()) {
        // if movePile: return lastStackDistance
        if (pile == movePile) {
            return lastStackDistance;
        }
        else if (pile == lastPile) {
            return lastStackDistance;
        }
        else if (pile->size() > 18) {
            return (int)(stackDistance * (1 - 0.025 * (pile->size() - 18)));
        }
    }
    return stackDistance;
}

// getter: main pile by number
std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getMainPile(int num) {
    switch(num) {
        case 1 :
            return mainPile1;
        case 2 :
            return mainPile2;
        case 3 :
            return mainPile3;
        case 4 :
            return mainPile4;
        case 5 :
            return mainPile5;
        case 6 :
            return mainPile6;
        case 7 :
            return mainPile7;
        case 8 :
            return mainPile8;
        case 9 :
            return mainPile9;
        case 10 :
            return mainPile10;
        default :
            return nullptr;
    }
}

// getter: returns foundation pile by number
std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getFoundationPile(int num) {
    switch(num) {
        case 1 :
            return foundationPile1;
        case 2 :
            return foundationPile2;
        case 3 :
            return foundationPile3;
        case 4 :
            return foundationPile4;
        case 5 :
            return foundationPile5;
        case 6 : 
            return foundationPile6;
        case 7 :
            return foundationPile7;
        case 8 :
            return foundationPile8;
        default:
            return nullptr;
    }
}

// getter: returns draw pile by number
std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getDrawPile(int num) {
    switch(num) {
        case 1 :
            return drawPile1;
        case 2 :
            return drawPile2;
        case 3 :
            return drawPile3;
        case 4 :
            return drawPile4;
        case 5 :
            return drawPile5;
        default :
            return nullptr;
    }
}

// getter: returns movePile
std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getMovePile() {
    return movePile;
}

// returns X coordinate of the next position in pile
int View::getNextXPos(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    for (int i = 0; i < 10; i++) {
        if (pile == this->getMainPile(i + 1)) {
            return (startPointX + cardWidth * i + distBtwPiles * i);
        }
    }
    // check draw piles
    for (int i = 0; i < 5; i++) {
        if (pile == this->getDrawPile(i + 1)) {
            return (startPointX + stackDistance * i);
        }
    }
    // check foundation piles starting with last pile
    for (int i = 7; i >= 0; i--) {
        if (pile == this->getFoundationPile(i + 1)) {
            return (startPointX + cardWidth * 2 + distBtwPiles * 2 + cardWidth * i + distBtwPiles * i);
        }
    }
    return 0;
}

// returns y coordinate of the next position in pile
int View::getNextYPos(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    for (int i = 1; i < 11; i++) {
        if (pile == this->getMainPile(i)) {
            return (startPointY + cardHeight + distBtwPiles + getStackDistance(getMainPile(i)) * (int)getMainPile(i)->size());
        }
    }
    // check draw piles
    for (int i = 1; i < 6; i++) {
        if (pile == this->getDrawPile(i)) {
            return startPointY;
        }
    }
    // check foundation piles starting with last pile
    for (int i = 7; i >= 0; i--) {
        if (pile == this->getFoundationPile(i + 1)) {
            return startPointY;
        }
    }
    return 0;
}

// setter: sets lastStackDistance
void View::setLastStackDistance(int stk_dist) {
    lastStackDistance = stk_dist;
}

// setter: sets lastPile
void View::setLastPile(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    lastPile = pile;
}

//std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getMovePile();
//std::shared_ptr<Deck> View::getDeck();

#endif