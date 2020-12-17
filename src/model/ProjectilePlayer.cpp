//
// Created by basti on 16.12.2020.
//

#include "../../include/model/ProjectilePlayer.h"

int ProjectilePlayer::projectileSpeed = 16;
GLubyte* ProjectilePlayer::sprites[4];
Position2D ProjectilePlayer::drawOffset = {-2,2};

ProjectilePlayer::ProjectilePlayer(int posx, int posy, int dirx, int diry, int spritedir) : GameObject() {
    pos.x = posx;
    pos.y = posy;
    direction.x = dirx;
    direction.y = diry;
    sprite = ProjectilePlayer::sprites[spritedir%4];
    traveled = 0;
}

