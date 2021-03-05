//
// Created by basti on 14.12.2020.
//
#include "Mine.h"
#include "Player.h"
#include "BackgroundPixel.h"
#include "ProjectilePlayer.h"
#include "EnemyShip.h"
#include "ITypeMissile.h"
#include "ETypeMissile.h"
#include "PTypeMissile.h"
#include "EnemyBase.h"
#include "Asteroid.h"
#include "Formation.h"
#include <list>

#ifndef BOSCONIAN_MODEL_H
#define BOSCONIAN_MODEL_H

class Model {
public:
    Model();
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
    std::list<EnemyBase*> enemyBasesExploding;
    std::list<EnemyBasePart*> enemyBasePartsExploding;
    std::list<ProjectilePlayer*> projectileEnemyBases;
    std::list<Formation*> formations;
    //evt später als array aus datei geladen
    int highScore=0;
};
#endif //BOSCONIAN_MODEL_H
