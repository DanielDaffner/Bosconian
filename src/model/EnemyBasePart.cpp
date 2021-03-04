//
// Created by basti on 03.01.2021.
//

#include "../../include/model/EnemyBasePart.h"

int EnemyBasePart::score = 200;

EnemyBasePart::EnemyBasePart(double x, double y, int direct) : GameObject() {
    dir = direct;
    pos.x = x;
    pos.y = y;
}