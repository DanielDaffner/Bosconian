//
// Created by basti on 11.12.2020.
//
#include "../../include/view/View.h"
#include <string>


View::View(Model* modl){
    model = modl;
    viewportpos[0] = model->player->pos.x - (GAME_WIDTH/2);
    viewportpos[1] = model->player->pos.y - (GAME_HEIGHT/2)-64;
    viewportpos[2] = model->player->pos.x + (GAME_WIDTH/2);
    viewportpos[3] = model->player->pos.y + (GAME_HEIGHT/2)-64;
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
   double normalize = sqrt(pow(model->player->direction[0],2)+pow(model->player->direction[1],2));

    viewportpos[0] +=(model->player->direction[0] /normalize)* model->player->playerspeed;
    viewportpos[1] +=(model->player->direction[1]  /normalize)* model->player->playerspeed;
    viewportpos[2] +=(model->player->direction[0]  /normalize)* model->player->playerspeed;
    viewportpos[3] +=(model->player->direction[1]  /normalize)* model->player->playerspeed;
//    viewportpos[0] = model->player->pos.x - (GAME_WIDTH/2);
//    viewportpos[1] = model->player->pos.y - (GAME_HEIGHT/2);
//    viewportpos[2] = model->player->pos.x + (GAME_WIDTH/2);
//    viewportpos[3] = model->player->pos.y + (GAME_HEIGHT/2);
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
    viewportpos[1] = model->player->pos.y - (GAME_HEIGHT/2)-64;
    viewportpos[2] = model->player->pos.x + (GAME_WIDTH/2);
    viewportpos[3] = model->player->pos.y + (GAME_HEIGHT/2)-64;
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
    glDrawPixels(*((uint32_t*)(bitmap)),*((uint32_t*)(bitmap+4)), GL_RGBA, GL_UNSIGNED_BYTE,
                 bitmap + 8);
}

void View::renderGameInfos(Position2D pos, GLubyte *bitmap) {
    glRasterPos2d(pos.x, pos.y);
    glDrawPixels(*((uint32_t*)(bitmap)),*((uint32_t*)(bitmap+4)),GL_RGBA,GL_UNSIGNED_BYTE,bitmap+8);
}

void View::renderStars(Position2D pos, GLubyte *bitmap) {
    glRasterPos2d(pos.x, pos.y);
    glDrawPixels(2,2,GL_RGBA,GL_UNSIGNED_BYTE,bitmap);
}

void View::drawString(Position2D pos,char *input) {
    int x = pos.x;
    int y = pos.y;
   while (*input!='\0'){
       glRasterPos2d(x, y);
       switch(*input){
           case 'A':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[0]+2);
               x +=32;
               break;
           case 'B':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[1]+2);
               x +=32;
               break;
           case 'C':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[2]+2);
               x +=32;
               break;
           case 'D':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[3]+2);
               x +=32;
               break;
           case 'E':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[4]+2);
               x +=32;
               break;
           case 'F':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[5]+2);
               x +=32;
               break;
           case 'G':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[6]+2);
               x +=32;
               break;
           case 'H':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[7]+2);
               x +=32;
               break;
           case 'I':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[8]+2);
               x +=32;
               break;
           case 'J':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[9]+2);
               x +=32;
               break;
           case 'K':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[10]+2);
               x +=32;
               break;
           case 'L':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[11]+2);
               x +=32;
               break;
           case 'M':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[12]+2);
               x +=32;
               break;
           case 'N':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[13]+2);
               x +=32;
               break;
           case 'O':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[14]+2);
               x +=32;
               break;
           case 'P':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[15]+2);
               x +=32;
               break;
           case 'Q':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[16]+2);
               x +=32;
               break;
           case 'R':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[17]+2);
               x +=32;
               break;
           case 'S':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[18]+2);
               x +=32;
               break;
           case 'T':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[19]+2);
               x +=32;
               break;
           case 'U':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[20]+2);
               x +=32;
               break;
           case 'V':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[21]+2);
               x +=32;
               break;
           case 'W':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[22]+2);
               x +=32;
               break;
           case 'X':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[23]+2);
               x +=32;
               break;
           case 'Y':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[24]+2);
               x +=32;
               break;
           case 'Z':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[25]+2);
               x +=32;
               break;
           case '-':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetWhite[28]+2);
               x +=32;
               break;
           case '0':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[0]+2);
               x +=32;
               break;
           case '1':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[1]+2);
               x +=32;
               break;
           case '2':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[2]+2);
               x +=32;
               break;
           case '3':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[3]+2);
               x +=32;
               break;
           case '4':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[4]+2);
               x +=32;
               break;
           case '5':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[5]+2);
               x +=32;
               break;
           case '6':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[6]+2);
               x +=32;
               break;
           case '7':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[7]+2);
               x +=32;
               break;
           case '8':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[8]+2);
               x +=32;
               break;
           case '9':

               glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[0]+2);
               x +=32;
               break;
           default :
               x +=16;
               break;
       }
       *input++;
    }

}

