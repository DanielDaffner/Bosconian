//
// Created by basti on 08.01.2021.
//

#include "../../include/model/PTypeMissile.h"

GLubyte* PTypeMissile::sprites[24];
int PTypeMissile::score = 60;

PTypeMissile::PTypeMissile(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {

}

