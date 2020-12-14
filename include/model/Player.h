//
// Created by basti on 13.12.2020.
//
#include "GameObject.h"

#ifndef BOSCONIAN_PLAYER_H
#define BOSCONIAN_PLAYER_H

enum PlayerSprite{
    up = 0,
    upright = 1,
    right = 2,
    downright = 3,
    down = 4,
    downleft = 5,
    left = 6,
    upleft = 7
};

class Player : public GameObject {
public:
    static GLubyte* sprites[9][2];
};

#endif //BOSCONIAN_PLAYER_H
