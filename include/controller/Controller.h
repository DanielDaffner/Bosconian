//
// Created by basti on 11.12.2020.
//
#include "../view/View.h"
#ifndef BOSCONIAN_CONTROLLER_H
#define BOSCONIAN_CONTROLLER_H

class Controller{
public:
    int posxy[2];
    int direction[2];
    Controller();
    View *view;
    int init();
    void update();

};
#endif //BOSCONIAN_CONTROLLER_H
