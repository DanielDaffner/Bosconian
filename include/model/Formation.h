//
// Created by basti on 09.01.2021.
//

#ifndef BOSCONIAN_FORMATION_H
#define BOSCONIAN_FORMATION_H

#include <list>
#include "GameObject.h"

class Formation : public GameObject {
public:
    Formation(int x, int y);
    static Position2D drawOffset;
    std::list<GameObject*> follower;
    int formationType;
    int formationMissile;
    int dir;
    static Position2D formationOffset[4][4];
    static int score;

};

#endif //BOSCONIAN_FORMATION_H
