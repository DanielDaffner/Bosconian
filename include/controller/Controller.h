//
// Created by basti on 11.12.2020.
//
#include <corecrt_wstdio.h>
#include "../view/View.h"
#include "../model/Model.h"
#include "../../include/model/Player.h"
#include "../../include/model/Mine.h"
#ifndef BOSCONIAN_CONTROLLER_H
#define BOSCONIAN_CONTROLLER_H

class Controller{
public:
    Controller();
    bool inGame;
    int level;
    Model* model;
    View *view;
    void run();
    void updateMainWindow();
    void onStart();
    void updateGameWindow();
    int loadLevel();
    void spawnEnemys();
};
#endif //BOSCONIAN_CONTROLLER_H
