//
// Created by basti on 11.12.2020.
//
#include <corecrt_wstdio.h>
#include "../view/View.h"
#ifndef BOSCONIAN_CONTROLLER_H
#define BOSCONIAN_CONTROLLER_H

class Controller{
public:
    int posxy[2];
    int direction[2];
    int viewportpos[4];
    bool inGame;
    GLubyte** ship[8];
    GLubyte* shipRender;
    Controller();
    View *view;
    int init();
    void updateMainWindow();
    void updateGameWindow();
    void loadBitmapsShip();
    int getBitmapLength(_iobuf *tmp);
};
#endif //BOSCONIAN_CONTROLLER_H