//void View::drawStringBlackNoBorder(Position2D pos,char *input) {
//    int x = pos.x;
//    int y = pos.y;
//    while (*input!='\0'){
//        glRasterPos2d(x, y);
//        switch(*input){
//            case 'A':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[0]+2);
//                x +=32;
//                break;
//            case 'B':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[1]+2);
//                x +=32;
//                break;
//            case 'C':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[2]+2);
//                x +=32;
//                break;
//            case 'D':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[3]+2);
//                x +=32;
//                break;
//            case 'E':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[4]+2);
//                x +=32;
//                break;
//            case 'F':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[5]+2);
//                x +=32;
//                break;
//            case 'G':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[6]+2);
//                x +=32;
//                break;
//            case 'H':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[7]+2);
//                x +=32;
//                break;
//            case 'I':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[8]+2);
//                x +=32;
//                break;
//            case 'J':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[9]+2);
//                x +=32;
//                break;
//            case 'K':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[10]+2);
//                x +=32;
//                break;
//            case 'L':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[11]+2);
//                x +=32;
//                break;
//            case 'M':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[12]+2);
//                x +=32;
//                break;
//            case 'N':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[13]+2);
//                x +=32;
//                break;
//            case 'O':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[14]+2);
//                x +=32;
//                break;
//            case 'P':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[15]+2);
//                x +=32;
//                break;
//            case 'Q':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[16]+2);
//                x +=32;
//                break;
//            case 'R':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[17]+2);
//                x +=32;
//                break;
//            case 'S':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[18]+2);
//                x +=32;
//                break;
//            case 'T':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[19]+2);
//                x +=32;
//                break;
//            case 'U':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[20]+2);
//                x +=32;
//                break;
//            case 'V':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[21]+2);
//                x +=32;
//                break;
//            case 'W':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[22]+2);
//                x +=32;
//                break;
//            case 'X':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[23]+2);
//                x +=32;
//                break;
//            case 'Y':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[24]+2);
//                x +=32;
//                break;
//            case 'Z':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[25]+2);
//                x +=32;
//                break;
//            case '-':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[28]+2);
//                x +=32;
//                break;
//            case '0':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[0]+2);
//                x +=32;
//                break;
//            case '1':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[1]+2);
//                x +=32;
//                break;
//            case '2':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[2]+2);
//                x +=32;
//                break;
//            case '3':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[3]+2);
//                x +=32;
//                break;
//            case '4':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[4]+2);
//                x +=32;
//                break;
//            case '5':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[5]+2);
//                x +=32;
//                break;
//            case '6':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[6]+2);
//                x +=32;
//                break;
//            case '7':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[7]+2);
//                x +=32;
//                break;
//            case '8':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[8]+2);
//                x +=32;
//                break;
//            case '9':
//
//                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::alphabetBlackNoBorder[0]+2);
//                x +=32;
//                break;
//            default :
//                x +=16;
//                break;
//        }
//        *input++;
//    }
//
//}

void View::drawNumber(Position2D pos,int number) {
    char* input = new char[std::to_string(number).length()];
    strcpy(input , std::to_string(number).c_str());
    int x = pos.x- 32*(std::to_string(number).length()-1) ;
    int y = pos.y;
    while (*input!='\0'){
        switch(*input){
            case '0':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[0]+2);
                x +=32;
                break;
            case '1':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[1]+2);
                x +=32;
                break;
            case '2':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[2]+2);
                x +=32;
                break;
            case '3':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[3]+2);
                x +=32;
                break;
            case '4':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[4]+2);
                x +=32;
                break;
            case '5':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[5]+2);
                x +=32;
                break;
            case '6':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[6]+2);
                x +=32;
                break;
            case '7':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[7]+2);
                x +=32;
                break;
            case '8':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[8]+2);
                x +=32;
                break;
            case '9':
                glRasterPos2d(x, y);
                glDrawPixels(32,32,GL_RGBA,GL_UNSIGNED_BYTE,Model::numbers[9]+2);
                x +=32;
                break;
            default :
                x +=16;
                break;
        }
        *input++;
    }

}
