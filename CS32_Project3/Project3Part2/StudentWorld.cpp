#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_balance = 0;
}

int StudentWorld::init()
{
    startCountdownTimer(99);
    

     Board bd;
     string board_file = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt";
     Board::LoadResult result = bd.loadBoard(board_file);
     if (result == Board::load_fail_file_not_found)
     cerr << "Could not find board01.txt data file\n";
     else if (result == Board::load_fail_bad_format)
     cerr << "Your board was improperly formatted\n";
     else if (result == Board::load_success) {
         cerr << "Successfully loaded board\n";
         for (int i = 0; i < 16; i++) {
             for (int j = 0; j < 16; j++) {
                 Board::GridEntry ge = bd.getContentsOf(i, j);
                 
                 switch(ge) {
                     case Board::empty: {
                         break;
                     }
                     case Board::player: {
                         m_Peach = new Player(0, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this, 1);
                         m_Yoshi = new Player(1, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this, 2);
                         BlueCoinSquare* b = new BlueCoinSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b);
                         break;
                     }
                     case Board::blue_coin_square: {
                         BlueCoinSquare* b = new BlueCoinSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b);
                         break;
                     }
                     case Board::red_coin_square: {
                         RedCoinSquare* r = new RedCoinSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(r);
                         break;
                     }
                     case Board::left_dir_square: {
                         DirectionalSquare* d = new DirectionalSquare(4, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, 180, this);
                         m_actors.push_back(d);
                         break;
                         
                     }
                     case Board::right_dir_square: {
                         DirectionalSquare* d = new DirectionalSquare(4, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, 0, this);
                         m_actors.push_back(d);
                         break;
                     }
                     case Board::up_dir_square: {
                         DirectionalSquare* d = new DirectionalSquare(4, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, 90, this);
                         m_actors.push_back(d);
                         break;
                     }
                     case Board::down_dir_square: {
                         DirectionalSquare* d = new DirectionalSquare(4, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, 270, this);
                         m_actors.push_back(d);
                         break;
                     }
                     case Board::event_square: {
                         EventSquare* e = new EventSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(e);
                         break;
                     }
                     case Board::bank_square: {
                         BankSquare* b = new BankSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b);
                         break;
                     }
                     case Board::star_square: {
                         StarSquare* s = new StarSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(s);
                         break;
                     }
                     case Board::bowser: {
                         Bowser* b = new Bowser(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b);
                         BlueCoinSquare* b_1 = new BlueCoinSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b_1);
                         break;
                     }
                     case Board::boo: {
                         Boo* b = new Boo(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b);
                         BlueCoinSquare* b_1 = new BlueCoinSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b_1);
                         break;
                     }
                     default: { // should never really be called
                         break;
                     }
                 }
                 
             }
         }
     }
        
         
      // this placeholder causes timeout after 5 seconds
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.
    string vortexPeach = "";
    string vortexYoshi = "";
    
    if (m_Peach->getVortex() == 1) { // if they have a vortex set text to vortex
        vortexPeach = "Vor";
    }
    if (m_Yoshi->getVortex() == 1) {
        vortexYoshi = "Vor";
    }

    setGameStatText("P1 Roll: " + to_string(m_Peach->getTicks()/8) + " Stars: " + to_string(m_Peach->getPlayerStars()) + " $$: " + to_string(m_Peach->getPlayerCoins()) + " " + vortexPeach + " | Time: " + to_string(timeRemaining()) + " | Bank: " + to_string(getBankBalance()) + " | P2 Roll: " + to_string(m_Yoshi->getTicks()/8) + " Stars: " + to_string(m_Yoshi->getPlayerStars()) + " $$: " + to_string(m_Yoshi->getPlayerCoins()) + " " + vortexYoshi);
    
    m_Peach->doSomething();
    m_Yoshi->doSomething();
    
    
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) { // all squares go first
        if ((*p)->isBoo() == false && (*p)->isBowser() == false) {
            (*p)->doSomething();
        }
    }
    
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) { // Boos go second
        if ((*p)->isBoo()) {
            (*p)->doSomething();
        }
    }
    
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) { // then Bowser
        if ((*p)->isBowser()) {
            (*p)->doSomething();
        }
    }
    
    list<Actor*>::iterator k = m_actors.begin();
    while (k != m_actors.end()) {
        if ((*k)->isInactive() == true) {
            delete(*k);
            k = m_actors.erase(k);
            continue;
        }
        k++;
    }
    
    if (timeRemaining() <= 0) {
        this->playSound(SOUND_GAME_FINISHED);
        if (m_Peach->getPlayerStars() > m_Yoshi->getPlayerStars()) {
            this->setFinalScore(m_Peach->getPlayerStars(), m_Peach->getPlayerCoins());
            return(GWSTATUS_PEACH_WON);
        }
        else if (m_Yoshi->getPlayerStars() > m_Peach->getPlayerStars()) {
            this->setFinalScore(m_Yoshi->getPlayerStars(), m_Yoshi->getPlayerCoins());
            return(GWSTATUS_YOSHI_WON);
        }
        else if (m_Peach->getPlayerCoins() > m_Yoshi->getPlayerCoins()) {
            this->setFinalScore(m_Peach->getPlayerStars(), m_Peach->getPlayerCoins());
            return(GWSTATUS_PEACH_WON);
        }
        else if (m_Yoshi->getPlayerCoins() > m_Peach->getPlayerCoins()) {
            this->setFinalScore(m_Yoshi->getPlayerStars(), m_Yoshi->getPlayerCoins());
            return(GWSTATUS_YOSHI_WON);
        }
        
        int rand2 = rand() % 2;
        
        switch(rand2) { // random winner if all stats are tied
            case 0: {
                this->setFinalScore(m_Peach->getPlayerStars(), m_Peach->getPlayerCoins());
                return(GWSTATUS_PEACH_WON);
            }
            case 1: {
                this->setFinalScore(m_Yoshi->getPlayerStars(), m_Yoshi->getPlayerCoins());
                return(GWSTATUS_YOSHI_WON);
            }
        }
        
    }
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_Peach;
    m_Peach = nullptr;
    delete m_Yoshi;
    m_Yoshi = nullptr;
    
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) {
        Actor* temp = *p;
        delete temp;
    }
    m_actors.clear();
    
}


