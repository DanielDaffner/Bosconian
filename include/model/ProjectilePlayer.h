//
// Created by basti on 16.12.2020.
//

#ifndef BOSCONIAN_PROJECTILEPLAYER_H
#define BOSCONIAN_PROJECTILEPLAYER_H

#include "GameObject.h"

class ProjectilePlayer : public GameObject{
public:
    ProjectilePlayer(int posx, int posy, int dirx, int diry);
    static int projectileSpeed;
    Position2D direction;
};
#endif //BOSCONIAN_PROJECTILEPLAYER_H
