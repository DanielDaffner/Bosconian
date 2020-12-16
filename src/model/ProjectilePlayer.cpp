//
// Created by basti on 16.12.2020.
//

#include "../../include/model/ProjectilePlayer.h"

int ProjectilePlayer::projectileSpeed = 8;
GLubyte* ProjectilePlayer::sprites[4];

ProjectilePlayer::ProjectilePlayer(int posx, int posy, int dirx, int diry, int spritedir) {
    pos.x = posx;
    pos.y = posy;
    direction.x = dirx;
    direction.y = diry;
//    sprite = ProjectilePlayer::sprites[spritedir/4];
}

