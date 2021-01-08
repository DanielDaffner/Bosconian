//
// Created by basti on 13.12.2020.
//

#include "../../include/model/EnemyBase.h"

GLubyte* EnemyBase::sprites[16];
GLubyte* EnemyBase::spritesExplosion[3];
Position2D EnemyBase::drawOffset{-144,144};
int EnemyBase::score = 1500;

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