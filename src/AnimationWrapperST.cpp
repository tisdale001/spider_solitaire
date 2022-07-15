// AnimationWrapperST.cpp
// Wrapper class (Self Terminating) for animating cards in Spider Solitaire
#ifndef ANIMATIONWRAPPERST_CPP
#define ANIMATIONWRAPPERST_CPP

//Include Header files
#include <AnimationWrapperST.hpp>

AnimationWrapperST::AnimationWrapperST(std::shared_ptr<sf::Sprite> card_, float beginXPos_, float beginYPos_, float endXPos_, 
float endYPos_, int numFrames_) {
    card = card_;
    //std::cout << "Checkpoint 1\n";
    beginXPos = beginXPos_;
    beginYPos = beginYPos_;
    //std::cout << "Checkpoint 2\n";
    endXPos = endXPos_;
    endYPos = endYPos_;
    numFrames = numFrames_;
    x_to_move = (float)((endXPos - beginXPos) / numFrames);
    y_to_move = (float)((endYPos - beginYPos) / numFrames);
    //std::cout << y_to_move << std::endl;
    //std::cout << "Checkpoint 3\n";
    card->setPosition(beginXPos, beginYPos);
    
}

AnimationWrapperST::~AnimationWrapperST() {}

// advances position of sprite one small step and changes begin position
void AnimationWrapperST::advance(int frame) {
    // self terminate by making numFrames the limit of movement
    if (frame > numFrames) {
        frame = numFrames;
    }
    float bXPos = this->beginXPos + (x_to_move * frame);
    float bYPos = this->beginYPos + (y_to_move * frame);
    //std::cout << "Checkpoint 2\n";
    card->setPosition(bXPos, bYPos);
}

void AnimationWrapperST::setID(int num) {
    wrapperID = num;
}
int AnimationWrapperST::getID() {
    return wrapperID;
}
std::shared_ptr<sf::Sprite> AnimationWrapperST::getPSprite() {
    return card;
}

#endif