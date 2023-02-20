#ifndef PLAYER_H
#define PLAYER_H

#include"Object.h"

class Player : public Object
{
    public:
        Player(char input);
        void move(int direction);
};

#endif