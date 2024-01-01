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

private:
    std::list<Actor*> m_actors;
    Player* m_Peach;
    Player* m_Yoshi;
};

#endif // STUDENTWORLD_H_
