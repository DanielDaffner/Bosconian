//
// Created by basti on 11.12.2020.
//
#include "../../include/view/View.h"


View::View(Model* modl){
    model = modl;
    viewportpos[0] = model->player->pos.x - (GAME_WIDTH/2);
    viewportpos[1] = model->player->pos.y - (GAME_HEIGHT/2);
    viewportpos[2] = model->player->pos.x + (GAME_WIDTH/2);
    viewportpos[3] = model->player->pos.y + (GAME_HEIGHT/2);
}

int View::createMainWindow() {

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(VIEW_WIDTH, VIEW_HEIGHT, "Bosconian", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
}
void View::prepareFrame() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc( GL_GREATER, 0.5 );
//    glOrtho( viewportpos[0], viewportpos[2], viewportpos[3], viewportpos[1], -1, 1 );
    glOrtho(0, VIEW_WIDTH, VIEW_HEIGHT, 0, -1, 1 );

}

void View::moveFrame() {
    viewportpos[0] +=model->player->direction[0] * model->player->playerspeed;
    viewportpos[1] +=model->player->direction[1] * model->player->playerspeed;
    viewportpos[2] +=model->player->direction[0] * model->player->playerspeed;
    viewportpos[3] +=model->player->direction[1] * model->player->playerspeed;
    if(viewportpos[0] < 0) viewportpos[0] += MAP_WIDTH;
    if(viewportpos[0] >= MAP_WIDTH)viewportpos[0] -= MAP_WIDTH;
    if(viewportpos[1] < 0)viewportpos[1] += MAP_HEIGHT;
    if(viewportpos[1] >= MAP_HEIGHT)viewportpos[1] -= MAP_HEIGHT;
    if(viewportpos[2] < 0)viewportpos[2] += MAP_WIDTH;
    if(viewportpos[2] >= MAP_WIDTH)viewportpos[2] -= MAP_WIDTH;
    if(viewportpos[3] < 0)viewportpos[3] += MAP_HEIGHT;
    if(viewportpos[3] >= MAP_HEIGHT)viewportpos[3] -= MAP_HEIGHT;
}
void View::resetFrame() {

    viewportpos[0] = model->player->pos.x - (GAME_WIDTH/2);
    viewportpos[1] = model->player->pos.y - (GAME_HEIGHT/2);
    viewportpos[2] = model->player->pos.x + (GAME_WIDTH/2);
    viewportpos[3] = model->player->pos.y + (GAME_HEIGHT/2);
}


//void View::render(Position2D pos, GLubyte *bitmap) {
//    int x = pos.x - viewportpos[0];
//    int y = pos.y - viewportpos[1];
//    glRasterPos2d(x, y);
//    glDrawPixels(*((uint32_t*)(bitmap+18)),*((uint32_t*)(bitmap+22)),GL_RGBA,GL_UNSIGNED_BYTE,bitmap+*((uint32_t*)(bitmap+10)));
//}

void View::render(Position2D pos, GLubyte *bitmap) {
    int x;
    int y;
    if(viewportpos[0] > viewportpos[2] || viewportpos[1] > viewportpos[3]) {
        if(viewportpos[0] > viewportpos[2] && viewportpos[1] > viewportpos[3]) {
            //4 teile
            if(viewportpos[0] <= pos.x && viewportpos[1] <= pos.y) {
                x = pos.x - viewportpos[0];
                y = pos.y - viewportpos[1];
            } else
            if(viewportpos[0] <= pos.x && viewportpos[3] >= pos.y) {
                x = pos.x - viewportpos[0];
                y = pos.y - viewportpos[3] + GAME_HEIGHT;
            } else
            if(viewportpos[2] >= pos.x && viewportpos[1] <= pos.y) {
                x = pos.x - viewportpos[2] + GAME_WIDTH;
                y = pos.y - viewportpos[1];
            } else
            if(viewportpos[2] >= pos.x && viewportpos[3] >= pos.y) {
                x = pos.x - viewportpos[2] + GAME_WIDTH;
                y = pos.y - viewportpos[3] + GAME_HEIGHT;
            } else return;
        } else if(viewportpos[0] > viewportpos[2]) {
            //2 teile links rechts
            if(viewportpos[0] <= pos.x) {
                x = pos.x - viewportpos[0];
                y = pos.y - viewportpos[1];
            } else if(viewportpos[2] >= pos.x ) {
                x = pos.x - viewportpos[2] + GAME_WIDTH;
                y = pos.y - viewportpos[1];
            } else return;
        } else {
            //2 teile oben unten
            if(viewportpos[1] <= pos.y) {
                x = pos.x - viewportpos[0];
                y = pos.y - viewportpos[1];
            } else if(viewportpos[3] >= pos.y) {
                x = pos.x - viewportpos[0];
                y = pos.y - viewportpos[3] + GAME_HEIGHT;
            } else return;
        }
    } else {
        x = pos.x - viewportpos[0];
        y = pos.y - viewportpos[1];
    }
    glRasterPos2i(x,y);
    glDrawPixels(*bitmap, *(bitmap + 1), GL_RGBA, GL_UNSIGNED_BYTE,
                 bitmap + 2);
}

void View::renderGameInfos(Position2D pos, GLubyte *bitmap) {
    glRasterPos2d(pos.x, pos.y);
    glDrawPixels(*((uint8_t*)(bitmap)),*((uint8_t*)(bitmap+1)),GL_RGBA,GL_UNSIGNED_BYTE,bitmap+2);
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
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[0]+2);
               x +=32;
               break;
           case 'B':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[1]+2);
               x +=32;
               break;
           case 'C':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[2]+2);
               x +=32;
               break;
           case 'D':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[3]+2);
               x +=32;
               break;
           case 'E':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[4]+2);
               x +=32;
               break;
           case 'F':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[5]+2);
               x +=32;
               break;
           case 'G':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[6]+2);
               x +=32;
               break;
           case 'H':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[7]+2);
               x +=32;
               break;
           case 'I':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[8]+2);
               x +=32;
               break;
           case 'J':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[9]+2);
               x +=32;
               break;
           case 'K':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[10]+2);
               x +=32;
               break;
           case 'L':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[11]+2);
               x +=32;
               break;
           case 'M':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[12]+2);
               x +=32;
               break;
           case 'N':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[13]+2);
               x +=32;
               break;
           case 'O':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[14]+2);
               x +=32;
               break;
           case 'P':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[15]+2);
               x +=32;
               break;
           case 'Q':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[16]+2);
               x +=32;
               break;
           case 'R':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[17]+2);
               x +=32;
               break;
           case 'S':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[18]+2);
               x +=32;
               break;
           case 'T':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[19]+2);
               x +=32;
               break;
           case 'U':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[20]+2);
               x +=32;
               break;
           case 'V':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[21]+2);
               x +=32;
               break;
           case 'W':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[22]+2);
               x +=32;
               break;
           case 'X':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[23]+2);
               x +=32;
               break;
           case 'Y':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[24]+2);
               x +=32;
               break;
           case 'Z':
               glRasterPos2d(x, y);
               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[25]+2);
               x +=32;
               break;
           default :
               x +=16;
               break;
       }
       *input++;
    }

}

