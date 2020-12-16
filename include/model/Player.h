//
// Created by basti on 13.12.2020.
//
#include "GameObject.h"
#include "../Utility.h"
#ifndef BOSCONIAN_PLAYER_H
#define BOSCONIAN_PLAYER_H

enum SpriteDirection{
    up = 0,
    upright = 1,
    right = 2,
    downright = 3,
    down = 4,
    downleft = 5,
    left = 6,
    upleft = 7
};
enum SpriteLights{
    on = 0,
    off = 1
};

class Player : public GameObject {
public:
    Player();
    static GLubyte* sprites[9][2];
    int direction[2]{};
    int playerspeed;
    int spriteDirection;
    int spriteLight;
};

#endif //BOSCONIAN_PLAYER_H
