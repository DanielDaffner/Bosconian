//
// Created by basti on 08.01.2021.
//

#ifndef BOSCONIAN_ETYPEMISSILE_H
#define BOSCONIAN_ETYPEMISSILE_H

#include "EnemyShip.h"

class eTypeMissile : public EnemyShip {
public:
    eTypeMissile(int posX, int posY, int dir);
    static GLubyte* sprites[24];

};

#endif //BOSCONIAN_ETYPEMISSILE_H
