//
// Created by basti on 11.12.2020.
//
#include "../../include/controller/Controller.h"
#include <iostream>

Controller::Controller() {

}




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
    view = new View();
    printf("init controller done\n");

    //load files

    loadBitmapsShip();
    shipRender = ship[2][0];

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
   // glDrawPixels(56,56,GL_RGBA,GL_UNSIGNED_BYTE,ship[0]+138);


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
        shipRender = ship[2][0];
    }
    if (left == GLFW_PRESS) {
        shipRender = ship[3][0];

    }

    if (right == GLFW_PRESS) {
        shipRender = ship[1][0];

    }
    if (down == GLFW_PRESS) {
        shipRender = ship[0][0];

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
void Controller::loadBitmapsShip() {
    //open files
    printf("bitmapsShip begin\n");

    //need static list or something to get this from
    //scam

    printf("names\n");

    char* names[8][2] = {
            {
                    "ship_up_light_on.bmp" ,
                    "ship_up_light_off.bmp"
            },
            {
                    "ship_up_right_light_on.bmp" ,
                    "ship_up_right_light_off.bmp"
            },
            {
                    "ship_right_light_on.bmp" ,
                    "ship_right_light_off.bmp"
            },
            {
                    "ship_down_right_light_on.bmp" ,
                    "ship_down_right_light_off.bmp"
            },
            {
                    "ship_down_light_on.bmp" ,
                    "ship_down_light_off.bmp"
            },
            {
                    "ship_down_left_light_on.bmp" ,
                    "ship_down_left_light_off.bmp"
            },
            {
                    "ship_left_light_on.bmp" ,
                    "ship_left_light_off.bmp"
            },
            {
                    "ship_up_left_light_on.bmp" ,
                    "ship_up_left_light_off.bmp"
            }
    };


    //path
    char* basePath = "../App_Data/";

    //load all files
    for (size_t x = 0; x < sizeof(names)/sizeof(*names); ++x) {


        printf("\n\n %d \n\n", sizeof(names)/sizeof(*names));
        printf("\n\n %d \n\n", sizeof(names[x])/sizeof(*names[x]));
        for (size_t y = 0; y < sizeof(names[x])/sizeof(*names[x]); ++y) {
            //getPath
            std::string path = std::string(basePath) + names[x][y];
            printf("%s", path.c_str());
            //loadFile
            FILE* file = fopen(path.c_str(), "r");
            if (file == nullptr) printf("file %s null\n", path.c_str());
            //check length
            int bmLength = getBitmapLength(file);
            printf("bmlength %d", bmLength);
            //set bitmap
            GLubyte* scam = new GLubyte[bmLength];
            printf("check");
            //error peter
            fread(scam, sizeof(GLubyte), bmLength, file);

            printf("check\n");
            ship[x][y] = scam;
            int intTMP = *((uint16_t*)(ship[x][y]+10));

            //print bitmap header
            printf("printBitmapHeader");
            printf(" %u\n",*((uint32_t*)(ship[x][y]+30)));
            printf(" %u\n",*((uint32_t*)(ship[x][y]+14)));
            printf(" %u\n",*((uint32_t*)(ship[x][y]+22)));
            printf(" %u\n",*((uint16_t*)(ship[x][y]+28)));
            printf(" %u\n",*((uint16_t*)(ship[x][y]+50)));
            printf(" %u\n",*((uint16_t*)(ship[x][y]+10)));

            GLubyte swap=0;
            for(int i = intTMP; i < bmLength; i+=4) {
                swap = ship[x][y][i];
                ship[x][y][i] = ship[x][y][i+2];
                ship[x][y][i+2] = swap;
            }
            fclose(file);
        }

    }
}

int Controller::getBitmapLength(FILE* tmp){
    fseek(tmp,0,SEEK_END);
    int result = ftell(tmp);
    return result;
}