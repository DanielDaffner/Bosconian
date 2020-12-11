//
// Created by basti on 11.12.2020.
//
#include "../view/View.h"
#ifndef BOSCONIAN_CONTROLLER_H
#define BOSCONIAN_CONTROLLER_H

class Controller{
public:
    Controller();
    View *view;
    int init();
    void update();
};
#endif //BOSCONIAN_CONTROLLER_H
