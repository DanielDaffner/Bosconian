//
// Created by basti on 13.12.2020.
//
#include "../../include/model/Mine.h"

Position2D Mine::drawOffset = {-32,32};
int Mine::score = 20;

Mine::Mine(int x, int y) : GameObject() {
    pos.x = x;
    pos.y = y;
}