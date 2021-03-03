//
// Created by basti on 13.12.2020.
//

#include "../../include/model/Player.h"

Position2D Player::drawOffset = {-32,32};

Player::Player() : GameObject() {
    direction[0] = 0;
    direction[1] = -1;
    pos.x = MAP_WIDTH / 2;
    pos.y = (MAP_HEIGHT / 4) * 3 ;
    spriteDirection = SpriteDirection::up;
    spriteLight = SpriteLights::on;
    playerspeed = 4;
    lifes = 4;
    score = 0;
}

void Player::resetPosition() {
    pos.x = MAP_WIDTH / 2;
    pos.y = (MAP_HEIGHT / 4) * 3;
    direction[0] = 0;
    direction[1] = -1;
    spriteDirection = SpriteDirection::up;
    spriteLight = SpriteLights::on;
}