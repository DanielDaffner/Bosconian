//
// Created by basti on 08.01.2021.
//

#include "../../include/model/eTypeMissile.h"

GLubyte* eTypeMissile::sprites[24];
int eTypeMissile::score = 70;

eTypeMissile::eTypeMissile(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {

}

