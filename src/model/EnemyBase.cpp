//
// Created by basti on 13.12.2020.
//

#include "../../include/model/EnemyBase.h"

Position2D EnemyBase::drawOffsetMiddle{-32,32};;

EnemyBase::EnemyBase(int x, int y) : GameObject() {
    pos.x = x;
    pos.y = y;
    rot = rand() % 2;
    if(rot == 0) {
        parts.push_back(new EnemyBasePart(pos.x, pos.y - 110, 0));
        parts.push_back(new EnemyBasePart(pos.x - 100, pos.y - 50, 1));
        parts.push_back(new EnemyBasePart(pos.x - 100, pos.y + 50, 2));
        parts.push_back(new EnemyBasePart(pos.x, pos.y + 110, 3));
        parts.push_back(new EnemyBasePart(pos.x + 100, pos.y + 50, 4));
        parts.push_back(new EnemyBasePart(pos.x + 100, pos.y - 50, 5));
    } else {
        parts.push_back(new EnemyBasePart(pos.x - 110, pos.y, 6));
        parts.push_back(new EnemyBasePart(pos.x - 50, pos.y + 100, 7));
        parts.push_back(new EnemyBasePart(pos.x + 50, pos.y + 100, 8));
        parts.push_back(new EnemyBasePart(pos.x + 110, pos.y, 9));
        parts.push_back(new EnemyBasePart(pos.x + 50, pos.y -100, 10));
        parts.push_back(new EnemyBasePart(pos.x - 50, pos.y -100, 11));
    }
    score = 1500;
    isOpen = false;
    timer = 0;
}