//
// Created by basti on 03.01.2021.
//

#ifndef BOSCONIAN_ENEMYBASEPART_H
#define BOSCONIAN_ENEMYBASEPART_H

#include "GameObject.h"

class EnemyBasePart : public GameObject {
public:
    EnemyBasePart(double x, double y, int dir);
    static int score;
    static Position2D drawOffset[12];
    int dir;

};

#endif //BOSCONIAN_ENEMYBASEPART_H
