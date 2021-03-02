//
// Created by basti on 11.12.2020.
//
#include "../../include/view/View.h"
#include <string>


View::View(Model* modl){
    model = modl;
    backgroundmove = false;
    loadSprites();
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
void View::update(bool &inGame)  {

    //    render exploding mines
    for(auto iterator = model->minesExploding.begin(); iterator!= model->minesExploding.end();) {
        render(iterator._Ptr->_Myval->pos + Mine::drawOffset,mineSpritesExplosion[iterator._Ptr->_Myval->explosionPhase/10]);
        iterator._Ptr->_Myval->explosionPhase++;
        if(iterator._Ptr->_Myval->explosionPhase >= 30) {
            delete (iterator._Ptr->_Myval);
            iterator = model->minesExploding.erase(iterator);
            model->player->score += Mine::score;
        }else
            iterator++;
    }

    //render exploding iTypeMissile
    double normalize = 0;
    for(auto iterator = model->iTypeMissilesExploding.begin(); iterator!= model->iTypeMissilesExploding.end();) {
        if( iterator._Ptr->_Myval->explosionPhase++!=0){
            normalize = sqrt((pow(ITypeMissile::directions[iterator._Ptr->_Myval->direction][0],2)+pow(ITypeMissile::directions[iterator._Ptr->_Myval->direction][1],2)));
            iterator._Ptr->_Myval->pos.x += (ITypeMissile::directions[iterator._Ptr->_Myval->direction][0] / normalize) * ITypeMissile::speed;
            iterator._Ptr->_Myval->pos.y += (ITypeMissile::directions[iterator._Ptr->_Myval->direction][1] / normalize) * ITypeMissile::speed;
            if(iterator._Ptr->_Myval->pos.x < 0) iterator._Ptr->_Myval->pos.x += MAP_WIDTH;
            if(iterator._Ptr->_Myval->pos.x >= MAP_WIDTH)iterator._Ptr->_Myval->pos.x -= MAP_WIDTH;
            if(iterator._Ptr->_Myval->pos.y < 0)iterator._Ptr->_Myval->pos.y += MAP_HEIGHT;
            if(iterator._Ptr->_Myval->pos.y >= MAP_HEIGHT)iterator._Ptr->_Myval->pos.y -= MAP_HEIGHT;
        }
        render(iterator._Ptr->_Myval->pos + EnemyShip::drawOffset,enemyShipSpritesExplosion[iterator._Ptr->_Myval->explosionPhase/10]);
        iterator._Ptr->_Myval->explosionPhase++;
        if(iterator._Ptr->_Myval->explosionPhase >= 30) {
            delete (iterator._Ptr->_Myval);
            iterator = model->iTypeMissilesExploding.erase(iterator);
            model->player->score+=ITypeMissile::score;
        }else
            iterator++;
    }


//    render mines
    for(Mine* ele: model->mines) {
        render(ele->pos + Mine::drawOffset, minesSprite);
    }

//    render projectiles from player
    for(ProjectilePlayer* ele: model->projectilesPlayer) {
        render(ele->pos + ProjectilePlayer::drawOffset, playerProjectileSprites[ele->spritedirection]);
    }

    //render enemy
    for(ITypeMissile* ele: model->iTypeMissiles) {
        render(ele->pos + EnemyShip::drawOffset, enemyShipSprites[0][ele->direction]);
    }


//    render player
    if(model->player->collision) {
        render(model->player->pos + Player::drawOffset,
                     playerSpritesExplosion[model->player->spriteLight/10]);
        if(model->player->spriteLight++ == 29) {
            if(model->player->lifes == 0) {
                drawString(Position2D{VIEW_WIDTH/2-(4*32+8),GAME_HEIGHT/2-32},"GAME OVER");
                inGame=false;
                model->player->collision = false;
                glfwSwapBuffers(window);
                model->player->resetPosition();
                resetFrame();
                _sleep(2000);
                glClear(GL_COLOR_BUFFER_BIT);
                return;
            }
            model->player->collision = false;
            model->player->spriteLight = 0;
            model->player->lifes--;
            model->player->resetPosition();
            resetFrame();
        }
    } else {
        render(model->player->pos + Player::drawOffset,playerSprites[model->player->spriteDirection][model->player->spriteLight]);
        if(count%30 == 0) {
            model->player->spriteLight = (model->player->spriteLight + 1) % 2;
        }
    }
    double playerDirectionVectorLenght = sqrt((pow(model->player->direction[0],2)+pow(model->player->direction[1],2)));
    //    render background
    for(BackgroundPixel* ele: model->pixelarr[(count/30)]) {
        if(backgroundmove){
            ele->pos.x -= (model->player->direction[0] / playerDirectionVectorLenght) * 4;
            ele->pos.y -= (model->player->direction[1] / playerDirectionVectorLenght) * 4;

        }
        renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    for(BackgroundPixel* ele: model->pixelarr[((count/30)+1)%3]) {
        if(backgroundmove){
            ele->pos.x -= (model->player->direction[0] / playerDirectionVectorLenght) * 4;
            ele->pos.y -= (model->player->direction[1] / playerDirectionVectorLenght) * 4;

        }
        renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    count++;
    count = count % 119;
    if(backgroundmove) {
        backgroundmove = false;
    }
    else {
        backgroundmove = true;
    }

//    render Base
    for(EnemyBase* ele: model->enemyBases) {
//        glDrawPixels(*EnemyBase::sprites[0],*(EnemyBase::sprites[0]+4),GL_RGBA,GL_UNSIGNED_BYTE,EnemyBase::sprites[0]+8);
//        glDrawPixels(*((uint32_t *)(EnemyBase::sprites[0])),*((uint32_t *)(EnemyBase::sprites[0]+4)),GL_RGBA,GL_UNSIGNED_BYTE,EnemyBase::sprites[0]+8);
        if(ele->isOpen) {
//            view->render(ele->pos + EnemyBase::drawOffset, EnemyBase::sprites[0]);

        } else {
//            view->render(ele->pos + EnemyBase::drawOffset, EnemyBase::sprites[0]);
        }
        for(EnemyBasePart* ele2: ele->parts) {
//            view->render(ele2->pos+Player::drawOffset,EnemyBase::sprites[0]);
        }
        printf("%f %f\n",ele->pos.x,ele->pos.y);
    }

//    move Formation
    for(Formation* ele: model->formations) {
        ele->pos = ele->pos + Position2D{5,0};
        if(ele->pos.x < 0) ele->pos.x += MAP_WIDTH;
        if(ele->pos.x >= MAP_WIDTH)ele->pos.x -= MAP_WIDTH;
        if(ele->pos.y < 0)ele->pos.y += MAP_HEIGHT;
        if(ele->pos.y >= MAP_HEIGHT)ele->pos.y -= MAP_HEIGHT;
        int i = 0;
        for(GameObject* ele2: ele->follower) {
            ele2->pos = ele->pos + (Formation::formationOffset[ele->formationType][i++] * 64);
            if(ele2->pos.x < 0) ele2->pos.x += MAP_WIDTH;
            if(ele2->pos.x >= MAP_WIDTH)ele2->pos.x -= MAP_WIDTH;
            if(ele2->pos.y < 0)ele2->pos.y += MAP_HEIGHT;
            if(ele2->pos.y >= MAP_HEIGHT)ele2->pos.y -= MAP_HEIGHT;
        }
    }
//  render Formation
    for(Formation* ele: model->formations) {
        render(ele->pos,enemyShipLeaderSprites[ele->formationMissile][ele->dir]);
        for(GameObject* ele2: ele->follower) {
            render(ele2->pos,enemyShipSprites[ele->formationMissile][ele->dir]);
        }
    }

//    draw background right side
    glColor3f(0, 0, 0);
    glRectd(VIEW_WIDTH-8*32,0,VIEW_WIDTH,VIEW_HEIGHT);

    //    draw map
//    view->renderGameInfos(Position2D{1280-300,300},Model::map);
    glRasterPos2d(MAP_POS_X,MAP_POS_Y);
    glDrawPixels(256,400,GL_RGBA,GL_UNSIGNED_BYTE,map);
    double x = model->player->pos.x /10;
    double y = model->player->pos.y /12.8;
    GLubyte testpix[4] = {255,255,255,255};
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);
    for(ITypeMissile* ele: model->iTypeMissiles) {
        x = ele->pos.x /10;
        y = ele->pos.y /12.8;
        glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
        glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);
    }
//    draw lifes
    for(int i = 0; i < model->player->lifes; i++) {
        renderGameInfos(Position2D{(double)LIFES_POS_X + (i * 64), LIFES_POS_Y}, playerSprites[0][0]);
    }

//    bases in map
    GLubyte* greenpix = new GLubyte(4);
    greenpix[0] = 0;
    greenpix[0] = 255;
    greenpix[0] = 0;
    greenpix[0] = 0;
    for(EnemyBase* ele: model->enemyBases) {
        x = ele->pos.x /10;
        y = ele->pos.y /12.8;
        glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
        glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,greenpix);
        glRasterPos2d(MAP_POS_X+x+1,MAP_POS_Y-400+y);
        glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,greenpix);
        glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y+1);
        glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,greenpix);
        glRasterPos2d(MAP_POS_X+x+1,MAP_POS_Y-400+y+1);
        glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,greenpix);
    }
    for(Formation* ele: model->formations) {
        x = ele->pos.x /10;
        y = ele->pos.y /12.8;
        glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
        glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,greenpix);
        glRasterPos2d(MAP_POS_X+x+1,MAP_POS_Y-400+y);
        glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,greenpix);
        glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y+1);
        glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,greenpix);
        glRasterPos2d(MAP_POS_X+x+1,MAP_POS_Y-400+y+1);
        glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,greenpix);
    }

