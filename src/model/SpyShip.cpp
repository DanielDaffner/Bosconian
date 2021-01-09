//
// Created by basti on 08.01.2021.
//

#include "../../include/model/SpyShip.h"

GLubyte* SpyShip::sprites[24];
int SpyShip::score = 500;

SpyShip::SpyShip(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {

}