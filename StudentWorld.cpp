#include "StudentWorld.h"
#include "GameConstants.h"
#include <ostream>


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
    peach = nullptr;
    yoshi = nullptr;
    actors.clear();
}

int StudentWorld::init()
{
    startCountdownTimer(99);

    bd = new Board;
    
    string boardFile = assetPath() + "board0" +  to_string(getBoardNumber()) + ".txt";
    Board::LoadResult result = bd->loadBoard(boardFile);
    
    if (result ==  Board::load_fail_file_not_found){
        cerr << "Could not find" << boardFile<< "data file\n";
        return GWSTATUS_BOARD_ERROR;
    }
    else if (result == Board::load_fail_bad_format){
        cerr << "Your board was improperly formatted\n";
        return GWSTATUS_BOARD_ERROR;
    }
    else if (result == Board::load_success)
    {
        cerr  << "Successfully loaded board\n";
        
        for (int y =0; y < BOARD_HEIGHT; y++)
            for (int x=0; x < BOARD_WIDTH; x++)
            {
                Board::GridEntry ge = bd->getContentsOf(x,y);
                switch(ge)
                {
                    case Board::empty:
                    {
                        
                        break;
                    }
                    case Board::boo:
                    {
                        //
                        break;
                    }
                    case Board::bowser:
                    {
                        break;
                    }
                    case Board::player:
                    {
                        peach = new Avatar(this, IID_PEACH, 16*x, 16*y,1);
                        CoinSquare* blue = new CoinSquare(this, IID_BLUE_COIN_SQUARE, 16*x, 16*y, true);
                            actors.push_back(blue);
                        //yoshi = new Avatar(this, IID_YOSHI, x, y, 0, 1, 1.0,2);
                        break;
                    }
                    case Board::red_coin_square:
                    {
                        
                        break;
                    }
                    case Board::blue_coin_square:
                    {
                        CoinSquare* blue = new CoinSquare(this, IID_BLUE_COIN_SQUARE, 16*x, 16*y, true);
                        actors.push_back(blue);
                        break;
                    }
                    case Board::up_dir_square:
                    {
                        break;
                    }
                    case Board::down_dir_square:
                    {
                        break;
                    }
                    case Board::left_dir_square:
                    {
                        break;
                    }
                    case Board::right_dir_square:
                    {
                        break;
                    }
                    case Board::event_square:
                    {
                        break;
                    }
                    case Board::bank_square:
                    {
                        break;
                    }
                    case Board::star_square:
                    {
                        break;
                    }
                }
            }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.
    peach->doSomething();
    //yoshi->doSomething();
    
    vector<Actor*>:: iterator it;
    it = actors.begin();
    while(it != actors.end())
    {
        (*it)->doSomething();
        it++;
    }
     
    
    setGameStatText("P1 Roll: " + to_string(peach->getRolls()) + " Stars: " + to_string(peach->getStars()) + " $$: " + to_string(peach->getCoins()) + " | Time: " + to_string(timeRemaining()) + " | Bank: 0 | P2 Roll: 0 Stars: 0 $$: 0");
    
    if (timeRemaining() <= 0)
    {
        playSound(SOUND_GAME_FINISHED);
        
        //if (yoshi->get)
        //setFinalScore(getWinnerStars(), getWinnerCoins());
       //fix this
        
    }
    
    
	return GWSTATUS_CONTINUE_GAME;
}
          

void StudentWorld::cleanUp()
{
    delete peach;

    vector<Actor*>:: iterator it;
    it = actors.begin();
    while(it != actors.end())
    {
        delete *it;
        it++;
    }
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
