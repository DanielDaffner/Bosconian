//
// Created by basti on 13.12.2020.
//

#include "../../include/model/Asteroid.h"

Position2D Asteroid::drawOffset = {-32,32};
int Asteroid::score = 10;

Asteroid::Asteroid(int x, int y) : GameObject() {
    pos.x = x;
    pos.y = y;
}