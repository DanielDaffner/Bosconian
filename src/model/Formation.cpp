//
// Created by basti on 09.01.2021.
//

#include "../../include/model/Formation.h"
#include "../../include/model/ITypeMissile.h"

GLubyte* Formation::sprites[3][24];
GLubyte* Formation::spritesExplosion[3];
Position2D Formation::drawOffset = {-144,144};
int Formation::score = 1500;
Position2D Formation::formationOffset[4][4] = { { Position2D{0,1},Position2D{0,2},Position2D{0,3},Position2D{0,4} },
                                          { Position2D{-1,0},Position2D{1,0},Position2D{0,1},Position2D{0,-1} },
                                          { Position2D{-1,-1},Position2D{1,1},Position2D{1,-1},Position2D{-1,1} },
                                          { Position2D{-1,1},Position2D{-2,2},Position2D{1,1},Position2D{2,2} }
};
Formation::Formation(int x, int y) : GameObject() {
    pos.x = x;
    pos.y = y;
    dir = 0;
    formationMissile = rand() % 3;
    formationType = rand() % 4;
    for(int i = 0; i < 4; i++) {
        follower.push_back(new ITypeMissile(pos.x + formationOffset[formationType][0+i].x, pos.y + formationOffset[formationType][0+i].y, i));
    }

}