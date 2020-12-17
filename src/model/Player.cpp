//
// Created by basti on 13.12.2020.
//

#include "../../include/model/Player.h"
#include <gl/GL.h>

GLubyte* Player::sprites[9][2];
Position2D Player::drawOffset = {-32,32};

Player::Player() : GameObject() {
    direction[0]=0;
    direction[1]=-1;
    pos.x = 640;
    pos.y = 360;
    spriteDirection = SpriteDirection::up;
    spriteLight = SpriteLights::on;
    playerspeed = 4;
}

void Player::resetPosition() {
    pos.x = 640;
    pos.y = 360;
}