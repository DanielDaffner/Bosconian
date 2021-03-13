//
// Created by basti on 09.01.2021.
//

#ifndef BOSCONIAN_FORMATION_H
#define BOSCONIAN_FORMATION_H

#include <list>
#include "GameObject.h"
#include "EnemyShip.h"

class Formation : public GameObject {
public:
    Formation(int x, int y, int dir);
    std::list<GameObject*> follower;
    EnemyShip* leader;
    int formationType;
    int formationMissile;
    static Position2D formationOffset[4][4];
};

#endif //BOSCONIAN_FORMATION_H
