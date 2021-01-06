//
// Created by basti on 13.12.2020.
//

#include "../../include/model/EnemyShip.h"

GLubyte* EnemyShip::sprites[24];
GLubyte* EnemyShip::spritesExplosion[3];
Position2D EnemyShip::drawOffset = {-32,32};

EnemyShip::EnemyShip(int posX, int posY, int dir) : GameObject() {
    pos.x = posX;
    pos.y = posY;
    direction = dir;

}