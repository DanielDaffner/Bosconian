//
// Created by basti on 13.12.2020.
//
#include "../../libs/glfw-3.3.2/include/GLFW/glfw3.h"
#include <gl/gl.h>
#include "../Utility.h"

#ifndef BOSCONIAN_GAMEOBJECT_H
#define BOSCONIAN_GAMEOBJECT_H

class GameObject {
public:
    GameObject();
    Position2D pos;
    bool collision;
    int explosionPhase;
    int colliderSize;
    int score;

};
#endif //BOSCONIAN_GAMEOBJECT_H
