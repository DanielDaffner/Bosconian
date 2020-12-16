//
// Created by basti on 14.12.2020.
//
#include "Mine.h"
#include "Player.h"
#include "BackgroundPixel.h"
#include <list>

#ifndef BOSCONIAN_MODEL_H
#define BOSCONIAN_MODEL_H

class Model {
public:
    Model();
    Player* player;
    std::list<Mine*> mines;
    std::list<Mine*> minesExploding;
    std::list<BackgroundPixel*> pixelarr[4];
};
#endif //BOSCONIAN_MODEL_H
