//
// Created by basti on 08.01.2021.
//

#include "../../include/model/SpyShip.h"

SpyShip::SpyShip(int posX, int posY, int dir) : EnemyShip(posX, posY, dir) {
    type = 3;
    score = 500;
}