#include "Actor.h"
#include "StudentWorld.h"
#include "GameController.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

bool Actor::canWalk(int x,int y, int dir)
{
    x= x/16;
    y= y/16;

   // if (x<0 || x >= (BOARD_WIDTH-1) || y < 0 || y >= (BOARD_HEIGHT-1))
   //     return false;
    
    if (dir == right)
    {
        if (getWorld()->getBoard()->getContentsOf(x+1, y) == Board::empty)
            return false;
    }
    
    else if (dir == left)
    {
        if (getWorld()->getBoard()->getContentsOf(x-1, y) == Board::empty)
            return false;
    }
    
    else if (dir == up)
    {
        if (getWorld()->getBoard()->getContentsOf(x, y+1) == Board::empty)
            return false;
    }
    
    else if (dir == down)
    {
        if (getWorld()->getBoard()->getContentsOf(x, y-1) == Board::empty)
            return false;
    }
    
    return true;
    
}

void Actor::changeDirection()
{

    if (movement_dir == right || movement_dir == left)
    {
        if (canWalk(getX(), getY(),up))
        {
            setDirection(right);
            movement_dir = up;
            moveAtAngle(up,2);
            //pixels_moved+=2;
        }
        else
        {
            movement_dir = down;
            setDirection(right);
            moveAtAngle(down,2);
            //pixels_moved+=2;
        }
    }
    else
    {
        if (canWalk(getX(), getY(), right))
        {
            movement_dir = right;
            setDirection(right);
            moveAtAngle(right,2);
            //pixels_moved+=2;
        }
        else
        {
            movement_dir = left;
            setDirection(left);
            moveAtAngle(left,2);
            //pixels_moved+=2;
        }
    }
}


void Avatar::doSomething()
{
    int die_roll = 0;
    
    if (!isWalking)
    {
        int result = getWorld()->getAction(getPnum());
        if (result != 0)
        {
            if (result == 5)
            {
                die_roll = randInt(1,10);
                setTicks(8*die_roll);
                isWalking = true;
                m_rolls++;
            }
        }
        else
            return;
    }
    if (isWalking)
    {
        if (pixels_moved%16 == 0)
        {
            if (!canWalk(getX(),getY(),getAngle()))
            {
                changeDirection();
                pixels_moved+=2;
            }
            else
            {
                moveAtAngle(getAngle(),2);
                pixels_moved+=2;
            }
                
        }
        else
        {
            moveAtAngle(getAngle(),2);
            pixels_moved+=2;
        }
        setTicks(getTicks()-1);
        if (getTicks() == 0)
        {
            isWalking =  false;
        }
    }
}


void Actor::setTicks(int ticks)
{
    ticks_to_move = ticks;
}


void CoinSquare::doSomething()
{
    if (!isAlive())
        return;
}
