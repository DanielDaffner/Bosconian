//
// Created by basti on 13.12.2020.
//

#include "../../include/model/Asteroid.h"
#include "stdlib.h"
Asteroid::Asteroid(int x, int y) : GameObject() {
    pos.x = x;
    pos.y = y;
    score = 10;
    type = rand() % 3;
}