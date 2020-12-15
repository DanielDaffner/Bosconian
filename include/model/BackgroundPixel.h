//
// Created by basti on 15.12.2020.
//
#include "../../libs/glfw-3.3.2/include/GLFW/glfw3.h"
#include "GameObject.h"
#include <gl/gl.h>

#ifndef BOSCONIAN_BACKGROUNDPIXEL_H
#define BOSCONIAN_BACKGROUNDPIXEL_H

class BackgroundPixel : public GameObject {
public:
    BackgroundPixel();
    static GLubyte colors[48];
    int color;
};
#endif //BOSCONIAN_BACKGROUNDPIXEL_H
