#include "Actor.h"
#include "StudentWorld.h"
#include <string>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, int direction, int depth, double size, StudentWorld* studentWorld) : GraphObject(imageID, startX, startY, direction, depth, size), m_studentWorld(studentWorld) {
    m_alive = true;
}

bool Actor::isInactive() {
    if (m_alive == false) {
        return(true);
    }
    return(false);
}

Actor::~Actor() {
    
}

StudentWorld* Actor::getWorld() {
    return(m_studentWorld);
}

bool Actor::isBoo() const {
    return(false);
}

bool Actor::isBowser() const {
    return(false);
}

bool Actor::canMoveTo() const {
    return(true);
}

bool Actor::isDirectionalSquare() const {
    return(false);
}

bool Actor::getAlive() const {
    return(m_alive);
}

void Actor::setAlive(const bool isAlive) {
    m_alive = isAlive;
}

Avatar::Avatar(int imageID, int startX, int startY, StudentWorld* studentWorld) : Actor(imageID, startX, startY, 0, 0, 1, studentWorld) {
    ticks_to_move = 0; // initialize relevant variables
    m_walking_direction = 0;
    is_new_player = true;
}

int Avatar::getTicks() const {
    return(ticks_to_move);
}

void Avatar::setTicks(const int ticks) {
    ticks_to_move = ticks_to_move + ticks;
}

int Avatar::getWalkingDirection() const {
    return(m_walking_direction);
}

void Avatar::setWalkingDirection(const int walkingDirection) {
    m_walking_direction = walkingDirection;
}

bool Avatar::canMoveTo() const {
    return(false);
}

void Avatar::shouldTurn() {
    int direction;
    if (this->getX() % 16 == 0 && this->getY() % 16 == 0) { // only call check turn when on a square
        int walkingDirection = this->getWalkingDirection();
        direction = getWorld()->checkTurn(walkingDirection, this, false);
    }
    else {
        direction = this->getWalkingDirection();
    }
    
    
    if (direction == 180) { // sets direction to left if already moving left
        this->setDirection(180);
    }
    else {
        this->setDirection(0);
    }
    
    setWalkingDirection(direction);
}



bool Avatar::getIsNewPlayer() const {
    return(is_new_player);
}

void Avatar::setIsNewPlayer(const bool isNew) {
    is_new_player = isNew;
}

Player::Player(int imageID, int startX, int startY, StudentWorld* studentWorld, int playerNum) : Avatar(imageID, startX, startY, studentWorld) {
    m_numCoins = 0;
    m_numStars = 0;
    m_playerNum = playerNum;
    m_vortexes = 0;
}


int Player::getPlayerNum() const {
    return(m_playerNum);
}

int Player::getPlayerCoins() const {
    return(m_numCoins);
}

void Player::setCoins(const int coins) {
    m_numCoins = m_numCoins + coins;
}

int Player::getPlayerStars() const {
    return(m_numStars);
}

void Player::setStars(const int stars) {
    m_numStars = m_numStars + stars;
}

int Player::getVortex() const {
    return(m_vortexes);
}

void Player::setVortex(const int numVortex) {
    m_vortexes = m_vortexes + numVortex;
}


