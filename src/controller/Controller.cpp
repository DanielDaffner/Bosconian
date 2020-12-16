//
// Created by basti on 11.12.2020.
//
#include "../../include/controller/Controller.h"

#include <iostream>
#include <cmath>

Controller::Controller() {

}

int Controller::init() {

    //init controller
    model = new Model();

    inGame = false;

    view = new View(model);
    printf("init controller done\n");

    loadSprites();

    onStart();
    return 0;
}

void Controller::updateMainWindow() {


    int up = glfwGetKey(view->window, GLFW_KEY_UP);
    if (up == GLFW_PRESS) {
    inGame = true;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glViewport(0,0,1280,720);
    view->render(model->player->pos,model->player->sprites[0][0]);

}

void Controller::onStart(){
    for(int i = 0; i < 50;i++) {
        model->mines.push_back(new Mine(1280-(rand() % (1280*2)),760-(rand() % (760*2))));
    }
};
bool move = false;
int count = 0;
int firecd = 0;
void Controller::updateGameWindow() {
    // input
    int up = glfwGetKey(view->window, GLFW_KEY_UP);
    int left = glfwGetKey(view->window, GLFW_KEY_LEFT);
    int right = glfwGetKey(view->window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(view->window, GLFW_KEY_DOWN);
    int space = glfwGetKey(view->window, GLFW_KEY_SPACE);
    int escape = glfwGetKey(view->window, GLFW_KEY_ESCAPE);
    //set direction
    if (up == GLFW_PRESS) {
        model->player->direction[0] = 0;
        model->player->direction[1] = -1;

        model->player->spriteDirection = SpriteDirection::up;
    }
    if (left == GLFW_PRESS) {
        model->player->direction[0] = -1;
        model->player->direction[1] = 0;

        model->player->spriteDirection = SpriteDirection::left;
    }

    if (right == GLFW_PRESS) {
        model->player->direction[0] = 1;
        model->player->direction[1] = 0;

        model->player->spriteDirection = SpriteDirection::right;
    }
    if (down == GLFW_PRESS) {
        model->player->direction[0] = 0;
        model->player->direction[1] = 1;

        model->player->spriteDirection = SpriteDirection::down;
    }
    firecd--;
    if (space == GLFW_PRESS) {
        if(firecd <= 0) {
            model->projectilesPlayer.push_back(
                    new ProjectilePlayer(model->player->pos.x, model->player->pos.y, model->player->direction[0],
                                         model->player->direction[1], 0));
            firecd = 10;
        }
    }
    if (escape == GLFW_PRESS) {
        inGame=false;
    }

//  calc player position
    model->player->pos.x += model->player->direction[0] * model->player->playerspeed;
    model->player->pos.y += model->player->direction[1] * model->player->playerspeed;
//  calc projectile position
    for(ProjectilePlayer* ele: model->projectilesPlayer) {
        ele->pos.x += ele->direction.x * ProjectilePlayer::projectileSpeed;
        ele->pos.y += ele->direction.y * ProjectilePlayer::projectileSpeed;
    }
//  prepare new frame
    view->prepareFrame();
//    render background
    for(BackgroundPixel* ele: model->pixelarr[(count/120)]) {
        if(move){
            ele->pos.x += model->player->direction[0];
            ele->pos.y += model->player->direction[1];

        }
        view->renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    for(BackgroundPixel* ele: model->pixelarr[((count/120)+1)%3]) {
        if(move){
            ele->pos.x += model->player->direction[0];
            ele->pos.y += model->player->direction[1];

        }
        view->renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    count++;
    count = count % 359;
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
        for(auto iterator2 = model->mines.begin(); iterator2 != model->mines.end();) {
            distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - iterator2._Ptr->_Myval->pos.x,2)+pow(iterator._Ptr->_Myval->pos.y - iterator2._Ptr->_Myval->pos.y,2));
            if(distance <= 32)  {
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

    getSprite(ProjectilePlayer::sprites[0], "../App_Data/projectile_bmp/projectile-4.bmp");
    getSprite(ProjectilePlayer::sprites[1], "../App_Data/projectile_bmp/projectile-3.bmp");
    getSprite(ProjectilePlayer::sprites[2], "../App_Data/projectile_bmp/projectile-2.bmp");
    getSprite(ProjectilePlayer::sprites[3], "../App_Data/projectile_bmp/projectile-1.bmp");

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

