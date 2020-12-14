//
// Created by basti on 11.12.2020.
//
#include "../view/View.h"
#include "../../include/model/Player.h"
#ifndef BOSCONIAN_CONTROLLER_H
#define BOSCONIAN_CONTROLLER_H

class Controller{
public:
    int posxy[2];
    int direction[2];
    int viewportpos[4];
    bool inGame;
    Controller();
    Player* myplayer;
    View *view;
    int init();
    void updateMainWindow();
    void updateGameWindow();

};
#endif //BOSCONIAN_CONTROLLER_H
