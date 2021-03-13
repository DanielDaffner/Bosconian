//
// Created by basti on 11.12.2020.
//
#include <corecrt_wstdio.h>
#include "../view/View.h"
#include "../model/Model.h"
#include "../../include/model/Player.h"
#include "../../include/model/Mine.h"
#include "../../include/audio/SoundControl.h"
#ifndef BOSCONIAN_CONTROLLER_H
#define BOSCONIAN_CONTROLLER_H

enum State{
    MainWindow = 0,
    InGame = 1,
    LevelComplete = 2,
    GameOver = 3
};

class Controller{
public:
    Controller();
    int level;
    State state;
    Model* model;
    View *view;
    bool inGame;
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
