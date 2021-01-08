//
// Created by basti on 08.01.2021.
//

#ifndef BOSCONIAN_SPYSHIP_H
#define BOSCONIAN_SPYSHIP_H

#include "EnemyShip.h"

class SpyShip : public EnemyShip {
public:
    SpyShip(int posX, int posY, int dir);
    static GLubyte* sprites[24];
    static int score;
};

#endif //BOSCONIAN_SPYSHIP_H