int StudentWorld::checkTurn(int walkingDirection, Actor* p, bool haveChecked) {
    
        
        switch(walkingDirection) {
            case 0: { // Right
                for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
                    if ((*k)->getX() == p->getX() + 16 && (*k)->getY() == p->getY() && (*k)->canMoveTo() == true) {
                        return(walkingDirection); // don't turn
                    }
                }
               
                if (haveChecked){
                    return 90;
                }
                else{
                    if (checkTurn(90, p, true) == 90) { // prefer up over down
                        return(90);
                    }
                    else {
                        return(270);
                    }
                }
                
            }
            case 90: { // Up
                for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
                    if ((*k)->getY() == p->getY() + 16 && (*k)->getX() == p->getX() && (*k)->canMoveTo() == true) {
                        return(walkingDirection); // don't turn
                    }
                }
                
                if (haveChecked){
                    return 0;
                }
                
                if (checkTurn(0, p, true) == 0) { // prefer right over left
                    return(0);
                }
                else {
                    return(180);
                }
            }
            case 180: { // Left
                for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
                    if ((*k)->getX() == p->getX() - 16 && (*k)->getY() == p->getY() && (*k)->canMoveTo() == true) {
                        return(walkingDirection); // don't turn
                    }
                }
               
                if (haveChecked){
                    return 0;
                }
                
                if (checkTurn(90, p, true) == 90) { // prefer up over down
                    return(90);
                }
                else {
                    return(270);
                }
            }
            case 270: { // Down
                for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
                    if ((*k)->getY() == p->getY() - 16 && (*k)->getX() == p->getX() && (*k)->canMoveTo() == true) {
                        return(walkingDirection); // don't turn
                    }
                }
                
                if (haveChecked){
                    return 0;
                }
                
                if (checkTurn(0, p, true) == 0) { // prefer right over left
                    return(0);
                }
                else {
                    return(180);
                }
            }
        }
    
    return(walkingDirection); // should never actually be called
}

Player* StudentWorld::getPlayerPointer(int playerNum) { // returns player pointer
    if (playerNum == 1) {
        return(m_Peach);
    }
    if (playerNum == 2) {
        return(m_Yoshi);
    }
    
    return(nullptr); // should never be called
}

