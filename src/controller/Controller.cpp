//
// Created by basti on 11.12.2020.
//
#include "../../include/controller/Controller.h"

#include <iostream>

Controller::Controller() {

}

FILE* file1;
FILE* file2;
FILE* file3;
FILE* file4;
GLubyte* ship[4];
GLubyte* shipRender;

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
    viewportpos[3] = 720;
    myplayer = new Player();
    myplayer->posX = 3;

    view = new View();
    //open files


    //scam 1
    printf("init controller done\n");
    file1 = fopen("../App_Data/pink_enemy_7_64_down.bmp", "r");
    if(file1 == nullptr) printf("fuck 1\n");
    else printf("file 1 nich nu ll\n");
    ship[0] = new GLubyte[12682];
    fread(ship[0],sizeof(GLubyte),12682,file1);

    //scam 2

    file2 = fopen("../App_Data/pink_enemy_7_64_right.bmp", "r");
    if(file2 == nullptr) printf("fuck 2\n");
    else printf("file 2 nich nu ll\n");
    ship[1] = new GLubyte[12682];
    fread(ship[1],sizeof(GLubyte),12682,file2);

    //scam 3

    file3 = fopen("../App_Data/pink_enemy_7_64_up.bmp", "r");
    if(file3 == nullptr) printf("fuck 3\n");
    else printf("file 3 nich nu ll\n");
    ship[2] = new GLubyte[12682];
    fread(ship[2],sizeof(GLubyte),12682,file3);

    //scam 4

    file4 = fopen("../App_Data/pink_enemy_7_64_left.bmp", "r");
    if(file4 == nullptr) printf("fuck 4\n");
    else printf("file 4 nich nu ll\n");
    ship[3] = new GLubyte[12682];
    fread(ship[3],sizeof(GLubyte),12682,file4);




    //print bitmap header
    printf("printBitmapHeader");
    printf(" %u\n",*((uint32_t*)(ship[0]+30)));
    printf(" %u\n",*((uint32_t*)(ship[0]+14)));
    printf(" %u\n",*((uint32_t*)(ship[0]+22)));
    printf(" %u\n",*((uint16_t*)(ship[0]+28)));
    printf(" %u\n",*((uint16_t*)(ship[0]+50)));
    printf(" %u\n",*((uint16_t*)(ship[0]+10)));
    GLubyte swap=0;
    for(int i = 138; i < 12682; i+=4) {
        swap = ship[0][i];
        ship[0][i] = ship[0][i+2];
        ship[0][i+2] = swap;

    }
    return 0;
}

void Controller::updateMainWindow() {


    int up = glfwGetKey(view->window, GLFW_KEY_UP);
    if (up == GLFW_PRESS) {
    inGame = true;
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION ); // Stack für Projektionsmatrix als
    // aktiven Matrixstack setzen
    glLoadIdentity();              // Identitätsmatrix auf den Stack laden

    // Eine orthogonale Projektionsmatrix zum Stack
    // dazu multiplizieren.
    glViewport(0,0,1280,720);
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
    glDrawPixels(56,56,GL_RGBA,GL_UNSIGNED_BYTE,ship[0]+138);


}
void Controller::updateGameWindow() {
    // input
    int up = glfwGetKey(view->window, GLFW_KEY_UP);
    int left = glfwGetKey(view->window, GLFW_KEY_LEFT);
    int right = glfwGetKey(view->window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(view->window, GLFW_KEY_DOWN);
    int space = glfwGetKey(view->window, GLFW_KEY_SPACE);

    //set direction
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
        inGame = false;
    }

    //basti magic
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION ); // Stack für Projektionsmatrix als
    // aktiven Matrixstack setzen
    glLoadIdentity();              // Identitätsmatrix auf den Stack laden

    // Eine orthogonale Projektionsmatrix zum Stack
    // dazu multiplizieren.
    glViewport(0,0,1280,720);
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


    printf("vp0 min x %d\n", viewportpos[0]);
    printf("vp1 min y %d\n", viewportpos[1]);
    printf("vp2 max x %d\n", viewportpos[2]);
    printf("vp3 max y %d\n", viewportpos[3]);


    //draw ship
    glRasterPos2d(viewportpos[0]+640,viewportpos[1]+360);

    if (up == GLFW_PRESS) {
        shipRender = ship[2];
    }
    if (left == GLFW_PRESS) {
        shipRender = ship[3];
        
    }

    if (right == GLFW_PRESS) {
        shipRender = ship[1];

    }
    if (down == GLFW_PRESS) {
        shipRender = ship[0];

    }
    if (space == GLFW_PRESS) {
        inGame=false;
    }
    glDrawPixels(56,56,GL_RGBA,GL_UNSIGNED_BYTE,shipRender+138);


    //draw enemy

    //flyWithShip
    //glRasterPos2d(viewportpos[0]+position,viewportpos[1]+position);

    //flyWorld
    //glRasterPos2d(position,position);
//    glDrawPixels(56,56,GL_RGBA,GL_UNSIGNED_BYTE,ship[0]+138);


    //move viewport
    viewportpos[0] +=direction[0];
    viewportpos[1] +=direction[1];
    viewportpos[2] +=direction[0];
    viewportpos[3] +=direction[1];
}