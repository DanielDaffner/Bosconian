//
// Created by basti on 08.01.2021.
//

#include "../../include/model/pTypeMissile.h"

GLubyte* pTypeMissile::sprites[24];
int pTypeMissile::score = 60;

pTypeMissile::pTypeMissile(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {

}

