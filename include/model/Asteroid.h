//
// Created by basti on 13.12.2020.
//

#include "GameObject.h"

#ifndef BOSCONIAN_ASTEROID_H
#define BOSCONIAN_ASTEROID_H

class Asteroid : public GameObject {
public:
    Asteroid(int x, int y);
    static Position2D drawOffset;
    static int score;
};

#endif //BOSCONIAN_ASTEROID_H
