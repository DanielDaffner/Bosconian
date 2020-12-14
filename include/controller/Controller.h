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
    int posxy[2];
    int direction[2];
    int viewportpos[4];
    bool inGame;
    GLubyte* shipRender;
    int wihi[2];
    Controller();
    Player* myplayer;
    Model* model;
    View *view;
    int init();
    void updateMainWindow();
    void onStart();
    void updateGameWindow();
    void loadSprites();
    int getSprite(GLubyte* &dst, char* filepath);
};
#endif //BOSCONIAN_CONTROLLER_H