void Player::doSomething() {
    if (getTicks() == 0) { //
        int action = getWorld()->getAction(getPlayerNum()); // getting action
        
        switch (action) {
            case ACTION_ROLL: {
                int rand_10 = rand() % 10 + 1; // random integer 1 through 10
                setTicks(rand_10*8);
                break;
            }
            case ACTION_FIRE: {
                if (this->getVortex() == 1) { // can only ever have one vortex
                    this->setVortex(-1); // reset vortex to 0
                    getWorld()->createNewVortex(this->getWalkingDirection(), this->getX(), this->getY()); // creates vortex in studentWorld
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                }
            }
            default: {
                return; // if actor does anything but move return
                break;
            }
        }
    }
    else if (getTicks() != 0) { // CHECK THIS
        
        int countOptions = 0;

        if(getWorld()->checkTurn(0, this, false) == 0) {
            countOptions = countOptions + 1;
        }
        if (getWorld()->checkTurn(90, this, false) == 90) {
            countOptions = countOptions + 1;
        }
        if (getWorld()->checkTurn(180, this, false) == 180) {
            countOptions = countOptions + 1;
        }
        if (getWorld()->checkTurn(270, this, false) == 270) {
            countOptions = countOptions + 1;
        }

        if (countOptions > 2 && getWorld()->isDirectional(this->getX(), this->getY()) == false) { // if more than 2 directions have squares then we are at a fork
            int actionFork = getWorld()->getAction(getPlayerNum());

            switch(actionFork) {
                case ACTION_LEFT: {
                    if (getWorld()->checkTurn(180, this, false) == 180) { // if it is possible to move in that direction
                        if (this->getWalkingDirection() != 0) {
                            setWalkingDirection(180);
                            break;
                        }
                        else {
                            return;
                        }
                    }
                    else {
                        return;
                    }
                }
                case ACTION_RIGHT: {
                    if (getWorld()->checkTurn(0, this, false) == 0) {
                        if (this->getWalkingDirection() != 180) {
                            setWalkingDirection(0);
                            break;
                        }
                        else {
                            return;
                        }
                    }
                    else {
                        return;
                    }
                }
                case ACTION_UP: {
                    if (getWorld()->checkTurn(90, this, false) == 90) {
                        if (this->getWalkingDirection() != 270) {
                            setWalkingDirection(90);
                            break;
                        }
                        else {
                            return;
                        }
                    }
                    else {
                        return;
                    }
                }
                case ACTION_DOWN: {
                    if (getWorld()->checkTurn(270, this, false) == 270) {
                        if (this->getWalkingDirection() != 90) {
                            setWalkingDirection(270);
                            break;
                        }
                        else {
                            return;
                        }
                    }
                    else {
                        return;
                    }
                }
                default: {
                    return;
                }
            }
        }

        shouldTurn(); // checks if corner and makes appropriate turning decision
        moveAtAngle(getWalkingDirection(), 2);
        setIsNewPlayer(true); // after player has moved off square they are reset to newPlayer
        setTicks(-1);
    }
}

Baddie::Baddie(int imageID, int startX, int startY, StudentWorld* studentWorld) : Avatar(imageID, startX, startY, studentWorld) {
    m_ticksPaused = 180;
    is_new_baddie_peach = true;
    is_new_baddie_yoshi = true;
}

void Baddie::setTicksPaused(const int ticks) {
    m_ticksPaused = m_ticksPaused + ticks;
}

int Baddie::getTicksPaused() const {
    return(m_ticksPaused);
}

void Baddie::baddieFork() {
    int countOptions = 0;

    if(getWorld()->checkTurn(0, this, false) == 0) {
        countOptions = countOptions + 1;
    }
    if (getWorld()->checkTurn(90, this, false) == 90) {
        countOptions = countOptions + 1;
    }
    if (getWorld()->checkTurn(180, this, false) == 180) {
        countOptions = countOptions + 1;
    }
    if (getWorld()->checkTurn(270, this, false) == 270) {
        countOptions = countOptions + 1;
    }

    if (countOptions > 2) {
        int direction = getWorld()->setRandomDirection(this); // if baddie is at a fork it goes in random direction
        setWalkingDirection(direction);
    }
}

bool Baddie::getIsNewBaddiePeach() const {
    return(is_new_baddie_peach);
}

bool Baddie::getIsNewBaddieYoshi() const {
    return(is_new_baddie_yoshi);
}

void Baddie::setIsNewBaddiePeach(const bool isNew) {
    is_new_baddie_peach = isNew;
}

void Baddie::setIsNewBaddieYoshi(const bool isNew) {
    is_new_baddie_yoshi = isNew;
}

Boo::Boo(int startX, int startY, StudentWorld* studentWorld) : Baddie(10, startX, startY, studentWorld) {

}

