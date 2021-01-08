//
// Created by basti on 08.01.2021.
//

#include "../../include/model/ITypeMissile.h"

GLubyte* ITypeMissile::sprites[24];
int ITypeMissile::score = 50;

ITypeMissile::ITypeMissile(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {

}

