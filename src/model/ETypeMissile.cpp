//
// Created by basti on 08.01.2021.
//

#include "../../include/model/ETypeMissile.h"

GLubyte* ETypeMissile::sprites[24];
int ETypeMissile::score = 70;

ETypeMissile::ETypeMissile(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {

}
