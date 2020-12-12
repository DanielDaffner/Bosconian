//
// Created by basti on 11.12.2020.
//
#include "../../include/view/View.h"


View::View(){

}

int View::createWindow(int width, int height) {

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glViewport(0,0,width,height);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
}

