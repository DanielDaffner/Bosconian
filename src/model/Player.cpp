//
// Created by basti on 13.12.2020.
//

#include "../../include/model/Player.h"
#include <gl/GL.h>

Player::Player() : GameObject() {
    direction[0]=0;
    direction[1]=-1;
    pos.x = 640;
    pos.y = 360;
    spriteDirection = SpriteDirection::up;
    spriteLight = SpriteLights::on;
    playerspeed = 4;
}

GLubyte* Player::sprites[9][2];