void Boo::doSomething() {
    if (getTicksPaused() != 0) { // if Boo is still
        Player* p = getWorld()->getPlayerPointer(1);
        Player* y = getWorld()->getPlayerPointer(2);
        
        if (p->getX() == this->getX() && p->getY() == this->getY() && this->getIsNewBaddiePeach() == true && p->getTicks() == 0) {
            this->setIsNewBaddiePeach(false);
            p->setIsNewPlayer(false);
            swapCoinsStars(p, y); // boo overlaps with Peach
        }
        
        if (y->getX() == this->getX() && y->getY() == this->getY() && this->getIsNewBaddieYoshi() == true && y->getTicks() == 0) {
            this->setIsNewBaddieYoshi(false);
            y->setIsNewPlayer(false);
            swapCoinsStars(y, p); // boo overlaps with Yoshi
        }
        
        setTicksPaused(-1);
        
        if (getTicksPaused() == 0) {
            int rand3 = rand() % 3 + 1;
            setTicks(rand3*8);
            int direction = getWorld()->setRandomDirection(this);
            setWalkingDirection(direction);
            this->setIsNewBaddieYoshi(true);
            this->setIsNewBaddiePeach(true);
            
        }
    }
    
    else if (this->getTicksPaused() == 0) {
        
        baddieFork(); // checks if fork
        shouldTurn(); // checks if corner
        moveAtAngle(getWalkingDirection(), 2);
        setTicks(-1);
        
        if (getTicks() == 0) {
            setTicksPaused(180);
        }
    }
}

void Boo::swapCoinsStars(Player *p, Player *y) {
    int rand2 = rand() % 2;
    bool actionPerformed = false;
    while (actionPerformed == false) { // boo has to swap something can't just do nothing
        switch(rand2) {
            case 0: {
                int tempCoins = p->getPlayerCoins();
                p->setCoins(-(p->getPlayerCoins())); // resets coins to zero
                p->setCoins(y->getPlayerCoins()); // swap coins
                y->setCoins(-(y->getPlayerCoins()));
                y->setCoins(tempCoins);
                getWorld()->playSound(SOUND_BOO_ACTIVATE);
                actionPerformed = true;
                return;
            }
            case 1: {
                if (p->getPlayerStars() > 0 || y->getPlayerStars() > 0) { // makes sure a player has stars to swap
                    int tempStars = p->getPlayerStars();
                    p->setStars(-(p->getPlayerStars())); // resets coins to zero
                    p->setStars(y->getPlayerStars()); // swap coins
                    y->setStars(-(y->getPlayerStars()));
                    y->setStars(tempStars);
                    getWorld()->playSound(SOUND_BOO_ACTIVATE);
                    actionPerformed = true;
                    return;
                }
                else {
                    break;
                }
            }
        }
        
        rand2 = 0; // players have no stars
    }
}

bool Boo::isBoo() const {
    return(true);
}

Bowser::Bowser(int startX, int startY, StudentWorld* studentWorld) : Baddie(9, startX, startY, studentWorld) {
    
}

void Bowser::doSomething() {
    if (getTicksPaused() != 0) { // if Bowser is still
        Player* p = getWorld()->getPlayerPointer(1);
        Player* y = getWorld()->getPlayerPointer(2);
        
        if (p->getX() == this->getX() && p->getY() == this->getY() && this->getIsNewBaddiePeach() == true && p->getTicks() == 0) {
            this->setIsNewBaddiePeach(false); // can't reactivate for Peach until it moves again
            p->setIsNewPlayer(false); // if bowsered Peach can't use square beneath
            destroyCoinsStars(p);
        }
        
        if (y->getX() == this->getX() && y->getY() == this->getY() && this->getIsNewBaddieYoshi() == true && y->getTicks() == 0) {
            this->setIsNewBaddieYoshi(false);
            y->setIsNewPlayer(false);
            destroyCoinsStars(y);
        }
        
        setTicksPaused(-1);
        
        if (getTicksPaused() == 0) { // moving action
            int rand10 = rand() % 10 + 1;
            setTicks(rand10*8);
            int direction = getWorld()->setRandomDirection(this);
            setWalkingDirection(direction);
            this->setIsNewBaddieYoshi(true);
            this->setIsNewBaddiePeach(true);
        }
    }
    else if (getTicks() != 0) {
        
        shouldTurn();
        moveAtAngle(getWalkingDirection(), 2);
        setIsNewPlayer(true);
        setTicks(-1);
        
        
        if (getTicks() == 0) {
            setTicksPaused(180);
        }
    }
}

