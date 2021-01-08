//
// Created by basti on 13.12.2020.
//

#include "../../include/model/EnemyShip.h"

//GLubyte* EnemyShip::sprites[24];
GLubyte* EnemyShip::spritesExplosion[3];
Position2D EnemyShip::drawOffset = {-32,32};
double EnemyShip::directions[24][2] = {{0,-1 },{-1,-3},{-2,-3},
                                   {-1,-1},{-3,-2},{-3,-1},
                                   {-1,0},{-3,1},{-3,2},
                                   {-1,1},{-2,3},{-1,3},
                                   {0,1},{1,3},{2,3},
                                   { 1,1},{3,2},{3,1},
                                   {1 ,0},{3,-1},{3,-2},
                                   {1,-1},{2,-3},{1,-3},
};
EnemyShip::EnemyShip(int posX, int posY, int dir) : GameObject() {
    pos.x = posX;
    pos.y = posY;
    direction = dir;

}