//    testviewpos
    x = viewportpos[0] /10;
    y = viewportpos[1] /13;
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);
    x = viewportpos[2] /10;
    y = viewportpos[1] /13;
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);
    x = viewportpos[0] /10;
    y = viewportpos[3] /13;
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);
    x = viewportpos[2] /10;
    y = viewportpos[3] /13;
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);

//    draw round
    Position2D roundpos = {ROUND_POS_X,ROUND_POS_Y};
    drawString(roundpos,"ROUND 1");
//    set highscore
    if(model->highScore<model->player->score)
        model->highScore = model->player->score;
//    draw highscore
    Position2D highscorePos = {VIEW_WIDTH-(8*32),0+8+32};
    drawString(highscorePos,"HI-SCORE");
    Position2D highScorePos = {VIEW_WIDTH-32,0+8+32+32};
    drawNumber(highScorePos,model->highScore);
    Position2D oneUp = {VIEW_WIDTH-(6*32),0+8+32+32+32};
    drawString(oneUp,"1UP");
    Position2D scorePos = {VIEW_WIDTH-32,0+8+32+32+64};
    drawNumber(scorePos,model->player->score);
    Position2D conditionPos = {VIEW_WIDTH-9*32,0+8+32+32+7*32};
    drawString(conditionPos,"CONDITION");
    glColor3f(0, 1, 0);
    glRectd(VIEW_WIDTH-8*32,0+8+32+32+7*32+16,VIEW_WIDTH,0+8+32+32+7*32+16+32+16);
    Position2D conditionTypePos = {VIEW_WIDTH-6*32-16,0+8+32+32+7*32+16+32+8};
    drawString(conditionTypePos,"GREEN");
    glRasterPos2d(400,400);

}

