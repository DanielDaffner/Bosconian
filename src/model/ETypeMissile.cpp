//
// Created by basti on 08.01.2021.
//

#include "../../include/model/ETypeMissile.h"

ETypeMissile::ETypeMissile(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {
    type = 1;
    score = 70;
}

