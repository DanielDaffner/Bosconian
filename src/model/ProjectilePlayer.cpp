//
// Created by basti on 16.12.2020.
//

#include "../../include/model/ProjectilePlayer.h"

int ProjectilePlayer::projectileSpeed = 8;

ProjectilePlayer::ProjectilePlayer(int posx, int posy, int dirx, int diry) {
    pos.x = posx;
    pos.y = posy;
    direction.x = dirx;
    direction.y = diry;
}