void View::updateMainwindow() {
    prepareFrame();

    Position2D posString1{};
    posString1.x=448;
    posString1.y=500;
    //scam, should have own var
    if((count/60)%2==1)

        drawString(posString1,"PRESS SPACE BAR");

    Position2D posPlayer = {640,360};
    render(posPlayer,Player::sprites[0][0]);

    //Background
    for(BackgroundPixel* ele: model->pixelarr[(count/30)]) {
        renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    for(BackgroundPixel* ele: model->pixelarr[((count/30)+1)%3]) {
        renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    count++;
    count = count % 119;
    if(backgroundmove){
        backgroundmove=false;
    }
    else{
        backgroundmove=true;
    }

    render(enemyPos, enemyShipSprites[0][15]);
    enemyPos.x+=2;
    enemyPos.y+=2;
    if(enemyPos.y >=730) enemyPos = {-300,100};
}

void View::loadSprites() {

//    Lives
    loadSprite(lives,"../App_Data/lives_final/lives.bmp");


//    Player
    loadSprite(playerSprites[SpriteDirection::up][0],"../App_Data/ship_final/ship_up_light_off.bmp");
    loadSprite(playerSprites[SpriteDirection::up][1],"../App_Data/ship_final/ship_up_light_on.bmp");

    loadSprite(playerSprites[SpriteDirection::upright][1], "../App_Data/ship_final/ship_up_right_light_on.bmp");
    loadSprite(playerSprites[SpriteDirection::upright][0], "../App_Data/ship_final/ship_up_right_light_off.bmp");

    loadSprite(playerSprites[SpriteDirection::right][1], "../App_Data/ship_final/ship_right_light_on.bmp");
    loadSprite(playerSprites[SpriteDirection::right][0], "../App_Data/ship_final/ship_right_light_off.bmp");

    loadSprite(playerSprites[SpriteDirection::downright][1], "../App_Data/ship_final/ship_down_right_light_on.bmp");
    loadSprite(playerSprites[SpriteDirection::downright][0], "../App_Data/ship_final/ship_down_right_light_off.bmp");

    loadSprite(playerSprites[SpriteDirection::down][1], "../App_Data/ship_final/ship_down_light_on.bmp");
    loadSprite(playerSprites[SpriteDirection::down][0], "../App_Data/ship_final/ship_down_light_off.bmp");

    loadSprite(playerSprites[SpriteDirection::downleft][1], "../App_Data/ship_final/ship_down_left_light_on.bmp");
    loadSprite(playerSprites[SpriteDirection::downleft][0], "../App_Data/ship_final/ship_down_left_light_off.bmp");

    loadSprite(playerSprites[SpriteDirection::left][1], "../App_Data/ship_final/ship_left_light_on.bmp");
    loadSprite(playerSprites[SpriteDirection::left][0], "../App_Data/ship_final/ship_left_light_off.bmp");

    loadSprite(playerSprites[SpriteDirection::upleft][1], "../App_Data/ship_final/ship_up_left_light_on.bmp");
    loadSprite(playerSprites[SpriteDirection::upleft][0], "../App_Data/ship_final/ship_up_left_light_off.bmp");

//    Player explosion
    loadSprite(playerSpritesExplosion[0], "../App_Data/ship_explosion_final/ship-explosion-1.bmp");
    loadSprite(playerSpritesExplosion[1], "../App_Data/ship_explosion_final/ship-explosion-2.bmp");
    loadSprite(playerSpritesExplosion[2], "../App_Data/ship_explosion_final/ship-explosion-3.bmp");

//    Mine and explosion
    loadSprite(minesSprite, "../App_Data/mine_final/mine.bmp");
    loadSprite(mineSpritesExplosion[0], "../App_Data/mine_explosion_final/mine_explosion_1.bmp");
    loadSprite(mineSpritesExplosion[1], "../App_Data/mine_explosion_final/mine_explosion_2.bmp");
    loadSprite(mineSpritesExplosion[2], "../App_Data/mine_explosion_final/mine_explosion_3.bmp");

//    asteriods and explosion
    loadSprite(asteroidsSprites[0], "../App_Data/asteroid_final/asteroid_1.bmp");
    loadSprite(asteroidsSprites[1], "../App_Data/asteroid_final/asteroid_2.bmp");
    loadSprite(asteroidsSprites[2], "../App_Data/asteroid_final/asteroid_3.bmp");
    loadSprite(asteroidsSpritesExplosion[0], "../App_Data/asteroid_explosion_final/asteroid_explosion_1.bmp");
    loadSprite(asteroidsSpritesExplosion[1], "../App_Data/asteroid_explosion_final/asteroid_explosion_2.bmp");
    loadSprite(asteroidsSpritesExplosion[2], "../App_Data/asteroid_explosion_final/asteroid_explosion_3.bmp");
//    Projectile
    loadSprite(playerProjectileSprites[0], "../App_Data/projectile_final/projectile-1.bmp");
    loadSprite(playerProjectileSprites[1], "../App_Data/projectile_final/projectile-4.bmp");
    loadSprite(playerProjectileSprites[2], "../App_Data/projectile_final/projectile-3.bmp");
    loadSprite(playerProjectileSprites[3], "../App_Data/projectile_final/projectile-2.bmp");

//    enemy Explosion
    loadSprite(enemyShipSpritesExplosion[0], "../App_Data/enemy_explosion_final/enemy-explosion-1.bmp");
    loadSprite(enemyShipSpritesExplosion[1], "../App_Data/enemy_explosion_final/enemy-explosion-2.bmp");
    loadSprite(enemyShipSpritesExplosion[2], "../App_Data/enemy_explosion_final/enemy-explosion-3.bmp");

//    enemyPink
    loadSprite(enemyShipSprites[0][0], "../App_Data/enemy_pink_final/enemy-pink-1.bmp");
    loadSprite(enemyShipSprites[0][1], "../App_Data/enemy_pink_final/enemy-pink-2.bmp");
    loadSprite(enemyShipSprites[0][2], "../App_Data/enemy_pink_final/enemy-pink-3.bmp");
    loadSprite(enemyShipSprites[0][3], "../App_Data/enemy_pink_final/enemy-pink-4.bmp");
    loadSprite(enemyShipSprites[0][4], "../App_Data/enemy_pink_final/enemy-pink-5.bmp");
    loadSprite(enemyShipSprites[0][5], "../App_Data/enemy_pink_final/enemy-pink-6.bmp");
    loadSprite(enemyShipSprites[0][6], "../App_Data/enemy_pink_final/enemy-pink-7.bmp");
    loadSprite(enemyShipSprites[0][7], "../App_Data/enemy_pink_final/enemy-pink-8.bmp");
    loadSprite(enemyShipSprites[0][8], "../App_Data/enemy_pink_final/enemy-pink-9.bmp");
    loadSprite(enemyShipSprites[0][9], "../App_Data/enemy_pink_final/enemy-pink-10.bmp");
    loadSprite(enemyShipSprites[0][10], "../App_Data/enemy_pink_final/enemy-pink-11.bmp");
    loadSprite(enemyShipSprites[0][11], "../App_Data/enemy_pink_final/enemy-pink-12.bmp");
    loadSprite(enemyShipSprites[0][12], "../App_Data/enemy_pink_final/enemy-pink-13.bmp");
    loadSprite(enemyShipSprites[0][13], "../App_Data/enemy_pink_final/enemy-pink-14.bmp");
    loadSprite(enemyShipSprites[0][14], "../App_Data/enemy_pink_final/enemy-pink-15.bmp");
    loadSprite(enemyShipSprites[0][15], "../App_Data/enemy_pink_final/enemy-pink-16.bmp");
    loadSprite(enemyShipSprites[0][16], "../App_Data/enemy_pink_final/enemy-pink-17.bmp");
    loadSprite(enemyShipSprites[0][17], "../App_Data/enemy_pink_final/enemy-pink-18.bmp");
    loadSprite(enemyShipSprites[0][18], "../App_Data/enemy_pink_final/enemy-pink-19.bmp");
    loadSprite(enemyShipSprites[0][19], "../App_Data/enemy_pink_final/enemy-pink-20.bmp");
    loadSprite(enemyShipSprites[0][20], "../App_Data/enemy_pink_final/enemy-pink-21.bmp");
    loadSprite(enemyShipSprites[0][21], "../App_Data/enemy_pink_final/enemy-pink-22.bmp");
    loadSprite(enemyShipSprites[0][22], "../App_Data/enemy_pink_final/enemy-pink-23.bmp");
    loadSprite(enemyShipSprites[0][23], "../App_Data/enemy_pink_final/enemy-pink-24.bmp");

//    base
    loadSprite(enemyBaseSprites[0], "../App_Data/base_final/base-1.bmp");
    loadSprite(enemyBaseSprites[1], "../App_Data/base_final/base-2.bmp");
    loadSprite(enemyBaseSprites[2], "../App_Data/base_final/base-3.bmp");
    loadSprite(enemyBaseSprites[3], "../App_Data/base_final/base-4.bmp");
    loadSprite(enemyBaseSprites[4], "../App_Data/base_final/baseDoor-1.bmp");
    loadSprite(enemyBaseSprites[5], "../App_Data/base_final/baseDoor-2.bmp");
    loadSprite(enemyBaseSprites[6], "../App_Data/base_final/baseDoor-3.bmp");
    loadSprite(enemyBaseSprites[7], "../App_Data/base_final/baseDoor-4.bmp");
    loadSprite(enemyBaseSprites[8], "../App_Data/base_final/baseDoor-5.bmp");
    loadSprite(enemyBaseSprites[10], "../App_Data/base_final/baseDoor-1.bmp");
    loadSprite(enemyBaseSprites[11], "../App_Data/base_final/baseDoor-2.bmp");
    loadSprite(enemyBaseSprites[12], "../App_Data/base_final/baseDoor-3.bmp");
    loadSprite(enemyBaseSprites[13], "../App_Data/base_final/baseDoor-4.bmp");
    loadSprite(enemyBaseSprites[14], "../App_Data/base_final/baseDoor-5.bmp");

//    base explo
    loadSprite(enemyBaseSpritesExplosion[0], "../App_Data/base_explosion_final/base-explosion-1.bmp");
    loadSprite(enemyBaseSpritesExplosion[1], "../App_Data/base_explosion_final/base-explosion-2.bmp");
    loadSprite(enemyBaseSpritesExplosion[2], "../App_Data/base_explosion_final/base-explosion-3.bmp");

//      enemyGreen
    loadSprite(enemyShipLeaderSprites[0][0], "../App_Data/enemy_green_final/enemy-green-1.bmp");
    loadSprite(enemyShipLeaderSprites[0][1], "../App_Data/enemy_green_final/enemy-green-2.bmp");
    loadSprite(enemyShipLeaderSprites[0][2], "../App_Data/enemy_green_final/enemy-green-3.bmp");
    loadSprite(enemyShipLeaderSprites[0][3], "../App_Data/enemy_green_final/enemy-green-4.bmp");
    loadSprite(enemyShipLeaderSprites[0][4], "../App_Data/enemy_green_final/enemy-green-5.bmp");
    loadSprite(enemyShipLeaderSprites[0][5], "../App_Data/enemy_green_final/enemy-green-6.bmp");
    loadSprite(enemyShipLeaderSprites[0][6], "../App_Data/enemy_green_final/enemy-green-7.bmp");
    loadSprite(enemyShipLeaderSprites[0][7], "../App_Data/enemy_green_final/enemy-green-8.bmp");
    loadSprite(enemyShipLeaderSprites[0][8], "../App_Data/enemy_green_final/enemy-green-9.bmp");
    loadSprite(enemyShipLeaderSprites[0][9], "../App_Data/enemy_green_final/enemy-green-10.bmp");
    loadSprite(enemyShipLeaderSprites[0][10], "../App_Data/enemy_green_final/enemy-green-11.bmp");
    loadSprite(enemyShipLeaderSprites[0][11], "../App_Data/enemy_green_final/enemy-green-12.bmp");
    loadSprite(enemyShipLeaderSprites[0][12], "../App_Data/enemy_green_final/enemy-green-13.bmp");
    loadSprite(enemyShipLeaderSprites[0][13], "../App_Data/enemy_green_final/enemy-green-14.bmp");
    loadSprite(enemyShipLeaderSprites[0][14], "../App_Data/enemy_green_final/enemy-green-15.bmp");
    loadSprite(enemyShipLeaderSprites[0][15], "../App_Data/enemy_green_final/enemy-green-16.bmp");
    loadSprite(enemyShipLeaderSprites[0][16], "../App_Data/enemy_green_final/enemy-green-17.bmp");
    loadSprite(enemyShipLeaderSprites[0][17], "../App_Data/enemy_green_final/enemy-green-18.bmp");
    loadSprite(enemyShipLeaderSprites[0][18], "../App_Data/enemy_green_final/enemy-green-19.bmp");
    loadSprite(enemyShipLeaderSprites[0][19], "../App_Data/enemy_green_final/enemy-green-20.bmp");
    loadSprite(enemyShipLeaderSprites[0][20], "../App_Data/enemy_green_final/enemy-green-21.bmp");
    loadSprite(enemyShipLeaderSprites[0][21], "../App_Data/enemy_green_final/enemy-green-22.bmp");
    loadSprite(enemyShipLeaderSprites[0][22], "../App_Data/enemy_green_final/enemy-green-23.bmp");
    loadSprite(enemyShipLeaderSprites[0][23], "../App_Data/enemy_green_final/enemy-green-24.bmp");

//    enemyBlue
    loadSprite(enemyShipSprites[1][0], "../App_Data/enemy_blue_final/enemy-blue-1.bmp");
    loadSprite(enemyShipSprites[1][1], "../App_Data/enemy_blue_final/enemy-blue-2.bmp");
    loadSprite(enemyShipSprites[1][2], "../App_Data/enemy_blue_final/enemy-blue-3.bmp");
    loadSprite(enemyShipSprites[1][3], "../App_Data/enemy_blue_final/enemy-blue-4.bmp");
    loadSprite(enemyShipSprites[1][4], "../App_Data/enemy_blue_final/enemy-blue-5.bmp");
    loadSprite(enemyShipSprites[1][5], "../App_Data/enemy_blue_final/enemy-blue-6.bmp");
    loadSprite(enemyShipSprites[1][6], "../App_Data/enemy_blue_final/enemy-blue-7.bmp");
    loadSprite(enemyShipSprites[1][7], "../App_Data/enemy_blue_final/enemy-blue-8.bmp");
    loadSprite(enemyShipSprites[1][8], "../App_Data/enemy_blue_final/enemy-blue-9.bmp");
    loadSprite(enemyShipSprites[1][9], "../App_Data/enemy_blue_final/enemy-blue-10.bmp");
    loadSprite(enemyShipSprites[1][10], "../App_Data/enemy_blue_final/enemy-blue-11.bmp");
    loadSprite(enemyShipSprites[1][11], "../App_Data/enemy_blue_final/enemy-blue-12.bmp");
    loadSprite(enemyShipSprites[1][12], "../App_Data/enemy_blue_final/enemy-blue-13.bmp");
    loadSprite(enemyShipSprites[1][13], "../App_Data/enemy_blue_final/enemy-blue-14.bmp");
    loadSprite(enemyShipSprites[1][14], "../App_Data/enemy_blue_final/enemy-blue-15.bmp");
    loadSprite(enemyShipSprites[1][15], "../App_Data/enemy_blue_final/enemy-blue-16.bmp");
    loadSprite(enemyShipSprites[1][16], "../App_Data/enemy_blue_final/enemy-blue-17.bmp");
    loadSprite(enemyShipSprites[1][17], "../App_Data/enemy_blue_final/enemy-blue-18.bmp");
    loadSprite(enemyShipSprites[1][18], "../App_Data/enemy_blue_final/enemy-blue-19.bmp");
    loadSprite(enemyShipSprites[1][19], "../App_Data/enemy_blue_final/enemy-blue-20.bmp");
    loadSprite(enemyShipSprites[1][20], "../App_Data/enemy_blue_final/enemy-blue-21.bmp");
    loadSprite(enemyShipSprites[1][21], "../App_Data/enemy_blue_final/enemy-blue-22.bmp");
    loadSprite(enemyShipSprites[1][22], "../App_Data/enemy_blue_final/enemy-blue-23.bmp");
    loadSprite(enemyShipSprites[1][23], "../App_Data/enemy_blue_final/enemy-blue-24.bmp");

//    enemyOrange
    loadSprite(enemyShipLeaderSprites[1][0], "../App_Data/enemy_orange_final/enemy-orange-1.bmp");
    loadSprite(enemyShipLeaderSprites[1][1], "../App_Data/enemy_orange_final/enemy-orange-2.bmp");
    loadSprite(enemyShipLeaderSprites[1][2], "../App_Data/enemy_orange_final/enemy-orange-3.bmp");
    loadSprite(enemyShipLeaderSprites[1][3], "../App_Data/enemy_orange_final/enemy-orange-4.bmp");
    loadSprite(enemyShipLeaderSprites[1][4], "../App_Data/enemy_orange_final/enemy-orange-5.bmp");
    loadSprite(enemyShipLeaderSprites[1][5], "../App_Data/enemy_orange_final/enemy-orange-6.bmp");
    loadSprite(enemyShipLeaderSprites[1][6], "../App_Data/enemy_orange_final/enemy-orange-7.bmp");
    loadSprite(enemyShipLeaderSprites[1][7], "../App_Data/enemy_orange_final/enemy-orange-8.bmp");
    loadSprite(enemyShipLeaderSprites[1][8], "../App_Data/enemy_orange_final/enemy-orange-9.bmp");
    loadSprite(enemyShipLeaderSprites[1][9], "../App_Data/enemy_orange_final/enemy-orange-10.bmp");
    loadSprite(enemyShipLeaderSprites[1][10], "../App_Data/enemy_orange_final/enemy-orange-11.bmp");
    loadSprite(enemyShipLeaderSprites[1][11], "../App_Data/enemy_orange_final/enemy-orange-12.bmp");
    loadSprite(enemyShipLeaderSprites[1][12], "../App_Data/enemy_orange_final/enemy-orange-13.bmp");
    loadSprite(enemyShipLeaderSprites[1][13], "../App_Data/enemy_orange_final/enemy-orange-14.bmp");
    loadSprite(enemyShipLeaderSprites[1][14], "../App_Data/enemy_orange_final/enemy-orange-15.bmp");
    loadSprite(enemyShipLeaderSprites[1][15], "../App_Data/enemy_orange_final/enemy-orange-16.bmp");
    loadSprite(enemyShipLeaderSprites[1][16], "../App_Data/enemy_orange_final/enemy-orange-17.bmp");
    loadSprite(enemyShipLeaderSprites[1][17], "../App_Data/enemy_orange_final/enemy-orange-18.bmp");
    loadSprite(enemyShipLeaderSprites[1][18], "../App_Data/enemy_orange_final/enemy-orange-19.bmp");
    loadSprite(enemyShipLeaderSprites[1][19], "../App_Data/enemy_orange_final/enemy-orange-20.bmp");
    loadSprite(enemyShipLeaderSprites[1][20], "../App_Data/enemy_orange_final/enemy-orange-21.bmp");
    loadSprite(enemyShipLeaderSprites[1][21], "../App_Data/enemy_orange_final/enemy-orange-22.bmp");
    loadSprite(enemyShipLeaderSprites[1][22], "../App_Data/enemy_orange_final/enemy-orange-23.bmp");
    loadSprite(enemyShipLeaderSprites[1][23], "../App_Data/enemy_orange_final/enemy-orange-24.bmp");

//    bomb_orange
    loadSprite(enemyShipSprites[2][0], "../App_Data/bomb_orange_final/bomb-orange-1.bmp");
    loadSprite(enemyShipSprites[2][1], "../App_Data/bomb_orange_final/bomb-orange-2.bmp");
    loadSprite(enemyShipSprites[2][2], "../App_Data/bomb_orange_final/bomb-orange-3.bmp");
    loadSprite(enemyShipSprites[2][3], "../App_Data/bomb_orange_final/bomb-orange-4.bmp");
    loadSprite(enemyShipSprites[2][4], "../App_Data/bomb_orange_final/bomb-orange-5.bmp");
    loadSprite(enemyShipSprites[2][5], "../App_Data/bomb_orange_final/bomb-orange-6.bmp");
    loadSprite(enemyShipSprites[2][6], "../App_Data/bomb_orange_final/bomb-orange-7.bmp");
    loadSprite(enemyShipSprites[2][7], "../App_Data/bomb_orange_final/bomb-orange-8.bmp");
    loadSprite(enemyShipSprites[2][8], "../App_Data/bomb_orange_final/bomb-orange-9.bmp");
    loadSprite(enemyShipSprites[2][9], "../App_Data/bomb_orange_final/bomb-orange-10.bmp");
    loadSprite(enemyShipSprites[2][10], "../App_Data/bomb_orange_final/bomb-orange-11.bmp");
    loadSprite(enemyShipSprites[2][11], "../App_Data/bomb_orange_final/bomb-orange-12.bmp");
    loadSprite(enemyShipSprites[2][12], "../App_Data/bomb_orange_final/bomb-orange-13.bmp");
    loadSprite(enemyShipSprites[2][13], "../App_Data/bomb_orange_final/bomb-orange-14.bmp");
    loadSprite(enemyShipSprites[2][14], "../App_Data/bomb_orange_final/bomb-orange-15.bmp");
    loadSprite(enemyShipSprites[2][15], "../App_Data/bomb_orange_final/bomb-orange-16.bmp");
    loadSprite(enemyShipSprites[2][16], "../App_Data/bomb_orange_final/bomb-orange-17.bmp");
    loadSprite(enemyShipSprites[2][17], "../App_Data/bomb_orange_final/bomb-orange-18.bmp");
    loadSprite(enemyShipSprites[2][18], "../App_Data/bomb_orange_final/bomb-orange-19.bmp");
    loadSprite(enemyShipSprites[2][19], "../App_Data/bomb_orange_final/bomb-orange-20.bmp");
    loadSprite(enemyShipSprites[2][20], "../App_Data/bomb_orange_final/bomb-orange-21.bmp");
    loadSprite(enemyShipSprites[2][21], "../App_Data/bomb_orange_final/bomb-orange-22.bmp");
    loadSprite(enemyShipSprites[2][22], "../App_Data/bomb_orange_final/bomb-orange-23.bmp");
    loadSprite(enemyShipSprites[2][23], "../App_Data/bomb_orange_final/bomb-orange-24.bmp");

//    bomb_green
    loadSprite(enemyShipLeaderSprites[2][0], "../App_Data/bomb_green_final/bomb-green-1.bmp");
    loadSprite(enemyShipLeaderSprites[2][1], "../App_Data/bomb_green_final/bomb-green-2.bmp");
    loadSprite(enemyShipLeaderSprites[2][2], "../App_Data/bomb_green_final/bomb-green-3.bmp");
    loadSprite(enemyShipLeaderSprites[2][3], "../App_Data/bomb_green_final/bomb-green-4.bmp");
    loadSprite(enemyShipLeaderSprites[2][4], "../App_Data/bomb_green_final/bomb-green-5.bmp");
    loadSprite(enemyShipLeaderSprites[2][5], "../App_Data/bomb_green_final/bomb-green-6.bmp");
    loadSprite(enemyShipLeaderSprites[2][6], "../App_Data/bomb_green_final/bomb-green-7.bmp");
    loadSprite(enemyShipLeaderSprites[2][7], "../App_Data/bomb_green_final/bomb-green-8.bmp");
    loadSprite(enemyShipLeaderSprites[2][8], "../App_Data/bomb_green_final/bomb-green-9.bmp");
    loadSprite(enemyShipLeaderSprites[2][9], "../App_Data/bomb_green_final/bomb-green-10.bmp");
    loadSprite(enemyShipLeaderSprites[2][10], "../App_Data/bomb_green_final/bomb-green-11.bmp");
    loadSprite(enemyShipLeaderSprites[2][11], "../App_Data/bomb_green_final/bomb-green-12.bmp");
    loadSprite(enemyShipLeaderSprites[2][12], "../App_Data/bomb_green_final/bomb-green-13.bmp");
    loadSprite(enemyShipLeaderSprites[2][13], "../App_Data/bomb_green_final/bomb-green-14.bmp");
    loadSprite(enemyShipLeaderSprites[2][14], "../App_Data/bomb_green_final/bomb-green-15.bmp");
    loadSprite(enemyShipLeaderSprites[2][15], "../App_Data/bomb_green_final/bomb-green-16.bmp");
    loadSprite(enemyShipLeaderSprites[2][16], "../App_Data/bomb_green_final/bomb-green-17.bmp");
    loadSprite(enemyShipLeaderSprites[2][17], "../App_Data/bomb_green_final/bomb-green-18.bmp");
    loadSprite(enemyShipLeaderSprites[2][18], "../App_Data/bomb_green_final/bomb-green-19.bmp");
    loadSprite(enemyShipLeaderSprites[2][19], "../App_Data/bomb_green_final/bomb-green-20.bmp");
    loadSprite(enemyShipLeaderSprites[2][20], "../App_Data/bomb_green_final/bomb-green-21.bmp");
    loadSprite(enemyShipLeaderSprites[2][21], "../App_Data/bomb_green_final/bomb-green-22.bmp");
    loadSprite(enemyShipLeaderSprites[2][22], "../App_Data/bomb_green_final/bomb-green-23.bmp");
    loadSprite(enemyShipLeaderSprites[2][23], "../App_Data/bomb_green_final/bomb-green-24.bmp");

//    numbers
    loadSprite(numbers[0],"../App_Data/numbers_final/Numbers-0.bmp" );
    loadSprite(numbers[1],"../App_Data/numbers_final/Numbers-1.bmp" );
    loadSprite(numbers[2],"../App_Data/numbers_final/Numbers-2.bmp" );
    loadSprite(numbers[3],"../App_Data/numbers_final/Numbers-3.bmp" );
    loadSprite(numbers[4],"../App_Data/numbers_final/Numbers-4.bmp" );
    loadSprite(numbers[5],"../App_Data/numbers_final/Numbers-5.bmp" );
    loadSprite(numbers[6],"../App_Data/numbers_final/Numbers-6.bmp" );
    loadSprite(numbers[7],"../App_Data/numbers_final/Numbers-7.bmp" );
    loadSprite(numbers[8],"../App_Data/numbers_final/Numbers-8.bmp" );
    loadSprite(numbers[9],"../App_Data/numbers_final/Numbers-9.bmp" );


//    alphabet white
    loadSprite(alphabetWhite[0],"../App_Data/alphabet_white_final/alphabet_white-1.bmp" );
    loadSprite(alphabetWhite[1],"../App_Data/alphabet_white_final/alphabet_white-2.bmp" );
    loadSprite(alphabetWhite[2],"../App_Data/alphabet_white_final/alphabet_white-3.bmp" );
    loadSprite(alphabetWhite[3],"../App_Data/alphabet_white_final/alphabet_white-4.bmp" );
    loadSprite(alphabetWhite[4],"../App_Data/alphabet_white_final/alphabet_white-5.bmp" );
    loadSprite(alphabetWhite[5],"../App_Data/alphabet_white_final/alphabet_white-6.bmp" );
    loadSprite(alphabetWhite[6],"../App_Data/alphabet_white_final/alphabet_white-7.bmp" );
    loadSprite(alphabetWhite[7],"../App_Data/alphabet_white_final/alphabet_white-8.bmp" );
    loadSprite(alphabetWhite[8],"../App_Data/alphabet_white_final/alphabet_white-9.bmp" );
    loadSprite(alphabetWhite[9],"../App_Data/alphabet_white_final/alphabet_white-10.bmp" );
    loadSprite(alphabetWhite[10],"../App_Data/alphabet_white_final/alphabet_white-11.bmp" );
    loadSprite(alphabetWhite[11],"../App_Data/alphabet_white_final/alphabet_white-12.bmp" );
    loadSprite(alphabetWhite[12],"../App_Data/alphabet_white_final/alphabet_white-13.bmp" );
    loadSprite(alphabetWhite[13],"../App_Data/alphabet_white_final/alphabet_white-14.bmp" );
    loadSprite(alphabetWhite[14],"../App_Data/alphabet_white_final/alphabet_white-15.bmp" );
    loadSprite(alphabetWhite[15],"../App_Data/alphabet_white_final/alphabet_white-16.bmp" );
    loadSprite(alphabetWhite[16],"../App_Data/alphabet_white_final/alphabet_white-17.bmp" );
    loadSprite(alphabetWhite[17],"../App_Data/alphabet_white_final/alphabet_white-18.bmp" );
    loadSprite(alphabetWhite[18],"../App_Data/alphabet_white_final/alphabet_white-19.bmp" );
    loadSprite(alphabetWhite[19],"../App_Data/alphabet_white_final/alphabet_white-20.bmp" );
    loadSprite(alphabetWhite[20],"../App_Data/alphabet_white_final/alphabet_white-21.bmp" );
    loadSprite(alphabetWhite[21],"../App_Data/alphabet_white_final/alphabet_white-22.bmp" );
    loadSprite(alphabetWhite[22],"../App_Data/alphabet_white_final/alphabet_white-23.bmp" );
    loadSprite(alphabetWhite[23],"../App_Data/alphabet_white_final/alphabet_white-24.bmp" );
    loadSprite(alphabetWhite[24],"../App_Data/alphabet_white_final/alphabet_white-25.bmp" );
    loadSprite(alphabetWhite[25],"../App_Data/alphabet_white_final/alphabet_white-26.bmp" );
    loadSprite(alphabetWhite[26],"../App_Data/alphabet_white_final/alphabet_white-27.bmp" );
    loadSprite(alphabetWhite[27],"../App_Data/alphabet_white_final/alphabet_white-28.bmp" );
    loadSprite(alphabetWhite[28],"../App_Data/alphabet_white_final/alphabet_white-29.bmp" );

    //    alphabet white
//    loadSprite(Model::alphabetBlackNoBorder[0],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-1.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[1],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-2.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[2],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-3.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[3],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-4.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[4],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-5.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[5],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-6.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[6],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-7.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[7],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-8.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[8],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-9.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[9],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-10.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[10],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-11.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[11],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-12.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[12],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-13.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[13],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-14.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[14],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-15.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[15],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-16.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[16],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-17.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[17],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-18.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[18],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-19.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[19],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-20.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[20],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-21.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[21],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-22.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[22],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-23.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[23],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-24.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[24],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-25.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[25],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-26.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[26],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-27.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[27],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-28.bmp" );
//    loadSprite(Model::alphabetBlackNoBorder[28],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-29.bmp" );

//    alphabet black
    loadSprite(alphabetBlack[0],"../App_Data/alphabet_black_final/alphabet_black-1.bmp" );
    loadSprite(alphabetBlack[1],"../App_Data/alphabet_black_final/alphabet_black-2.bmp" );
    loadSprite(alphabetBlack[2],"../App_Data/alphabet_black_final/alphabet_black-3.bmp" );
    loadSprite(alphabetBlack[3],"../App_Data/alphabet_black_final/alphabet_black-4.bmp" );
    loadSprite(alphabetBlack[4],"../App_Data/alphabet_black_final/alphabet_black-5.bmp" );
    loadSprite(alphabetBlack[5],"../App_Data/alphabet_black_final/alphabet_black-6.bmp" );
    loadSprite(alphabetBlack[6],"../App_Data/alphabet_black_final/alphabet_black-7.bmp" );
    loadSprite(alphabetBlack[7],"../App_Data/alphabet_black_final/alphabet_black-8.bmp" );
    loadSprite(alphabetBlack[8],"../App_Data/alphabet_black_final/alphabet_black-9.bmp" );
    loadSprite(alphabetBlack[9],"../App_Data/alphabet_black_final/alphabet_black-10.bmp" );
    loadSprite(alphabetBlack[10],"../App_Data/alphabet_black_final/alphabet_black-11.bmp" );
    loadSprite(alphabetBlack[11],"../App_Data/alphabet_black_final/alphabet_black-12.bmp" );
    loadSprite(alphabetBlack[12],"../App_Data/alphabet_black_final/alphabet_black-13.bmp" );
    loadSprite(alphabetBlack[13],"../App_Data/alphabet_black_final/alphabet_black-14.bmp" );
    loadSprite(alphabetBlack[14],"../App_Data/alphabet_black_final/alphabet_black-15.bmp" );
    loadSprite(alphabetBlack[15],"../App_Data/alphabet_black_final/alphabet_black-16.bmp" );
    loadSprite(alphabetBlack[16],"../App_Data/alphabet_black_final/alphabet_black-17.bmp" );
    loadSprite(alphabetBlack[17],"../App_Data/alphabet_black_final/alphabet_black-18.bmp" );
    loadSprite(alphabetBlack[18],"../App_Data/alphabet_black_final/alphabet_black-19.bmp" );
    loadSprite(alphabetBlack[19],"../App_Data/alphabet_black_final/alphabet_black-20.bmp" );
    loadSprite(alphabetBlack[20],"../App_Data/alphabet_black_final/alphabet_black-21.bmp" );
    loadSprite(alphabetBlack[21],"../App_Data/alphabet_black_final/alphabet_black-22.bmp" );
    loadSprite(alphabetBlack[22],"../App_Data/alphabet_black_final/alphabet_black-23.bmp" );
    loadSprite(alphabetBlack[23],"../App_Data/alphabet_black_final/alphabet_black-24.bmp" );
    loadSprite(alphabetBlack[24],"../App_Data/alphabet_black_final/alphabet_black-25.bmp" );
    loadSprite(alphabetBlack[25],"../App_Data/alphabet_black_final/alphabet_black-26.bmp" );
    loadSprite(alphabetBlack[26],"../App_Data/alphabet_black_final/alphabet_black-27.bmp" );
    loadSprite(alphabetBlack[27],"../App_Data/alphabet_black_final/alphabet_black-28.bmp" );
    loadSprite(alphabetBlack[28],"../App_Data/alphabet_black_final/alphabet_black-29.bmp" );

    map = new GLubyte[256*400*4];
    for(int x = 0; x < 256*400*4; x+=4) {
        map[x+0] = 125;
        map[x+1] = 0;
        map[x+2] = 125;
        map[x+3] = 255;
    }
}
void View::loadSprite(GLubyte* &dst, char* filepath) {
    int filesize;
    int swap;
    FILE* file = fopen(filepath, "r");
    fseek(file,0,SEEK_END);
    filesize = ftell(file);
    fseek(file,0,SEEK_SET);
    dst = new GLubyte[filesize];
    fread(dst, sizeof(GLubyte), filesize, file);

    for(int i = 8; i < filesize; i+=4) {
        swap = dst[i];
        dst[i] = dst[i+2];
        dst[i+2] = swap;
    }
    fclose(file);
    printf("%d\n",dst);
}