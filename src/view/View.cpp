//
// Created by basti on 11.12.2020.
//
#include "../../include/view/View.h"


View::View(Model* modl){
    model = modl;
    viewportpos[0] = 0;
    viewportpos[1] = 0;
    viewportpos[2] = 1280;
    viewportpos[3] = 720;
}

int View::createMainWindow() {

    int width =  1280;
    int height = 720;
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
void View::prepareFrame() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport(0,0,1280,720);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc( GL_GREATER, 0.5 );
    glOrtho( viewportpos[0], viewportpos[2], viewportpos[3], viewportpos[1], -1, 1 );

}

void View::moveFrame() {
    viewportpos[0] +=model->player->direction[0] * model->player->playerspeed;
    viewportpos[1] +=model->player->direction[1] * model->player->playerspeed;
    viewportpos[2] +=model->player->direction[0] * model->player->playerspeed;
    viewportpos[3] +=model->player->direction[1] * model->player->playerspeed;
}



void View::render(Position2D pos, GLubyte *bitmap) {
    glRasterPos2d(pos.x, pos.y);
    glDrawPixels(*((uint32_t*)(bitmap+18)),*((uint32_t*)(bitmap+22)),GL_RGBA,GL_UNSIGNED_BYTE,bitmap+*((uint32_t*)(bitmap+10)));
}

void View::renderStars(Position2D pos, GLubyte *bitmap) {
    glRasterPos2d(pos.x, pos.y);
    glDrawPixels(2,2,GL_RGBA,GL_UNSIGNED_BYTE,bitmap);
}

void View::drawString(Position2D pos,char *input, GLubyte *bitmap) {
    int x = pos.x;
    int y = pos.y;
   while (*input!='\0'){
       switch(*input){
           case 'A':
               glRasterPos2d(x, y);
               glDrawPixels(64,64,GL_RGBA,GL_UNSIGNED_BYTE,bitmap);
               break;
           default :
               break;
       }
       x +=8;
       *input++;
    }

}

