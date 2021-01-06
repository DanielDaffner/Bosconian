//
// Created by basti on 14.12.2020.
//
#include "Mine.h"
#include "Player.h"
#include "BackgroundPixel.h"
#include "ProjectilePlayer.h"
#include "EnemyShip.h"
#include "EnemyBase.h"
#include <list>

#ifndef BOSCONIAN_MODEL_H
#define BOSCONIAN_MODEL_H

class Model {
public:
    Model();
    static GLubyte* alphabetWhite[29];
    static GLubyte* map;
    Player* player;
    std::list<Mine*> mines;
    std::list<Mine*> minesExploding;
    std::list<EnemyShip*> enemyShipsPink;
    std::list<BackgroundPixel*> pixelarr[4];
    std::list<ProjectilePlayer*> projectilesPlayer;
    std::list<EnemyBase*> enemyBases;
};
#endif //BOSCONIAN_MODEL_H
