//
// Created by basti on 11.12.2020.
//
#include "../../include/controller/Controller.h"

#include <iostream>

Controller::Controller() {

}

int Controller::init() {

    //init controller
    model = new Model();
    model->mines.push_back(new Mine(10,10));
    model->mines.push_back(new Mine(50,50));
    model->mines.push_back(new Mine(100,100));
    model->mines.push_back(new Mine(220,220));
    model->mines.push_back(new Mine(330,330));
    model->mines.push_back(new Mine(570,570));
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
    printf("init controller done\n");

    //load files

    loadSprites();


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


    viewportpos[0] +=direction[0];
    viewportpos[1] +=direction[1];
    viewportpos[2] +=direction[0];
    viewportpos[3] +=direction[1];
    //glBitmap(56,56,0,0,0,0,test+55);
    //GLubyte* cmon = test+138;
   // glDrawPixels(56,56,GL_RGBA,GL_UNSIGNED_BYTE,ship[0]+138);


}

void onStart(){

};

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
    glVertex3f(posxy[0],posxy[1]-300,0); // Der erste Eckpunkt ist mittig und 100 Pixel
    // vom oberen Rand entfernt

    glColor3f(0,1,0);      // Ab jetzt werden alle gezeichneten Punkte grün
    glVertex3f(posxy[0]-300,posxy[1]+300,0); // Der zweite Eckpunkt ist 50 Pixel vom rechten
    // und 100 Pixel vom unteren Rand entfernt

    glColor3f(0,0,1);      // Ab jetzt werden alle gezeichneten Punkte blau
    glVertex3f(posxy[0]+300,posxy[1]+300,0);  // Der dritte Eckpunkt ist 50 Pixel vom linken
    // und 100 Pixel vom unteren Rand entfernt
    glEnd();
    //posxy[0]+=direction[0];
    //posxy[1]+=direction[1];


    printf("vp0 min x %d\n", viewportpos[0]);
    printf("vp1 min y %d\n", viewportpos[1]);
    printf("vp2 max x %d\n", viewportpos[2]);
    printf("vp3 max y %d\n", viewportpos[3]);
    printf("bishier %s\n",Player::sprites[0][0]);

    //draw ship
    glRasterPos2d(viewportpos[0]+640,viewportpos[1]+360);

    if (up == GLFW_PRESS) {
        shipRender = Player::sprites[0][0];
        wihi[0] = *((uint32_t*)(myplayer->sprites[0][0]+18));
        wihi[1] = *((uint32_t*)(myplayer->sprites[0][0]+22));
    }
    if (left == GLFW_PRESS) {
        shipRender = myplayer->sprites[6][0];
        wihi[0] = *((uint32_t*)(myplayer->sprites[6][0]+18));
        wihi[1] = *((uint32_t*)(myplayer->sprites[6][0]+22));
    }

    if (right == GLFW_PRESS) {
        shipRender = myplayer->sprites[2][0];
        wihi[0] = *((uint32_t*)(myplayer->sprites[2][0]+18));
        wihi[1] = *((uint32_t*)(myplayer->sprites[2][0]+22));
    }
    if (down == GLFW_PRESS) {
        shipRender = myplayer->sprites[4][0];
        wihi[0] = *((uint32_t*)(myplayer->sprites[4][0]+18));
        wihi[1] = *((uint32_t*)(myplayer->sprites[4][0]+22));
    }
    if (space == GLFW_PRESS) {
        inGame=false;
    }

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc( GL_GREATER, 0.5 );
    glDrawPixels(wihi[0],wihi[1],GL_RGBA,GL_UNSIGNED_BYTE,shipRender+138);


    unsigned char* meinPixel = new unsigned char[4];
    meinPixel[0] = 255;
    meinPixel[1] = 0;
    meinPixel[2] = 0;
    meinPixel[3] = 255;

