//
// Created by basti on 13.12.2020.
//

#include "../../include/model/EnemyBase.h"

GLubyte* EnemyBase::sprites;
Position2D EnemyBase::drawOffset;
int EnemyBase::score = 2000;

EnemyBase::EnemyBase(int x, int y) : GameObject() {
    pos.x = x;
    pos.y = y;
    parts.push_back(new EnemyBasePart(pos.x-100, pos.y));
    parts.push_back(new EnemyBasePart(pos.x+100, pos.y));
    parts.push_back(new EnemyBasePart(pos.x-40, pos.y-100));
    parts.push_back(new EnemyBasePart(pos.x-40, pos.y+100));
    parts.push_back(new EnemyBasePart(pos.x+40, pos.y-100));
    parts.push_back(new EnemyBasePart(pos.x+40, pos.y+100));
    isOpen = false;
    timer = 0;
}