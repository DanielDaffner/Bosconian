//
// Created by basti on 08.01.2021.
//

#ifndef BOSCONIAN_ITYPEMISSILE_H
#define BOSCONIAN_ITYPEMISSILE_H

#include "EnemyShip.h"

class iTypeMissile : public EnemyShip {
public:
    iTypeMissile(int posX, int posY, int dir);
    static GLubyte* sprites[24];

};

#endif //BOSCONIAN_ITYPEMISSILE_H
