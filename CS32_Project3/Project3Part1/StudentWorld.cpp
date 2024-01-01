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
                         //m_Yoshi = new Player(1, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this, 2);
                         BlueCoinSquare* b = new BlueCoinSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b);
                         break;
                     }
                     case Board::blue_coin_square: {
                         BlueCoinSquare* b = new BlueCoinSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b);
                         break;
                     }
                     /*case Board::red_coin_square: {
                         break;
                     }
                     case Board::left_dir_square: {
                         break;
                         
                     }
                     case Board::right_dir_square: {
                         break;
                     }
                     case Board::up_dir_square: {
                         break;
                     }
                     case Board::down_dir_square: {
                         break;
                     }
                     case Board::event_square: {
                         break;
                     }
                     case Board::bank_square: {
                         break;
                     }
                     case Board::star_square: {
                         break;
                     }
                     case Board::bowser: {
                         break;
                     }
                     case Board::boo: {
                         break;
                     }*/
                     default: {
                         BlueCoinSquare* b = new BlueCoinSquare(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, this);
                         m_actors.push_back(b);
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

    setGameStatText("Game will end in a few seconds");
    m_Peach->doSomething();
    
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) {
        (*p)->doSomething();
    }
    /*
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) {
        if ((*p)->isInactive() == true) {
            delete (*p);
        }
    } */
    
    if (timeRemaining() <= 0) {
        return GWSTATUS_NOT_IMPLEMENTED;
    }
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_Peach;
    m_Peach = nullptr;
    //delete m_Yoshi;
   
    //m_Yoshi = nullptr;
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) {
        delete *p;
    }
    m_actors.clear();
    
}


int StudentWorld::checkTurn(int walkingDirection, Actor* p, bool haveChecked) {
    
        
        switch(walkingDirection) {
            case 0: { // Right
                for (list<Actor*>::iterator k = m_actors.begin(); k!= m_actors.end(); k++) {
                    if ((*k)->getX() == p->getX() + 16 && (*k)->getY() == p->getY()) {
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
                    if ((*k)->getY() == p->getY() + 16 && (*k)->getX() == p->getX()) {
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
                    if ((*k)->getX() == p->getX() - 16 && (*k)->getY() == p->getY()) {
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
                    if ((*k)->getY() == p->getY() - 16 && (*k)->getX() == p->getX()) {
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

StudentWorld::~StudentWorld() {
    cleanUp();
}
