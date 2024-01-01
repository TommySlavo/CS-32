#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <vector>
#include <list>
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    ~StudentWorld();
    int checkTurn(int walkingDirection, Actor* p, bool haveChecked);
    Player* getPlayerPointer(int playerNum);
    int getBankBalance() const;
    void setBankBalance(const int amount);
    bool isDirectional(const int xCord, const int yCord);
    
    void Teleport(int& xCord, int& yCord);
    void changeSquare(int xCord, int yCord);
    
    Baddie* checkBaddieVortexOverlap(int xCord, int yCord);
    
    void createNewVortex(const int direction, const int xCord, const int yCord);
    
    int setRandomDirection(Actor* b);
    
    
    Boo* getBooPointer();
    Bowser* getBowserPointer();

private:
    std::list<Actor*> m_actors;
    Player* m_Peach;
    Player* m_Yoshi;
    int m_balance;
};

#endif // STUDENTWORLD_H_