//    for (int pixelcount = 50; pixelcount >=0; pixelcount--){
//        int x = (rand() % 1280);
//        int y = (rand() % 720);
//        printf("x %d y %d\n",x,y);
//        glRasterPos2d(viewportpos[0]+x,viewportpos[1]+y);
//        glDrawPixels(64,64,GL_RGBA,GL_UNSIGNED_BYTE, Mine::sprites+138 );
//    }
    for(Mine* ele: model->mines) {
        glRasterPos2d(ele->posX,ele->posY);
        glDrawPixels(64,64,GL_RGBA,GL_UNSIGNED_BYTE, Mine::sprites+138 );
    }


    //move viewport
    viewportpos[0] +=direction[0];
    viewportpos[1] +=direction[1];
    viewportpos[2] +=direction[0];
    viewportpos[3] +=direction[1];
}
void Controller::loadSprites() {

    getSprite(Player::sprites[PlayerSprite::up][0],"../App_Data/ship_bmp/ship_up_light_off.bmp");
    getSprite(Player::sprites[PlayerSprite::up][1],"../App_Data/ship_bmp/ship_up_light_on.bmp");

    getSprite(Player::sprites[PlayerSprite::upright][1], "../App_Data/ship_bmp/ship_up_right_light_on.bmp");
    getSprite(Player::sprites[PlayerSprite::upright][0], "../App_Data/ship_bmp/ship_up_right_light_off.bmp");

    getSprite(Player::sprites[PlayerSprite::right][1], "../App_Data/ship_bmp/ship_right_light_on.bmp");
    getSprite(Player::sprites[PlayerSprite::right][0], "../App_Data/ship_bmp/ship_right_light_off.bmp");

    getSprite(Player::sprites[PlayerSprite::downright][1], "../App_Data/ship_bmp/ship_down_right_light_on.bmp");
    getSprite(Player::sprites[PlayerSprite::downright][0], "../App_Data/ship_bmp/ship_down_right_light_off.bmp");

    getSprite(Player::sprites[PlayerSprite::down][1], "../App_Data/ship_bmp/ship_down_light_on.bmp");
    getSprite(Player::sprites[PlayerSprite::down][0], "../App_Data/ship_bmp/ship_down_light_off.bmp");

    getSprite(Player::sprites[PlayerSprite::downleft][1], "../App_Data/ship_bmp/ship_down_left_light_on.bmp");
    getSprite(Player::sprites[PlayerSprite::downleft][0], "../App_Data/ship_bmp/ship_down_left_light_off.bmp");

    getSprite(Player::sprites[PlayerSprite::left][1], "../App_Data/ship_bmp/ship_left_light_on.bmp");
    getSprite(Player::sprites[PlayerSprite::left][0], "../App_Data/ship_bmp/ship_left_light_off.bmp");

    getSprite(Player::sprites[PlayerSprite::upleft][1], "../App_Data/ship_bmp/ship_up_left_light_on.bmp");
    getSprite(Player::sprites[PlayerSprite::upleft][0], "../App_Data/ship_bmp/ship_up_left_light_off.bmp");

    getSprite(Mine::sprites, "../App_Data/mine_bmp/mine.bmp");
    printf("machdochnichsidesn\n");
    getSprite(Mine::spritesExplosion[0], "../App_Data/mine_explosion_bmp/mine_explosion_1.bmp");
    getSprite(Mine::spritesExplosion[1], "../App_Data/mine_explosion_bmp/mine_explosion_1.bmp");
    getSprite(Mine::spritesExplosion[2], "../App_Data/mine_explosion_bmp/mine_explosion_1.bmp");

}
int Controller::getSprite(GLubyte* &dst, char* filepath) {
    int filesize;
    int swap;
    FILE* file = fopen(filepath, "r");
    fseek(file,0,SEEK_END);
    filesize = ftell(file);
    fseek(file,0,SEEK_SET);
    dst = new GLubyte[filesize];
    fread(dst, sizeof(GLubyte), filesize, file);

    for(int i = *((uint16_t*)(dst+10)); i < filesize; i+=4) {
        swap = dst[i];
        dst[i] = dst[i+2];
        dst[i+2] = swap;
    }

    fclose(file);
    return 0;
}

