#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size) : GraphObject(imageID, startX, startY, dir, depth, size),   m_world(world), ticks_to_move(0),  movement_dir(right), bank_amount(0) {};
    virtual ~Actor() {};
    virtual void doSomething() = 0;
    StudentWorld* getWorld()  {return m_world;};
    void setTicks(int ticks);
    int getTicks() {return ticks_to_move;};
    bool canWalk(int x, int y, int dir);
    void changeDirection();
    bool getStatus() {return isActive;};
    int getAngle() {return movement_dir;};
    void setAngle(int dir) {movement_dir = dir;};
    int getBank() {return bank_amount;};
    //virtual void alterBank() = 0;
private:
    StudentWorld* m_world;
    int ticks_to_move;
    bool isActive;
    int movement_dir;
    int bank_amount;
};

class Avatar : public Actor
{
public:
    Avatar(StudentWorld* world, int imageID, int startX, int startY, int pnum) :
    Actor(world, imageID, startX, startY, 0, 0, 1.0), m_pnum(pnum), isWalking(false), m_coins(0), m_stars(0), m_rolls(0), pixels_moved(0) {};
    virtual  ~Avatar() {};
    void doSomething();
    virtual int getPnum() {return m_pnum;};
    bool getWalking() {return isWalking;};
    int getCoins() {return m_coins;};
    void addCoins(int n) {m_coins = m_coins+n;};
    int getStars() {return m_stars;};
    void addStars(int n) {m_stars = m_stars+n;};
    int getRolls(){return m_rolls;};
    //void alterBank();
private:
    bool isWalking; //true if walking, false if waiting
    int m_pnum;
    int m_coins;
    int m_stars;
    int m_rolls;
    int pixels_moved;
};


class Baddies : public Actor
{
    
};

class Square : public Actor
{
public:
    Square(StudentWorld* world, int imageID, int startX, int startY) :
    Actor(world, imageID, startX, startY, right, 1, 1.0) {};
    virtual void doSomething() = 0;
    //void alterBank() = 0;
    virtual ~Square() {};

private:
};

class CoinSquare : public Square
{
public:
    CoinSquare(StudentWorld* world, int imageID, int startX, int startY, bool isBlueSquare = false)
    :Square(world, imageID, startX, startY), isBlue(isBlueSquare),
    alive(true) {};
    
    ~CoinSquare() {};
    
    void doSomething();
    //void alterBank() = 0;
    
    virtual void die() {alive = false; return;}
    
    bool isAlive() {return alive;}
private:
    bool alive;
    bool isBlue;
};

/*
class Projectile : public Actor
{
    
};
 
 class ...

*/
#endif // ACTOR_H_
