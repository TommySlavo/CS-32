#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject {
public:
    virtual void doSomething() = 0;
    Actor(int imageID, int startX, int startY, int direction, int depth, double size, StudentWorld* studentWorld);
    virtual ~Actor();
    virtual bool isInactive();
    StudentWorld* getWorld();
    
private:
    StudentWorld* m_studentWorld;
};

class Player : public Actor {
public:
    Player(int imageID, int startX, int startY, StudentWorld* studentWorld, int playerNum);
    virtual void doSomething();
    int getPlayerCoins() const;
    int getPlayerStars() const;
    int getPlayerNum() const;
    int getTicks() const;
    int getWalkingDirection() const;
    void setWalkingDirection(const int walkingDirection);
    //void setCoins(int coins);
    //void setStars(int stars);
    void setTicks(int ticks);
private:
    int m_walking_direction;
    int m_numCoins;
    int m_numStars;
    int m_playerNum;
    int ticks_to_move;
};

/*

class Baddie : public Actor {
public:
    
private:
    
};*/

class Bowser : public Actor {
public:
    
private:
};

class Boo : public Actor {
public:
    
private:
    
};


class Square : public Actor {
public:
    Square(int imageID, int startX, int startY, StudentWorld* studentWorld);
    //virtual void doSomething() = 0;
    //virtual ~Square();
    
private:
    bool is_active;
};

class CoinSquare : public Square {
    CoinSquare(int imageID, int startX, int startY, StudentWorld* studentWorld);
};


class BlueCoinSquare : public Square {
public:
    BlueCoinSquare(int startX, int startY, StudentWorld* studentWorld);
    virtual void doSomething();
    void giveCoins();
    
private:
};

class RedCoinSquare : public Square {
public:
    RedCoinSquare(int startX, int startY, StudentWorld* studentWorld);
    virtual void doSomething();
    //virtual void deductCoins();
    
private:
};

class StarSquare : public Square {
    
};

class DirectionalSquare : public Square {
    
};

class BankSquare : public Square {
    
};

class EventSquare : public Square {
    
};

class DroppingSquare : public Square {
    virtual void deductCoins();
};

class Vortex : public Actor {
public:
    
private:
};



#endif // ACTOR_H_
