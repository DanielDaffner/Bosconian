//
// Created by basti on 13.12.2020.
//

#include "../../include/model/Player.h"
#include <gl/GL.h>

GLubyte* Player::sprites[9][2];
GLubyte* Player::spritesExplosion[3];
Position2D Player::drawOffset = {-32,32};

Player::Player() : GameObject() {
    direction[0]=0;
    direction[1]=-1;
    pos.x = 640;
    pos.y = 360;
    spriteDirection = SpriteDirection::up;
    spriteLight = SpriteLights::on;
    playerspeed = 4;
    lifes = 3;
    score = 0;
}

void Player::resetPosition() {
    pos.x = 640;
    pos.y = 360;
    direction[0]=0;
    direction[1]=-1;
    spriteDirection = SpriteDirection::up;
    spriteLight = SpriteLights::on;
}