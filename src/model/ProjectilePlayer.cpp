//
// Created by basti on 16.12.2020.
//

#include "../../include/model/ProjectilePlayer.h"

int ProjectilePlayer::projectileSpeed = 24;

ProjectilePlayer::ProjectilePlayer(int posx, int posy, int dirx, int diry, int spritedir) : GameObject() {
    pos.x = posx;
    pos.y = posy;
    direction.x = dirx;
    direction.y = diry;
    spritedirection = spritedir%4;
    traveled = 0;
}

