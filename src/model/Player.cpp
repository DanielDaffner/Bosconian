//
// Created by basti on 13.12.2020.
//

#include "../../include/model/Player.h"

Player::Player() : GameObject() {
    direction[0] = 0;
    direction[1] = -1;
    pos.x = MAP_WIDTH / 2;
    pos.y = (MAP_HEIGHT / 4) * 3 ;
    spriteDirection = SpriteDirection::up;
    spriteLight = SpriteLights::on;
    playerspeed = 4;
    lifes = 2;
    score = 0;
    firecd = 10;
    colliderSize = 32;
}

void Player::resetPosition() {
    pos.x = MAP_WIDTH / 2;
    pos.y = (MAP_HEIGHT / 4) * 3;
    direction[0] = 0;
    direction[1] = -1;
    spriteDirection = SpriteDirection::up;
    spriteLight = SpriteLights::on;
}