//
// Created by basti on 08.01.2021.
//

#include "../../include/model/ITypeMissile.h"

ITypeMissile::ITypeMissile(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {
    type = 0;
    score = 50;
}

