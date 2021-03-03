//
// Created by basti on 08.01.2021.
//

#ifndef BOSCONIAN_ITYPEMISSILE_H
#define BOSCONIAN_ITYPEMISSILE_H

#include "EnemyShip.h"

class ITypeMissile : public EnemyShip {
public:
    ITypeMissile(int posX, int posY, int dir);
    static int score;
};

#endif //BOSCONIAN_ITYPEMISSILE_H
