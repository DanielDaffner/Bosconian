//
// Created by basti on 11.12.2020.
//
#include "../../include/controller/Controller.h"
#include <iostream>

Controller::Controller() {

}

int Controller::init() {
    view = new View();
    //view->createWindow(1280,960);
    posxy[0] = 630;
    posxy[1] = 800;
    direction[0] = 0;
    direction[1] = 0;
    printf("setcallback");

    return 0;
}

void Controller::update() {
    int up = glfwGetKey(view->window, GLFW_KEY_UP);
    int left = glfwGetKey(view->window, GLFW_KEY_LEFT);
    int right = glfwGetKey(view->window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(view->window, GLFW_KEY_DOWN);
    int space = glfwGetKey(view->window, GLFW_KEY_SPACE);
    if (up == GLFW_PRESS) {
        direction[0] = 0;
        direction[1] = -1;
    }
    if (left == GLFW_PRESS) {
        direction[0] = -1;
        direction[1] = 0;
    }
    if (right == GLFW_PRESS) {
        direction[0] = 1;
        direction[1] = 0;
    }
    if (down == GLFW_PRESS) {
        direction[0] = 0;
        direction[1] = 1;
    }
    if (space == GLFW_PRESS) {
        direction[0] = 0;
        direction[1] = 0;
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION ); // Stack für Projektionsmatrix als
    // aktiven Matrixstack setzen
    glLoadIdentity();              // Identitätsmatrix auf den Stack laden

    // Eine orthogonale Projektionsmatrix zum Stack
    // dazu multiplizieren.
    glOrtho( 0, 1280, 960, 0, 0, 1 );

    glBegin( GL_TRIANGLES ); // Wir wollen ein Dreieck zeichnen
    glColor3f(1,0,0);      // Ab jetzt werden alle gezeichneten Punkte rot
    glVertex3f(posxy[0],posxy[1]-100,0); // Der erste Eckpunkt ist mittig und 100 Pixel
    // vom oberen Rand entfernt

    glColor3f(0,1,0);      // Ab jetzt werden alle gezeichneten Punkte grün
    glVertex3f(posxy[0]-100,posxy[1]+100,0); // Der zweite Eckpunkt ist 50 Pixel vom rechten
    // und 100 Pixel vom unteren Rand entfernt

    glColor3f(0,0,1);      // Ab jetzt werden alle gezeichneten Punkte blau
    glVertex3f(posxy[0]+100,posxy[1]+100,0);  // Der dritte Eckpunkt ist 50 Pixel vom linken
    // und 100 Pixel vom unteren Rand entfernt
    glEnd();
    posxy[0]+=direction[0];
    posxy[1]+=direction[1];
}