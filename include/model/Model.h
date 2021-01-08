//
// Created by basti on 14.12.2020.
//
#include "Mine.h"
#include "Player.h"
#include "BackgroundPixel.h"
#include "ProjectilePlayer.h"
#include "EnemyShip.h"
#include "ITypeMissile.h"
#include "eTypeMissile.h"
#include "PTypeMissile.h"
#include "EnemyBase.h"
#include "Asteroid.h"
#include <list>

#ifndef BOSCONIAN_MODEL_H
#define BOSCONIAN_MODEL_H

class Model {
public:
    Model();
    static GLubyte* alphabetWhite[29];
    static GLubyte* alphabetBlack[29];
    static GLubyte* numbers[10];
    static GLubyte* map;
    Player* player;
    std::list<Mine*> mines;
    std::list<Mine*> minesExploding;
    std::list<Asteroid*> asteroids;
    std::list<Asteroid*> asteroidsExplosion;
    std::list<ITypeMissile*> iTypeMissiles;
    std::list<ITypeMissile*> iTypeMissilesExploding;
    std::list<ITypeMissile*> pTypeMissiles;
    std::list<ITypeMissile*> pTypeMissilesExploding;
    std::list<ITypeMissile*> eTypeMissiles;
    std::list<ITypeMissile*> eTypeMissilesExploding;
    std::list<BackgroundPixel*> pixelarr[4];
    std::list<ProjectilePlayer*> projectilesPlayer;
    std::list<EnemyBase*> enemyBases;
    std::list<ProjectilePlayer*> projectileEnemyBases;
};
#endif //BOSCONIAN_MODEL_H
