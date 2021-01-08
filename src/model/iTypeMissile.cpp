//
// Created by basti on 08.01.2021.
//

#include "../../include/model/iTypeMissile.h"

GLubyte* iTypeMissile::sprites[24];
int iTypeMissile::score = 50;

iTypeMissile::iTypeMissile(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {

}

