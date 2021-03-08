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
#include "../../include/audio/SoundControl.h"

class Controller{
public:
    Controller();
    bool inGame;
    int level;
    Model* model;
    View *view;
    SoundControl* soundControl;
    void run();
    void updateMainWindow();
    void onStart();
    void updateGameWindow();
    int loadLevel();
    void spawnEnemys();
    void calcdirection(EnemyShip* ele, int playerQuadrant);
};
#endif //BOSCONIAN_CONTROLLER_H
