#include "Actor.h"
#include "StudentWorld.h"
#include <string>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, int direction, int depth, double size, StudentWorld* studentWorld) : GraphObject(imageID, startX, startY, direction, depth, size), m_studentWorld(studentWorld) {
    
}

bool Actor::isInactive() {
    return(false);
}

Actor::~Actor() {
    
}

StudentWorld* Actor::getWorld() {
    return(m_studentWorld);
}

Player::Player(int imageID, int startX, int startY, StudentWorld* studentWorld, int playerNum) : Actor(imageID, startX, startY, 0, 0, 1, studentWorld) {
    m_numCoins = 0;
    m_numStars = 0;
    m_playerNum = playerNum;
    ticks_to_move = 0;
    m_walking_direction = 0;
}

int Player::getTicks() const {
    return(ticks_to_move);
}

void Player::setTicks(int ticks) {
    ticks_to_move = ticks_to_move + ticks;
}

int Player::getPlayerNum() const {
    return(m_playerNum);
}

int Player::getPlayerCoins() const {
    return(m_numCoins);
}

int Player::getPlayerStars() const {
    return(m_numStars);
}

int Player::getWalkingDirection() const {
    return(m_walking_direction);
}

void Player::setWalkingDirection(const int walkingDirection) {
    m_walking_direction = walkingDirection;
}

void Player::doSomething() {
    if (getTicks() == 0) { //
        int action = getWorld()->getAction(getPlayerNum());
        
        switch (action) {
            case ACTION_ROLL: {
                int rand_10 = rand() % 10 + 1; // random integer 1 through 10
                setTicks(rand_10*8);
                break;
            }
            default: {
                return; // if actor does anything but move return
                break;
            }
        }
    }
    else if (getTicks() != 0) {
        
        int shouldTurn; // this is set to the value you should move in
        if (this->getX() % 16 == 0 && this->getY() % 16 == 0) { // only call check turn when on a square
            int walkingDirection = this->getWalkingDirection();
            shouldTurn = getWorld()->checkTurn(walkingDirection, this, false);
        }
        else {
            shouldTurn = this->getWalkingDirection();
        }
        
        
        if (shouldTurn == 180) { // sets direction to left if already moving left
            this->setDirection(180);
        }
        else {
            this->setDirection(0);
        }
        
        setWalkingDirection(shouldTurn);
        moveAtAngle(getWalkingDirection(), 2);
        setTicks(-1);
    }
}

Square::Square(int imageID, int startX, int startY, StudentWorld* studentWorld) : Actor(imageID, startX, startY, 0, 1, 1, studentWorld){
    
}

BlueCoinSquare::BlueCoinSquare(int startX, int startY, StudentWorld* studentWorld) : Square(2, startX, startY, studentWorld){
    
}

void BlueCoinSquare::giveCoins() {
    
}

void BlueCoinSquare::doSomething() {
    if (isInactive() == true) {
        return;
    }
    
    
}

RedCoinSquare::RedCoinSquare(int startX, int startY, StudentWorld* studentWorld) : Square(3, startX, startY, studentWorld) {
    
}

void RedCoinSquare::doSomething() {
    
}


