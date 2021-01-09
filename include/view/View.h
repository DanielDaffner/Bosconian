//
// Created by basti on 11.12.2020.
//
#include "../../libs/glfw-3.3.2/include/GLFW/glfw3.h"
#include <gl/GL.h>
#include "../model/Model.h"

#ifndef BOSCONIAN_VIEW_H
#define BOSCONIAN_VIEW_H


class View{
public:
    View(Model* modl);
    Model* model;
    GLFWwindow* window{};
    int viewportpos[4]{};
    int createMainWindow();
    void prepareFrame();
    void moveFrame();
    void render(Position2D pos, GLubyte* bitmap);
    void renderGameInfos(Position2D pos, GLubyte *bitmap);
    void renderStars(Position2D pos, GLubyte *bitmap);
    void drawString(Position2D pos, char* input);
    void drawNumber(Position2D pos,int number);
    void resetFrame();
};
#endif //BOSCONIAN_VIEW_H
