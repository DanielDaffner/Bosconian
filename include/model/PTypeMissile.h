//
// Created by basti on 08.01.2021.
//

#ifndef BOSCONIAN_PTYPEMISSILE_H
#define BOSCONIAN_PTYPEMISSILE_H

#include "EnemyShip.h"

class PTypeMissile : public EnemyShip {
public:
    PTypeMissile(int posX, int posY, int dir);
    static GLubyte* sprites[24];
    static int score;
};

#endif //BOSCONIAN_PTYPEMISSILE_H
