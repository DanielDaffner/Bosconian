//
// Created by basti on 09.01.2021.
//

#ifndef BOSCONIAN_FORMATION_H
#define BOSCONIAN_FORMATION_H

#include <list>
#include "GameObject.h"

class EnemyBase : public GameObject {
public:
    EnemyBase(int x, int y);
    static GLubyte* sprites[16];
    static GLubyte* spritesExplosion[3];
    static Position2D drawOffset;
    std::list<EnemyBasePart*> parts;
    static int score;
    bool isOpen;
    int timer;
};

#endif //BOSCONIAN_FORMATION_H