Boo* StudentWorld::getBooPointer() {
    for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
        if ((*k)->isBoo() == true) {
            Boo* b = dynamic_cast<Boo*>(*k);
            return(b);
        }
    }
    
    return(nullptr); // should never be called
}

Bowser* StudentWorld::getBowserPointer() {
    for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
        if ((*k)->isBowser() == true) {
            Bowser* b = dynamic_cast<Bowser*>(*k);
            return(b);
        }
    }
    
    return(nullptr); // should never be called
}

void StudentWorld::Teleport(int& xCord, int& yCord) { // changes inputs
    bool isValid = false;
    
    while (isValid == false) {
        int xRandInt = rand() % 16; // produces number from 0-15 so exactly what we want
        int yRandInt = rand() % 16;
        xCord = xRandInt * SPRITE_WIDTH; // resetting inputted values
        yCord = yRandInt * SPRITE_HEIGHT;
        
        for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
            if ((*k)->getX() == xCord && (*k)->getY() == yCord && (*k)->canMoveTo() == true) { // if there exists a valid object at the x and y Cord then return
                isValid = true;
                return;
            }
        }
    }
}

int StudentWorld::getBankBalance() const {
    return(m_balance);
}

void StudentWorld::setBankBalance(const int amount) {
    m_balance = m_balance + amount;
}

void StudentWorld::changeSquare(int xCord, int yCord) {
    for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
        if ((*k)->getX() == xCord && (*k)->getY() == yCord && (*k)->canMoveTo() == true) {
            DroppingSquare* d = new DroppingSquare(xCord, yCord, this); // creates new square
            m_actors.push_back(d);
            return;
        }
    }
}

bool StudentWorld::isDirectional(const int xCord, const int yCord) { // directional squares aren't forks
    for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
        if ((*k)->getX() == xCord && (*k)->getY() == yCord && (*k)->isDirectionalSquare() == true) {
            return(true);
        }
    }
    
    return(false);
}

Baddie* StudentWorld::checkBaddieVortexOverlap(int xCord, int yCord) {
    for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
        if ((*k)->getX() < xCord + 16 && (*k)->getY() < yCord + 16 && (*k)->getX() > xCord - 1 && (*k)->getY() > yCord - 1) { // this gets proper overlap between vortex and Baddie
            if ((*k)->isBowser() == true || (*k)->isBoo() == true) {
                Baddie* b = dynamic_cast<Baddie*>(*k); // changes to baddie pointer for vortex
                return(b);
            }
        }
    }
    
    return(nullptr);
}

void StudentWorld::createNewVortex(const int direction, const int xCord, const int yCord) {
    switch(direction) { // creates new vortex in correct direction in square in front of player
        case 0: {
            Vortex* v = new Vortex(xCord + 16, yCord, this, direction);
            m_actors.push_back(v);
            break;
        }
        case 90: {
            Vortex* v = new Vortex(xCord, yCord + 16, this, direction);
            m_actors.push_back(v);
            break;
        }
        case 180 : {
            Vortex* v = new Vortex(xCord - 16, yCord, this, direction);
            m_actors.push_back(v);
            break;
        }
        case 270: {
            Vortex* v = new Vortex(xCord, yCord - 16, this, direction);
            m_actors.push_back(v);
            break;
        }
    }
}

int StudentWorld::setRandomDirection(Actor *b) { // gives random valid direction
    int rand4 = randInt(0, 3);
    bool validDirection = false;
    
    while (validDirection == false) {
        if (rand4 == 0) {
            if (checkTurn(0, b, false) == 0) {
                validDirection = true;
                return(0);
            }
        }
        else if (rand4 == 1) {
            if (checkTurn(90, b, false) == 90) {
                validDirection = true;
                return(90);
            }
            
        }
        else if (rand4 == 2) {
            if (checkTurn(180, b, false) == 180) {
                validDirection = true;
                return(180);
            }
            
        }
        else if (rand4 == 3) {
            if (checkTurn(270, b, false) == 270) {
                validDirection = true;
                return(270);
            }
        }
        
        rand4 = randInt(0, 3);
    }
    
    return(0); // should never be called
}

StudentWorld::~StudentWorld() {
    cleanUp();
}
