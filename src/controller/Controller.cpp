//
// Created by basti on 11.12.2020.
//
#include "../../include/controller/Controller.h"
#include <iostream>

Controller::Controller() {

}
FILE* file;
GLubyte* test;
int Controller::init() {
    //init controller
    printf("init controller begin\n");
    inGame = false;
    posxy[0] = 630;
    posxy[1] = 800;
    direction[0] = 0;
    direction[1] = 0;
    viewportpos[0] = 0;
    viewportpos[1] = 0;
    viewportpos[2] = 1280;
    viewportpos[3] = 960;

    //open files

    printf("init controller done\n");
    file = fopen("../App_Data/pink_enemy_7_64.bmp", "r");
    if(file == nullptr) printf("fuck\n");
    else printf("file nich nu ll\n");
    test = new GLubyte[12682];
    fread(test,sizeof(GLubyte),12682,file);

    printf(" %u\n",*((uint32_t*)(test+30)));
    printf(" %u\n",*((uint32_t*)(test+14)));
    printf(" %u\n",*((uint32_t*)(test+22)));
    printf(" %u\n",*((uint16_t*)(test+28)));
    printf(" %u\n",*((uint16_t*)(test+50)));
    printf(" %u\n",*((uint16_t*)(test+10)));
    GLubyte swap=0;
    for(int i = 138; i < 12682; i+=4) {
        swap = test[i];
        test[i] = test[i+2];
        test[i+2] = swap;

    }
    return 0;
}

void Controller::updateMainWindow() {


    int space = glfwGetKey(view->window, GLFW_KEY_SPACE);

    if (space == GLFW_PRESS) {

    }
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION ); // Stack für Projektionsmatrix als
    // aktiven Matrixstack setzen
    glLoadIdentity();              // Identitätsmatrix auf den Stack laden

    // Eine orthogonale Projektionsmatrix zum Stack
    // dazu multiplizieren.
    glViewport(0,0,1920,1080);
    //glViewport(viewportpos[0],viewportpos[1],viewportpos[2],viewportpos[3]);

    //glOrtho( 0, 1280, 960, 0, 0, 1 );
    glOrtho( viewportpos[0], viewportpos[2], viewportpos[3], viewportpos[1], -1, 1 );

//    glBegin( GL_TRIANGLES ); // Wir wollen ein Dreieck zeichnen
//    glColor3f(1,0,0);      // Ab jetzt werden alle gezeichneten Punkte rot
//    glVertex3f(posxy[0],posxy[1]-100,0); // Der erste Eckpunkt ist mittig und 100 Pixel
//    // vom oberen Rand entfernt
//
//    glColor3f(0,1,0);      // Ab jetzt werden alle gezeichneten Punkte grün
//    glVertex3f(posxy[0]-100,posxy[1]+100,0); // Der zweite Eckpunkt ist 50 Pixel vom rechten
//    // und 100 Pixel vom unteren Rand entfernt
//
//    glColor3f(0,0,1);      // Ab jetzt werden alle gezeichneten Punkte blau
//    glVertex3f(posxy[0]+100,posxy[1]+100,0);  // Der dritte Eckpunkt ist 50 Pixel vom linken
//    // und 100 Pixel vom unteren Rand entfernt
//    glEnd();
    //posxy[0]+=direction[0];
    //posxy[1]+=direction[1];
    viewportpos[0] +=direction[0];
    viewportpos[1] +=direction[1];
    viewportpos[2] +=direction[0];
    viewportpos[3] +=direction[1];
    //glBitmap(56,56,0,0,0,0,test+55);
    //GLubyte* cmon = test+138;
    glDrawPixels(56,56,GL_RGBA,GL_UNSIGNED_BYTE,test+138);


}
void Controller::updateGameWindow() {

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
    glViewport(0,0,1280,960);
    //glViewport(viewportpos[0],viewportpos[1],viewportpos[2],viewportpos[3]);

    //glOrtho( 0, 1280, 960, 0, 0, 1 );
    glOrtho( viewportpos[0], viewportpos[2], viewportpos[3], viewportpos[1], -1, 1 );

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
    //posxy[0]+=direction[0];
    //posxy[1]+=direction[1];
    viewportpos[0] +=direction[0];
    viewportpos[1] +=direction[1];
    viewportpos[2] +=direction[0];
    viewportpos[3] +=direction[1];
    //glBitmap(56,56,0,0,0,0,test+55);
    //GLubyte* cmon = test+138;
    glDrawPixels(56,56,GL_RGBA,GL_UNSIGNED_BYTE,test+138);


}