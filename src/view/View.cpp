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
void View::resetFrame() {

    viewportpos[0] =0;
    viewportpos[1] =0;
    viewportpos[2] =1280;
    viewportpos[3] =720;
}


void View::render(Position2D pos, GLubyte *bitmap) {
    glRasterPos2d(pos.x, pos.y);
    glDrawPixels(*((uint32_t*)(bitmap+18)),*((uint32_t*)(bitmap+22)),GL_RGBA,GL_UNSIGNED_BYTE,bitmap+*((uint32_t*)(bitmap+10)));
}

void View::renderStars(Position2D pos, GLubyte *bitmap) {
    glRasterPos2d(pos.x, pos.y);
    glDrawPixels(2,2,GL_RGBA,GL_UNSIGNED_BYTE,bitmap);
}

void View::drawString(Position2D pos,char *input) {
    int x = pos.x;
    int y = pos.y;
   while (*input!='\0'){
       switch(*input){
           case 'A':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[0]+138);
               x +=32;
               break;
           case 'B':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[1]+138);
               x +=32;
               break;
           case 'C':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[2]+138);
               x +=32;
               break;
           case 'D':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[3]+138);
               x +=32;
               break;
           case 'E':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[4]+138);
               x +=32;
               break;
           case 'F':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[5]+138);
               x +=32;
               break;
           case 'G':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[6]+138);
               x +=32;
               break;
           case 'H':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[7]+138);
               x +=32;
               break;
           case 'I':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[8]+138);
               x +=32;
               break;
           case 'J':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[9]+138);
               x +=32;
               break;
           case 'K':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[10]+138);
               x +=32;
               break;
           case 'L':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[11]+138);
               x +=32;
               break;
           case 'M':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[12]+138);
               x +=32;
               break;
           case 'N':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[13]+138);
               x +=32;
               break;
           case 'O':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[14]+138);
               x +=32;
               break;
           case 'P':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[15]+138);
               x +=32;
               break;
           case 'Q':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[16]+138);
               x +=32;
               break;
           case 'R':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[17]+138);
               x +=32;
               break;
           case 'S':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[18]+138);
               x +=32;
               break;
           case 'T':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[19]+138);
               x +=32;
               break;
           case 'U':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[20]+138);
               x +=32;
               break;
           case 'V':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[21]+138);
               x +=32;
               break;
           case 'W':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[22]+138);
               x +=32;
               break;
           case 'X':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[23]+138);
               x +=32;
               break;
           case 'Y':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[24]+138);
               x +=32;
               break;
           case 'Z':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[25]+138);
               x +=32;
               break;
           default :
               x +=16;
               break;
       }
       *input++;
    }

}

