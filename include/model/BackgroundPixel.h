//
// Created by basti on 15.12.2020.
//
#include "../../libs/glfw-3.3.2/include/GLFW/glfw3.h"
#include "GameObject.h"
#include <gl/gl.h>

#ifndef BOSCONIAN_BACKGROUNDPIXEL_H
#define BOSCONIAN_BACKGROUNDPIXEL_H

class BackgroundPixel {
public:
    BackgroundPixel();
    Position2D pos;
    static GLubyte colors[320];
    int color;
};
#endif //BOSCONIAN_BACKGROUNDPIXEL_H
