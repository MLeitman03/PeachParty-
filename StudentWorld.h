#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;

//class Boswer: public Game

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    Board* getBoard() {return bd;};
    ~StudentWorld();
private:
    Avatar* peach;
    Avatar* yoshi;
    std::vector<Actor*> actors;
    Board* bd;
};

#endif // STUDENTWORLD_H_
