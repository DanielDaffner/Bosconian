//
// Created by basti on 13.12.2020.
//
#include "../../include/model/Mine.h"

GLubyte* Mine::sprites;
GLubyte* Mine::spritesExplosion[3];
Position2D Mine::drawOffset = {-32,32};
int score = 20;

Mine::Mine(int x, int y) : GameObject() {
    pos.x = x;
    pos.y = y;
}