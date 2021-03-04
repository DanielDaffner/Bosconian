//
// Created by basti on 13.12.2020.
//

#include "../../include/model/EnemyBase.h"

Position2D EnemyBase::drawOffset{-144,144};
Position2D EnemyBase::drawOffsetMiddle{-32,32};;
int EnemyBase::score = 1500;

EnemyBase::EnemyBase(int x, int y) : GameObject() {
    pos.x = x;
    pos.y = y;
    rot = rand() % 2;
    if(rot == 0) {
        parts.push_back(new EnemyBasePart(pos.x - 100, pos.y, 0));
        parts.push_back(new EnemyBasePart(pos.x + 100, pos.y, 1));
        parts.push_back(new EnemyBasePart(pos.x - 40, pos.y - 100, 2));
        parts.push_back(new EnemyBasePart(pos.x - 40, pos.y + 100, 3));
        parts.push_back(new EnemyBasePart(pos.x + 40, pos.y - 100, 4));
        parts.push_back(new EnemyBasePart(pos.x + 40, pos.y + 100, 5));
    } else {
        parts.push_back(new EnemyBasePart(pos.x - 100, pos.y, 6));
        parts.push_back(new EnemyBasePart(pos.x + 100, pos.y, 7));
        parts.push_back(new EnemyBasePart(pos.x - 40, pos.y - 100, 8));
        parts.push_back(new EnemyBasePart(pos.x - 40, pos.y + 100, 9));
        parts.push_back(new EnemyBasePart(pos.x + 40, pos.y - 100, 10));
        parts.push_back(new EnemyBasePart(pos.x + 40, pos.y + 100, 11));
    }
    isOpen = false;
    timer = 0;
}