//
// Created by basti on 14.12.2020.
//
#include "Mine.h"
#include "Player.h"
#include <list>

#ifndef BOSCONIAN_MODEL_H
#define BOSCONIAN_MODEL_H

class Model {
public:
    Model();
    Player* player;
    std::list<Mine*> mines;
};
#endif //BOSCONIAN_MODEL_H
