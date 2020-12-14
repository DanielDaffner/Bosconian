//
// Created by basti on 13.12.2020.
//
#include "GameObject.h"

#ifndef BOSCONIAN_MINE_H
#define BOSCONIAN_MINE_H

class Mine : public GameObject {
public:
    Mine(int x, int y);
    static GLubyte* sprites;
    static GLubyte* spritesExplosion[3];
};
#endif //BOSCONIAN_MINE_H
