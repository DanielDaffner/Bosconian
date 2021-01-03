//
// Created by basti on 13.12.2020.
//

#ifndef BOSCONIAN_ENEMYSHIP_H
#define BOSCONIAN_ENEMYSHIP_H

#include "GameObject.h"

class EnemyShip : public GameObject {
public:
    EnemyShip();
    static GLubyte* sprites[24];
    static GLubyte* spritesExplosion[3];
    static Position2D drawOffset;
    static int score;
};

#endif //BOSCONIAN_ENEMYSHIP_H