void Bowser::destroyCoinsStars(Player *p) {
    int rand2 = rand() % 2;
    
    switch (rand2) { // 50% chance to destroy all coins and stars
        case 0: {
            p->setCoins(-(p->getPlayerCoins()));
            p->setStars(-(p->getPlayerStars()));
            getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
            break;
        }
        default: {
            break;
        }
    }
}

bool Bowser::isBowser() const {
    return(true);
}

Square::Square(int imageID, int startX, int startY, int direction, StudentWorld* studentWorld) : Actor(imageID, startX, startY, direction, 1, 1, studentWorld){
}

void Square::checkForBowser() { // this determines whether a dropping is dropped
    Bowser* b = getWorld()->getBowserPointer();
    if (b != nullptr) {
        if (this->getX() == b->getX() && this->getY() == b->getY() && b->getTicks() == 0 && b->getIsNewPlayer() == true) {
            b->setIsNewPlayer(false);
            int rand4 = rand() % 4;
            switch(rand4) {
                case 3: { // 25% chance of dropping
                    getWorld()->changeSquare(this->getX(), this->getY()); // this creates a dropping square on site of previous square
                    setAlive(false); // changes square to inactive
                    getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
                    return;
                }
                default:
                    return;
            }
        }
    }

    return;
}

Square::~Square() {
    
}

BlueCoinSquare::BlueCoinSquare(int startX, int startY, StudentWorld* studentWorld) : Square(2, startX, startY, 0, studentWorld){
    
}
BlueCoinSquare::~BlueCoinSquare() {
    
}

void BlueCoinSquare::doSomething() {
    checkForBowser();
    if (isInactive() == true) {
        return;
    }

    Player* p = getWorld()->getPlayerPointer(1);
    Player* y = getWorld()->getPlayerPointer(2);

    addCoins(p);
    addCoins(y);

}

void BlueCoinSquare::addCoins(Player* p) {
    if (p->getX() == this->getX() && p->getY() == this->getY()) { // makes sure x and y coords are correct
        if (p->getIsNewPlayer() == true && p->getTicks() == 0) { // makes sure player is still and new
            p->setCoins(3); // simply adds three coins
            p->setIsNewPlayer(false);
            this->getWorld()->playSound(SOUND_GIVE_COIN);
        }
    }
}

RedCoinSquare::RedCoinSquare(int startX, int startY, StudentWorld* studentWorld) : Square(3, startX, startY, 0, studentWorld) {
    
}

RedCoinSquare::~RedCoinSquare() {
    
}

void RedCoinSquare::doSomething() {
    checkForBowser();
    if (isInactive() == true) {
        return;
    }

    Player* p = getWorld()->getPlayerPointer(1);
    Player* y = getWorld()->getPlayerPointer(2);

    deductCoins(p);
    deductCoins(y);
}

void RedCoinSquare::deductCoins(Player* p) {
    if (p->getX() == this->getX() && p->getY() == this->getY()) {
        if (p->getIsNewPlayer() == true && p->getTicks() == 0) {
            if (p->getPlayerCoins() >= 3) { // if player has 3 or more coins
                p->setCoins(-3);
            }
            else { // if player has less than three coins
                p->setCoins(-(p->getPlayerCoins())); // sets coins to zero
            }
            p->setIsNewPlayer(false);
            this->getWorld()->playSound(SOUND_TAKE_COIN); // plays deduction sound
        }
    }
}

StarSquare::StarSquare(int startX, int startY, StudentWorld* studentWorld) : Square(7, startX, startY, 0, studentWorld) {
    
}

StarSquare::~StarSquare() {
    
}

void StarSquare::doSomething() {
    checkForBowser();
    if (isInactive() == true) {
        return;
    }

    Player* p = getWorld()->getPlayerPointer(1);
    Player* y = getWorld()->getPlayerPointer(2);

    giveStars(p);
    giveStars(y);
}

void StarSquare::giveStars(Player* p) {
    if (p->getX() == this->getX() && p->getY() == this->getY() && p->getIsNewPlayer() == true) {
        if (p->getPlayerCoins() < 20) { // can't but star with less than 20 coins
            p->setIsNewPlayer(false);
            return;
        }
        else {
            p->setCoins(-20);
            p->setStars(1);
            p->setIsNewPlayer(false);
            getWorld()->playSound(SOUND_GIVE_STAR);
        }
    }
}

