#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject {
public:
    virtual void doSomething() = 0;
    Actor(int imageID, int startX, int startY, int direction, int depth, double size, StudentWorld* studentWorld);
    virtual ~Actor();
    bool isInactive();
    StudentWorld* getWorld();
    virtual bool isBowser() const;
    virtual bool isBoo() const;
    virtual bool canMoveTo() const; // a function made so that nothing is randomly teleported to a vortex
    virtual bool isDirectionalSquare() const;
    bool getAlive() const;
    void setAlive(const bool isAlive);
    
private:
    StudentWorld* m_studentWorld;
    bool m_alive;
};

class Avatar : public Actor {
public:
    Avatar(int imageID, int startX, int startY, StudentWorld* studenWorld);
    int getTicks() const;
    void setTicks(const int ticks);
    int getWalkingDirection() const;
    void setWalkingDirection(const int walkingDirection);
    virtual bool canMoveTo() const;
    void shouldTurn();
    void setRandomDirection(int& direction, int xCord, int yCord);
    bool getIsNewPlayer() const;
    void setIsNewPlayer(const bool isNew);
    
    
private:
    int ticks_to_move;
    int m_walking_direction;
    bool is_new_player;
};

class Player : public Avatar {
public:
    Player(int imageID, int startX, int startY, StudentWorld* studentWorld, int playerNum);
    virtual void doSomething();
    int getPlayerCoins() const;
    int getPlayerStars() const;
    int getPlayerNum() const;
    void setCoins(const int coins);
    void setStars(const int stars);
    int getVortex() const;
    void setVortex(const int numVortex);
private:
    int m_numCoins;
    int m_numStars;
    int m_playerNum;
    int m_vortexes;
};



class Baddie : public Avatar {
public:
    Baddie(int imageID, int startX, int startY, StudentWorld* studentWorld);
    int getTicksPaused() const;
    void setTicksPaused(const int ticks);
    void baddieFork();
    bool getIsNewBaddiePeach() const;
    void setIsNewBaddiePeach(const bool isNew);
    bool getIsNewBaddieYoshi() const;
    void setIsNewBaddieYoshi(const bool isNew);
private:
    int m_ticksPaused;
    bool is_new_baddie_peach;
    bool is_new_baddie_yoshi;
};

class Bowser : public Baddie {
public:
    virtual void doSomething();
    Bowser(int startX, int startY, StudentWorld* studentWorld);
    virtual bool isBowser() const;
    void destroyCoinsStars(Player* p);
private:
};

class Boo : public Baddie {
public:
    virtual void doSomething();
    Boo(int startX, int startY, StudentWorld* studentWorld);
    virtual bool isBoo() const;
    void swapCoinsStars(Player* p, Player* y);
private:
    
};


class Square : public Actor {
public:
    Square(int imageID, int startX, int startY, int direction, StudentWorld* studentWorld);
    virtual ~Square();
    void checkForBowser();
private:
};

class BlueCoinSquare : public Square {
public:
    BlueCoinSquare(int startX, int startY, StudentWorld* studentWorld);
    virtual ~BlueCoinSquare();
    virtual void doSomething();
    void addCoins(Player* p);
    
private:
};

class RedCoinSquare : public Square {
public:
    
    RedCoinSquare(int startX, int startY, StudentWorld* studentWorld);
    virtual ~RedCoinSquare();
    virtual void doSomething();
    void deductCoins(Player* p);
    
private:
};

class StarSquare : public Square {
public:
    virtual void doSomething();
    virtual ~StarSquare();
    StarSquare(int startX, int startY, StudentWorld* studentWorld);
    void giveStars(Player* p);
};

class DirectionalSquare : public Square {
public:
    virtual void doSomething();
    DirectionalSquare(int imageID, int startX, int startY, int direction, StudentWorld* studentWorld);
    virtual ~DirectionalSquare();
    int getDirection();
    void changeDirection(Player* p);
    virtual bool isDirectionalSquare() const;
    
private:
    int m_direction;
};

class BankSquare : public Square {
public:
    virtual void doSomething();
    BankSquare(int startX, int startY, StudentWorld* studentWorld);
    virtual ~BankSquare();
    void bankCoins(Player* p);
};

class EventSquare : public Square {
public:
    virtual void doSomething();
    EventSquare(int startX, int startY, StudentWorld* studentWorld);
    virtual ~EventSquare();
    void doEvent(Player* p, Player* y);
};

class DroppingSquare : public Square {
public:
    virtual void doSomething();
    DroppingSquare(int startX, int startY, StudentWorld* studentWorld);
    virtual ~DroppingSquare();
    void dropCoins(Player* p);
};

class Vortex : public Actor {
public:
    virtual void doSomething();
    virtual bool canMoveTo() const;
    void setVortexDirection(const int direction);
    int getVortexDirection() const;
    Vortex(int startX, int startY, StudentWorld* studentWorld, int vortexDirection);
    virtual ~Vortex();
    
private:
    int m_vortexDirection;
};



#endif // ACTOR_H_
