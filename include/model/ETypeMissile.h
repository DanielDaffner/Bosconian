//
// Created by basti on 08.01.2021.
//

#ifndef BOSCONIAN_ETYPEMISSILE_H
#define BOSCONIAN_ETYPEMISSILE_H

#include "EnemyShip.h"

class ETypeMissile : public EnemyShip {
public:
    ETypeMissile(int posX, int posY, int dir);
    static GLubyte* sprites[24];
    static int score;
};

#endif //BOSCONIAN_ETYPEMISSILE_H
