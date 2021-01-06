//
// Created by basti on 13.12.2020.
//

#ifndef BOSCONIAN_ENEMYSHIP_H
#define BOSCONIAN_ENEMYSHIP_H

#include "GameObject.h"

class EnemyShip : public GameObject {
public:
    EnemyShip(int posX,int posY, int dir);
    static GLubyte* sprites[24];
    static GLubyte* spritesExplosion[3];
    static Position2D drawOffset;
    static const int speed = 3;
    double directions[8][2] = {{0,-1 },{-1,-1},{-1,0},{-1,1},{0,1},{ 1,1},{0,1},{1,-1}};
    int direction;
    int turned = 3;
};

#endif //BOSCONIAN_ENEMYSHIP_H