DirectionalSquare::DirectionalSquare(int imageID, int startX, int startY, int direction, StudentWorld* studentWorld) : Square(imageID, startX, startY, direction, studentWorld) {
    m_direction = direction;
}

DirectionalSquare::~DirectionalSquare() {
    
}

void DirectionalSquare::doSomething() { // only relevant to players

    checkForBowser();
    if (isInactive() == true) {
        return;
    }

    Player* p = getWorld()->getPlayerPointer(1);
    Player* y = getWorld()->getPlayerPointer(2);

    changeDirection(p);
    changeDirection(y);
}

int DirectionalSquare::getDirection() {
    return(m_direction);
}

void DirectionalSquare::changeDirection(Player *p) {
    if (p->getX() == this->getX() && p->getY() == this->getY()) {
        p->setWalkingDirection(this->getDirection()); // directional square is made with direction that player's walking direction is set to
    }
}

bool DirectionalSquare::isDirectionalSquare() const {
    return(true);
}

BankSquare::BankSquare(int startX, int startY, StudentWorld* studentWorld) : Square(6, startX, startY, 0, studentWorld) {
    
}

BankSquare::~BankSquare() {
    
}

void BankSquare::doSomething() {
    
    checkForBowser();
    if (isInactive() == true) {
        return;
    }

    Player* p = getWorld()->getPlayerPointer(1);
    Player* y = getWorld()->getPlayerPointer(2);

    bankCoins(p);
    bankCoins(y);
}

void BankSquare::bankCoins(Player* p) {
    
    if (p->getX() == this->getX() && p->getY() == this->getY() && p->getTicks() != 0 && p->getIsNewPlayer() == true) {
        if (p->getPlayerCoins() >= 5) { // player deposits five coins if they have more than or equal to 5 coins
            getWorld()->setBankBalance(5);
            p->setCoins(-5);
        }
        else { // otherwise deposit as much coins as possible
            getWorld()->setBankBalance(p->getPlayerCoins());
            p->setCoins(-(p->getPlayerCoins()));
        }
        getWorld()->playSound(SOUND_DEPOSIT_BANK);
    }
    else if (p->getX() == this->getX() && p->getY() == this->getY() && p->getTicks() == 0 && p->getIsNewPlayer() == true) {
        p->setCoins(getWorld()->getBankBalance()); // adds bankBalance to player coins
        getWorld()->setBankBalance(-(getWorld()->getBankBalance())); // sets BankBalance to zero
        p->setIsNewPlayer(false); // makes sure they don't pay on their way out
        getWorld()->playSound(SOUND_WITHDRAW_BANK);
    }
}

EventSquare::EventSquare(int startX, int startY, StudentWorld* studentWorld) : Square(5, startX, startY, 0, studentWorld) {
    
}

EventSquare::~EventSquare() {
    
}

void EventSquare::doSomething() {
    
    checkForBowser();
    if (isInactive() == true) {
        return;
    }

    Player* p = getWorld()->getPlayerPointer(1);
    Player* y = getWorld()->getPlayerPointer(2);

    doEvent(p, y);
    doEvent(y, p);
}

