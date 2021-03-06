//
// Created by basti on 16.12.2020.
//

#ifndef BOSCONIAN_PROJECTILEPLAYER_H
#define BOSCONIAN_PROJECTILEPLAYER_H

#include "GameObject.h"

class ProjectilePlayer : public GameObject{
public:
    static int projectileSpeed;
    ProjectilePlayer(int posx, int posy, int dirx, int diry, int spritedir);
    Position2D direction{};
    int spritedirection;
    int traveled;
};
#endif //BOSCONIAN_PROJECTILEPLAYER_H
