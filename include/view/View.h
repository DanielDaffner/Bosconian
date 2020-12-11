//
// Created by basti on 11.12.2020.
//
#include "../../libs/glfw-3.3.2/include/GLFW/glfw3.h"
#include <gl/gl.h>

#ifndef BOSCONIAN_VIEW_H
#define BOSCONIAN_VIEW_H
class View{
public:
    View();
    GLFWwindow* window;
    int createWindow(int width, int height);
};
#endif //BOSCONIAN_VIEW_H
