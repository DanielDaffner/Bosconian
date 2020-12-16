//
// Created by basti on 11.12.2020.
//
#include "../../include/controller/Controller.h"

#include <iostream>
#include <cmath>

Controller::Controller() {

}

//öhm hat keiner gesehn o.O
GLubyte* enemyPink;

int Controller::init() {

    //init controller
    model = new Model();
    inGame = false;
    view = new View(model);
    loadSprites();
    //psshhhtttt
    getSprite(enemyPink,"../App_Data/enemy_pink_bmp/enemy-pink-16.bmp");
    //o.O
    onStart();
    return 0;
}

bool move = false;
int count = 0;
int firecd = 0;

//Testo e?
Position2D enemyPos= {-300,100};

void Controller::updateMainWindow() {

    int space = glfwGetKey(view->window, GLFW_KEY_SPACE);
    if (space == GLFW_PRESS) {
    inGame = true;
    }

    view->prepareFrame();

    Position2D posString1;
    posString1.x=448;
    posString1.y=500;
    //scam, should have own var
    if((count/60)%2==1)

    view->drawString(posString1,"PRESS SPACE BAR");

    Position2D posPlayer ={640,360};
    view->render(posPlayer,model->player->sprites[0][0]);

    //Background
    for(BackgroundPixel* ele: model->pixelarr[(count/30)]) {
        view->renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    for(BackgroundPixel* ele: model->pixelarr[((count/30)+1)%3]) {
        view->renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    count++;
    count = count % 119;
    if(move){
        move=false;
    }
    else{
        move=true;
    }

    view->render(enemyPos,enemyPink);
    enemyPos.x+=2;
    enemyPos.y+=2;
    if(enemyPos.y >=730) enemyPos = {-300,100};
}

void Controller::onStart(){
    for(int i = 0; i < 50;i++) {
        model->mines.push_back(new Mine(1280-(rand() % (1280*2)),760-(rand() % (760*2))));
    }
};

void Controller::updateGameWindow() {
    // input
//    int up = glfwGetKey(view->window, GLFW_KEY_UP);
//    int left = glfwGetKey(view->window, GLFW_KEY_LEFT);
//    int right = glfwGetKey(view->window, GLFW_KEY_RIGHT);
//    int down = glfwGetKey(view->window, GLFW_KEY_DOWN);
//    int space = glfwGetKey(view->window, GLFW_KEY_SPACE);
//    int escape = glfwGetKey(view->window, GLFW_KEY_ESCAPE);
    //set direction
//    if (up == GLFW_PRESS) {
//        model->player->direction[0] = 0;
//        model->player->direction[1] = -1;
//        model->player->spriteDirection = SpriteDirection::up;
//        model->player->playerspeed = 4;
//    }
//    if (left == GLFW_PRESS) {
//        model->player->direction[0] = -1;
//        model->player->direction[1] = 0;
//        model->player->spriteDirection = SpriteDirection::left;
//        model->player->playerspeed = 4;
//    }
//    if (right == GLFW_PRESS) {
//        model->player->direction[0] = 1;
//        model->player->direction[1] = 0;
//        model->player->spriteDirection = SpriteDirection::right;
//        model->player->playerspeed = 4;
//    }
//    if (down == GLFW_PRESS) {
//        model->player->direction[0] = 0;
//        model->player->direction[1] = 1;
//        model->player->spriteDirection = SpriteDirection::down;
//        model->player->playerspeed = 4;
//    }
//    if (up == GLFW_PRESS && left == GLFW_PRESS) {
//        model->player->direction[0] = -1;
//        model->player->direction[1] = -1;
//        model->player->spriteDirection = SpriteDirection::upleft;
//        model->player->playerspeed = 3;
//    }
//    if (up == GLFW_PRESS && right == GLFW_PRESS) {
//        model->player->direction[0] = 1;
//        model->player->direction[1] = -1;
//        model->player->spriteDirection = SpriteDirection::upright;
//        model->player->playerspeed = 3;
//    }
//    if (down == GLFW_PRESS && left == GLFW_PRESS) {
//        model->player->direction[0] = -1;
//        model->player->direction[1] = 1;
//        model->player->spriteDirection = SpriteDirection::downleft;
//        model->player->playerspeed = 3;
//    }
//    if (down == GLFW_PRESS && right == GLFW_PRESS) {
//        model->player->direction[0] = 1;
//        model->player->direction[1] = 1;
//        model->player->spriteDirection = SpriteDirection::downright;
//        model->player->playerspeed = 3;
//    }
    int up = glfwGetKey(view->window, GLFW_KEY_W);
    int left = glfwGetKey(view->window, GLFW_KEY_A);
    int right = glfwGetKey(view->window, GLFW_KEY_D);
    int down = glfwGetKey(view->window, GLFW_KEY_S);
    int space = glfwGetKey(view->window, GLFW_KEY_SPACE);
    int escape = glfwGetKey(view->window, GLFW_KEY_ESCAPE);
    if (up == GLFW_PRESS) {
        model->player->direction[0] = 0;
        model->player->direction[1] = -1;
        model->player->spriteDirection = SpriteDirection::up;
        model->player->playerspeed = 4;
    }
    if (left == GLFW_PRESS) {
        model->player->direction[0] = -1;
        model->player->direction[1] = 0;
        model->player->spriteDirection = SpriteDirection::left;
        model->player->playerspeed = 4;
    }
    if (right == GLFW_PRESS) {
        model->player->direction[0] = 1;
        model->player->direction[1] = 0;
        model->player->spriteDirection = SpriteDirection::right;
        model->player->playerspeed = 4;
    }
    if (down == GLFW_PRESS) {
        model->player->direction[0] = 0;
        model->player->direction[1] = 1;
        model->player->spriteDirection = SpriteDirection::down;
        model->player->playerspeed = 4;
    }
    if (up == GLFW_PRESS && left == GLFW_PRESS) {
        model->player->direction[0] = -1;
        model->player->direction[1] = -1;
        model->player->spriteDirection = SpriteDirection::upleft;
        model->player->playerspeed = 3;
    }
    if (up == GLFW_PRESS && right == GLFW_PRESS) {
        model->player->direction[0] = 1;
        model->player->direction[1] = -1;
        model->player->spriteDirection = SpriteDirection::upright;
        model->player->playerspeed = 3;
    }
    if (down == GLFW_PRESS && left == GLFW_PRESS) {
        model->player->direction[0] = -1;
        model->player->direction[1] = 1;
        model->player->spriteDirection = SpriteDirection::downleft;
        model->player->playerspeed = 3;
    }
    if (down == GLFW_PRESS && right == GLFW_PRESS) {
        model->player->direction[0] = 1;
        model->player->direction[1] = 1;
        model->player->spriteDirection = SpriteDirection::downright;
        model->player->playerspeed = 3;
    }

    firecd--;
    if (space == GLFW_PRESS) {
        if(firecd <= 0) {
            model->projectilesPlayer.push_back(
                    new ProjectilePlayer(model->player->pos.x+32, model->player->pos.y-32, model->player->direction[0],
                                         model->player->direction[1], model->player->spriteDirection));
            model->projectilesPlayer.push_back(
                    new ProjectilePlayer(model->player->pos.x+32, model->player->pos.y-32, model->player->direction[0]*-1,
                                         model->player->direction[1]*-1, model->player->spriteDirection));
            firecd = 10;
        }
    }
    if (escape == GLFW_PRESS) {
        inGame=false;
        view->resetFrame();
        model->player->resetPosition();
        return;
    }

//  calc player position
    model->player->pos.x += model->player->direction[0] * model->player->playerspeed;
    model->player->pos.y += model->player->direction[1] * model->player->playerspeed;
//  calc projectile position
    for(ProjectilePlayer* ele: model->projectilesPlayer) {
        ele->pos.x = model->player->pos.x +32+ ( ProjectilePlayer::projectileSpeed * ele->traveled * ele->direction.x );
        ele->pos.y = model->player->pos.y -32+ ( ProjectilePlayer::projectileSpeed * ele->traveled * ele->direction.y);
        ele->traveled++;
    }
//  prepare new frame
    view->prepareFrame();
    // move Frame
    view->moveFrame();
//    render background
    for(BackgroundPixel* ele: model->pixelarr[(count/30)]) {
        if(move){
            ele->pos.x += model->player->direction[0];
            ele->pos.y += model->player->direction[1];

        }
        view->renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    for(BackgroundPixel* ele: model->pixelarr[((count/30)+1)%3]) {
        if(move){
            ele->pos.x += model->player->direction[0];
            ele->pos.y += model->player->direction[1];

        }
        view->renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    count++;
    count = count % 119;
    if(move){
        move=false;
    }
    else{
        move=true;
    }

//    detect mine Collosion
    double distance;
    for(auto iterator = model->mines.begin(); iterator!= model->mines.end();) {
        distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - model->player->pos.x,2)+pow(iterator._Ptr->_Myval->pos.y - model->player->pos.y,2));
        if(distance <= 32)  {
            model->player->collision = true;
            iterator._Ptr->_Myval->collision = true;
            model->minesExploding.push_back(iterator._Ptr->_Myval);
            iterator._Ptr->_Myval->pos.x += -32;
            iterator._Ptr->_Myval->pos.y += 32;
            iterator = model->mines.erase(iterator);
        } else
            iterator++;
    }
//    detect projectile player
    bool hit = false;
    for(auto iterator = model->projectilesPlayer.begin(); iterator!= model->projectilesPlayer.end();) {
        if(iterator._Ptr->_Myval->traveled <= 100) {
            for (auto iterator2 = model->mines.begin(); iterator2 != model->mines.end();) {
                distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - iterator2._Ptr->_Myval->pos.x, 2) +
                                pow(iterator._Ptr->_Myval->pos.y - iterator2._Ptr->_Myval->pos.y, 2));
                if (distance <= 32) {
                    iterator2._Ptr->_Myval->collision = true;
                    model->minesExploding.push_back(iterator2._Ptr->_Myval);
                    iterator2._Ptr->_Myval->pos.x += -32;
                    iterator2._Ptr->_Myval->pos.y += 32;
                    iterator2 = model->mines.erase(iterator2);
                    delete (iterator._Ptr->_Myval);
                    iterator = model->projectilesPlayer.erase(iterator);
                    hit = true;
                    break;
                } else
                    iterator2++;
            }
            if (hit) {
                hit = false;
            } else
                iterator++;
        } else {
            iterator = model->projectilesPlayer.erase(iterator);
        }
    }

//    render exploding mines
    for(auto iterator = model->minesExploding.begin(); iterator!= model->minesExploding.end();) {
        view->render(iterator._Ptr->_Myval->pos,Mine::spritesExplosion[iterator._Ptr->_Myval->explosionPhase/10]);
        iterator._Ptr->_Myval->explosionPhase++;
        if(iterator._Ptr->_Myval->explosionPhase >= 30) {
            delete (iterator._Ptr->_Myval);
            iterator = model->minesExploding.erase(iterator);
        }else
            iterator++;
    }


//    render mines
    for(Mine* ele: model->mines) {
        view->render(ele->pos,ele->sprites);
    }
//    render projectiles from player
    for(ProjectilePlayer* ele: model->projectilesPlayer) {
        view->render(ele->pos,ele->sprite);
    }
//    render player
    view->render(model->player->pos,model->player->sprites[model->player->spriteDirection][model->player->spriteLight]);

}
void Controller::loadSprites() {

    getSprite(Player::sprites[SpriteDirection::up][0],"../App_Data/ship_bmp/ship_up_light_off.bmp");
    getSprite(Player::sprites[SpriteDirection::up][1],"../App_Data/ship_bmp/ship_up_light_on.bmp");

    getSprite(Player::sprites[SpriteDirection::upright][1], "../App_Data/ship_bmp/ship_up_right_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::upright][0], "../App_Data/ship_bmp/ship_up_right_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::right][1], "../App_Data/ship_bmp/ship_right_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::right][0], "../App_Data/ship_bmp/ship_right_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::downright][1], "../App_Data/ship_bmp/ship_down_right_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::downright][0], "../App_Data/ship_bmp/ship_down_right_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::down][1], "../App_Data/ship_bmp/ship_down_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::down][0], "../App_Data/ship_bmp/ship_down_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::downleft][1], "../App_Data/ship_bmp/ship_down_left_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::downleft][0], "../App_Data/ship_bmp/ship_down_left_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::left][1], "../App_Data/ship_bmp/ship_left_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::left][0], "../App_Data/ship_bmp/ship_left_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::upleft][1], "../App_Data/ship_bmp/ship_up_left_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::upleft][0], "../App_Data/ship_bmp/ship_up_left_light_off.bmp");

    getSprite(Mine::sprites, "../App_Data/mine_bmp/mine.bmp");
    getSprite(Mine::spritesExplosion[0], "../App_Data/mine_explosion_bmp/mine_explosion_1.bmp");
    getSprite(Mine::spritesExplosion[1], "../App_Data/mine_explosion_bmp/mine_explosion_2.bmp");
    getSprite(Mine::spritesExplosion[2], "../App_Data/mine_explosion_bmp/mine_explosion_3.bmp");

    getSprite(ProjectilePlayer::sprites[0], "../App_Data/projectile_bmp/projectile-1.bmp");
    getSprite(ProjectilePlayer::sprites[1], "../App_Data/projectile_bmp/projectile-4.bmp");
    getSprite(ProjectilePlayer::sprites[2], "../App_Data/projectile_bmp/projectile-3.bmp");
    getSprite(ProjectilePlayer::sprites[3], "../App_Data/projectile_bmp/projectile-2.bmp");

    //alphabet

    getSprite(Model::alphabetWhite[0],"../App_Data/alphabet_bmp/alphabet_white-1.bmp" );
    getSprite(Model::alphabetWhite[1],"../App_Data/alphabet_bmp/alphabet_white-2.bmp" );
    getSprite(Model::alphabetWhite[2],"../App_Data/alphabet_bmp/alphabet_white-3.bmp" );
    getSprite(Model::alphabetWhite[3],"../App_Data/alphabet_bmp/alphabet_white-4.bmp" );
    getSprite(Model::alphabetWhite[4],"../App_Data/alphabet_bmp/alphabet_white-5.bmp" );
    getSprite(Model::alphabetWhite[5],"../App_Data/alphabet_bmp/alphabet_white-6.bmp" );
    getSprite(Model::alphabetWhite[6],"../App_Data/alphabet_bmp/alphabet_white-7.bmp" );
    getSprite(Model::alphabetWhite[7],"../App_Data/alphabet_bmp/alphabet_white-8.bmp" );
    getSprite(Model::alphabetWhite[8],"../App_Data/alphabet_bmp/alphabet_white-9.bmp" );
    getSprite(Model::alphabetWhite[9],"../App_Data/alphabet_bmp/alphabet_white-10.bmp" );
    getSprite(Model::alphabetWhite[10],"../App_Data/alphabet_bmp/alphabet_white-11.bmp" );
    getSprite(Model::alphabetWhite[11],"../App_Data/alphabet_bmp/alphabet_white-12.bmp" );
    getSprite(Model::alphabetWhite[12],"../App_Data/alphabet_bmp/alphabet_white-13.bmp" );
    getSprite(Model::alphabetWhite[13],"../App_Data/alphabet_bmp/alphabet_white-14.bmp" );
    getSprite(Model::alphabetWhite[14],"../App_Data/alphabet_bmp/alphabet_white-15.bmp" );
    getSprite(Model::alphabetWhite[15],"../App_Data/alphabet_bmp/alphabet_white-16.bmp" );
    getSprite(Model::alphabetWhite[16],"../App_Data/alphabet_bmp/alphabet_white-17.bmp" );
    getSprite(Model::alphabetWhite[17],"../App_Data/alphabet_bmp/alphabet_white-18.bmp" );
    getSprite(Model::alphabetWhite[18],"../App_Data/alphabet_bmp/alphabet_white-19.bmp" );
    getSprite(Model::alphabetWhite[19],"../App_Data/alphabet_bmp/alphabet_white-20.bmp" );
    getSprite(Model::alphabetWhite[20],"../App_Data/alphabet_bmp/alphabet_white-21.bmp" );
    getSprite(Model::alphabetWhite[21],"../App_Data/alphabet_bmp/alphabet_white-22.bmp" );
    getSprite(Model::alphabetWhite[22],"../App_Data/alphabet_bmp/alphabet_white-23.bmp" );
    getSprite(Model::alphabetWhite[23],"../App_Data/alphabet_bmp/alphabet_white-24.bmp" );
    getSprite(Model::alphabetWhite[24],"../App_Data/alphabet_bmp/alphabet_white-25.bmp" );
    getSprite(Model::alphabetWhite[25],"../App_Data/alphabet_bmp/alphabet_white-26.bmp" );
    getSprite(Model::alphabetWhite[26],"../App_Data/alphabet_bmp/alphabet_white-27.bmp" );
    getSprite(Model::alphabetWhite[27],"../App_Data/alphabet_bmp/alphabet_white-28.bmp" );
    getSprite(Model::alphabetWhite[28],"../App_Data/alphabet_bmp/alphabet_white-29.bmp" );

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

