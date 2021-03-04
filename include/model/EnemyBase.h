//
// Created by basti on 13.12.2020.
//

#ifndef BOSCONIAN_ENEMYBASE_H
#define BOSCONIAN_ENEMYBASE_H

#include <list>
#include "GameObject.h"
#include "EnemyBasePart.h"

class EnemyBase : public GameObject {
public:
    EnemyBase(int x, int y);
    static Position2D drawOffset;
    static Position2D drawOffsetMiddle;
    std::list<EnemyBasePart*> parts;
    static int score;
    int rot;
    bool isOpen;
    int timer;
};
#endif //BOSCONIAN_ENEMYBASE_H