void EventSquare::doEvent(Player* p, Player* y) {
    
    if (p->getX() == this->getX() && p->getY() == this->getY() && p->getTicks() == 0 && p->getIsNewPlayer() == true) {
        int randInt = rand() % 3;
        bool action_performed = false;

        while (action_performed == false) { // forces an event to happen

            switch(randInt) {
                case 0: {
                    int xCord, yCord;
                    getWorld()->Teleport(xCord, yCord);
                    p->moveTo(xCord, yCord);
                    p->setIsNewPlayer(false); // I think I need this
                    getWorld()->playSound(SOUND_PLAYER_TELEPORT);
                    action_performed = true;
                    break;
                }
                case 1: {
                    int temp_x = p->getX();
                    int temp_y = p->getY();
                    int temp_walkingDirection = p->getWalkingDirection();
                    int temp_direction = p->getDirection();

                    p->moveTo(y->getX(), y->getY());
                    p->setTicks(y->getTicks());
                    p->setWalkingDirection(y->getWalkingDirection());
                    p->setDirection(y->getDirection());

                    y->moveTo(temp_x, temp_y);
                    y->setWalkingDirection(temp_walkingDirection);
                    y->setDirection(temp_direction);
                    y->setTicks(-(y->getTicks())); // setting other player's ticks to zero
                    y->setIsNewPlayer(false); // makes sure that the event square isn't immediately called on the other player again; CHECK IF THIS IMPLEMENTATION IS CORRECT
                    getWorld()->playSound(SOUND_PLAYER_TELEPORT);
                    action_performed = true;
                    break;
                }
                case 2: {
                    if (p->getVortex() < 1) { // can only have one vortex at a time I guess
                        p->setVortex(1);

                        p->setIsNewPlayer(false);
                        getWorld()->playSound(SOUND_GIVE_VORTEX);
                        action_performed = true;
                        break;
                    }
                    else {
                        randInt = rand() % 2; // only called if player already has vortex
                    }
                }
            }
        }
    }
}

DroppingSquare::DroppingSquare(int startX, int startY, StudentWorld* studentWorld) : Square(8, startX, startY, 0, studentWorld) {
    
}

DroppingSquare::~DroppingSquare() {
    
}

void DroppingSquare::doSomething() {

    if (isInactive() == true) {
        return;
    }

    Player* p = getWorld()->getPlayerPointer(1);
    Player* y = getWorld()->getPlayerPointer(2);

    dropCoins(p);
    dropCoins(y);
}

void DroppingSquare::dropCoins(Player* p) {
    if (p->getX() == this->getX() && p->getY() == this->getY() && p->getTicks() == 0 && p->getIsNewPlayer() == true) {
        p->setIsNewPlayer(false);
        int randInt = rand() % 2;
        bool actionPerformed = false;
        while (actionPerformed == false) { // randomized to remove coins or star
            switch(randInt) {
                case 0: {
                    if (p->getPlayerCoins() >= 10) {
                        p->setCoins(-10);
                    }
                    else {
                        p->setCoins(-(p->getPlayerCoins()));
                    }
                    getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
                    actionPerformed = true;
                    return;
                }
                case 1: {
                    if (p->getPlayerStars() >= 1) {
                        p->setStars(-1);
                        getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
                        actionPerformed = true;
                        return;
                    }
                    
                    break;
                }
            }
            randInt = 0; // if player has no stars
        }
    }
}

Vortex::Vortex(int startX, int startY, StudentWorld* studentWorld, int vortexDirection) : Actor(11, startX, startY, 0, 0, 1, studentWorld) {
    m_vortexDirection = vortexDirection;

}

void Vortex::doSomething() {
    if (isInactive() == true) {
        return;
    }
    
    if (this->getX() < 0 || this->getX() > VIEW_WIDTH || this->getY() < 0 || this->getY() > VIEW_HEIGHT) {
        this->setAlive(false);
        return;
    }
    
    Baddie* b = getWorld()->checkBaddieVortexOverlap(this->getX(), this->getY()); // gets baddie pointer for overlap
    
    if (b != nullptr) { // don't check if there are no baddies
        int xCord, yCord;
        b->getWorld()->Teleport(xCord, yCord);
        b->moveTo(xCord, yCord);
        b->setTicks(-(b->getTicks()));
        b->setTicksPaused(-(b->getTicksPaused())); // sets baddie to paused state after teleport
        b->setTicksPaused(180);
        b->setWalkingDirection(0); // starts walking right and facing right
        b->setDirection(0);
        b->setIsNewPlayer(true);
        b->setIsNewBaddiePeach(true);
        b->setIsNewBaddieYoshi(true);
        this->setAlive(false);
        getWorld()->playSound(SOUND_HIT_BY_VORTEX);
        return;
    }
    
    moveAtAngle(getVortexDirection(), 2);
    
}

bool Vortex::canMoveTo() const {
    return(false);
}

int Vortex::getVortexDirection() const {
    return(m_vortexDirection);
}

void Vortex::setVortexDirection(const int direction) {
    
}

Vortex::~Vortex() {
    
}
