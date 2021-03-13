//
// Created by basti on 08.01.2021.
//

#include "../../include/model/PTypeMissile.h"

PTypeMissile::PTypeMissile(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {
    type = 2;
    score = 60;
}

