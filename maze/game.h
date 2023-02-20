#ifndef GAME_H
#define GAME_H

#include"default/default.h"
#include"default/maze.h"
#include"print.h"
#include"random.h"
#include"default/buf.h"
#include"object/Object.h"
#include"object/player.h"
#include"default/YNquestion.h"
#include"const.h"
#include"default/option.h"

#define mazeNumber 31
#define mazeLengthMax 999
#define mazeLengthMin 65

#define RESTART 0
#define RESET 1
#define SETTING 2
#define EXIT 3
#define CANCEL 4

enum class State{
    Setting,
    Maze,
    YesNoQ,
    Option,
    GoalOption,
    End,
    GoalEnd,
};

class Game
{
    private:
        Maze* maze;
        Player* player;
        Buf* buf;
        Print* print;
        YNQuestion** questions;
        Option* playingOption;
        Option* goalOption;
        int questionNum;
        int isGoal;
        int gameEnd;
        int loopEnd;
        int length;
        State state;

    public:
        Game();
        ~Game();
        void setting();
        void gameStart();
        void gameLoop();
        void keySet(char key);
        void setEvent(int x,int y);
};

#endif