//
// Created by basti on 11.12.2020.
//
#include "../../include/controller/Controller.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <cmath>
#include <string>

Controller::Controller() {

}

int Controller::init() {

    //init controller
    model = new Model();
    inGame = false;
    view = new View(model);
    loadSprites();


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

    Position2D posPlayer = {640,360};
    view->render(posPlayer,Player::sprites[0][0]);

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

    view->render(enemyPos, ITypeMissile::sprites[15]);
    enemyPos.x+=2;
    enemyPos.y+=2;
    if(enemyPos.y >=730) enemyPos = {-300,100};
}

void Controller::onStart(){

    model->mines.clear();
    model->iTypeMissiles.clear();
    model->minesExploding.clear();
    model->iTypeMissilesExploding.clear();
    model->player->lifes=4;
    model->player->score=0;
    model->player->resetPosition();
    view->resetFrame();
    int x;
    int y;
    int distance;
    for(int i = 0; i < 120;i++) {
        x = (rand() % (MAP_WIDTH));
        y = (rand() % (MAP_HEIGHT));
        distance = sqrt(pow(x - model->player->pos.x,2)+pow(y - model->player->pos.y,2));

        if(distance > 255 )
        model->mines.push_back(new Mine(x,y));
        else printf("protected\n");
    }
    for(int i = 0; i < 20;i++) {
        x = (rand() % (MAP_WIDTH));
        y = (rand() % (MAP_HEIGHT));
        distance = sqrt(pow(x - model->player->pos.x,2)+pow(y - model->player->pos.y,2));

        if(distance > 255 )
            model->iTypeMissiles.push_back(new ITypeMissile(x, y, 1));
        else printf("protected\n");
    }
//    model->enemyShipsPink.push_back(new ITypeMissile(MAP_WIDTH / 2,(MAP_HEIGHT / 4) * 3,1));
    model->enemyBases.push_back(new EnemyBase(500,500));

}


void Controller::spawnEnemys(){
    if(model->iTypeMissiles.size()<10){
        int x;
        int y;
        int distance;
        for(int i = 0; i < 10;i++) {
            x = (rand() % (MAP_WIDTH));
            y = (rand() % (MAP_HEIGHT));
            distance = sqrt(pow(x - model->player->pos.x,2)+pow(y - model->player->pos.y,2));

            if(distance > 255 )
                model->iTypeMissiles.push_back(new ITypeMissile(x, y, 1));
            else printf("protected\n");
        }
    }

}
void Controller::updateGameWindow() {
    // input
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
    if (up == GLFW_PRESS && left == GLFW_PRESS) {
        model->player->direction[0] = -1;
        model->player->direction[1] = -1;
        model->player->spriteDirection = SpriteDirection::upleft;
    }
    if (up == GLFW_PRESS && right == GLFW_PRESS) {
        model->player->direction[0] = 1;
        model->player->direction[1] = -1;
        model->player->spriteDirection = SpriteDirection::upright;
    }
    if (down == GLFW_PRESS && left == GLFW_PRESS) {
        model->player->direction[0] = -1;
        model->player->direction[1] = 1;
        model->player->spriteDirection = SpriteDirection::downleft;
    }
    if (down == GLFW_PRESS && right == GLFW_PRESS) {
        model->player->direction[0] = 1;
        model->player->direction[1] = 1;
        model->player->spriteDirection = SpriteDirection::downright;
    }

    firecd--;
    if (space == GLFW_PRESS) {
        if(firecd <= 0) {
            model->projectilesPlayer.push_back(
                    new ProjectilePlayer(model->player->pos.x, model->player->pos.y, model->player->direction[0],
                                         model->player->direction[1], model->player->spriteDirection));
            model->projectilesPlayer.push_back(
                    new ProjectilePlayer(model->player->pos.x, model->player->pos.y, model->player->direction[0]*-1,
                                         model->player->direction[1]*-1, model->player->spriteDirection));
            firecd = 10;
        }
    }
    if (escape == GLFW_PRESS) {
        inGame=false;
        view->resetFrame();
        model->player->resetPosition();
        onStart();
        return;
    }

    //spawn new enemys
    spawnEnemys();

    //  calc & move player position
    double playerDirectionVectorLenght = sqrt((pow(model->player->direction[0],2)+pow(model->player->direction[1],2)));
    model->player->pos.x += ((model->player->direction[0]) / playerDirectionVectorLenght) * model->player->playerspeed;
    model->player->pos.y += (model->player->direction[1] / playerDirectionVectorLenght) * model->player->playerspeed;
    if(model->player->pos.x < 0) model->player->pos.x += MAP_WIDTH;
    if(model->player->pos.x >= MAP_WIDTH)model->player->pos.x -= MAP_WIDTH;
    if(model->player->pos.y < 0)model->player->pos.y += MAP_HEIGHT;
    if(model->player->pos.y >= MAP_HEIGHT)model->player->pos.y -= MAP_HEIGHT;

    //  calc & move projectile position
    for(ProjectilePlayer* ele: model->projectilesPlayer) {
        ele->pos.x = model->player->pos.x + ( ProjectilePlayer::projectileSpeed * ele->traveled * ele->direction.x);
        ele->pos.y = model->player->pos.y + ( ProjectilePlayer::projectileSpeed * ele->traveled * ele->direction.y);
        if(ele->pos.x < 0) ele->pos.x += MAP_WIDTH;
        if(ele->pos.x >= MAP_WIDTH) ele->pos.x -= MAP_WIDTH;
        if(ele->pos.y < 0) ele->pos.y += MAP_HEIGHT;
        if(ele->pos.y >= MAP_HEIGHT )ele->pos.y -= MAP_HEIGHT;
        ele->traveled++;
    }


    //  calc & move enemyPink position
    // calc direction
    double degL, degR, degO;

    double ux = 0;
    double uy = 0;
    double vx = 0;
    double vy = 0;
    double minDistance = 0;
    double testDistance = 0;
//    Player
    Position2D playerPos{};
    int playerQuadrant = 1;
    if(model->player->pos.x >= (MAP_WIDTH/2) ) {
        if (model->player->pos.y >= (MAP_HEIGHT/2) ) {
            playerQuadrant = 4;
        } else {
            playerQuadrant = 2;
        }
    } else {
        if (model->player->pos.y >= (MAP_HEIGHT/2) ) {
            playerQuadrant = 3;
        } else {
            playerQuadrant = 1;
        }
    }

    for(ITypeMissile* ele: model->iTypeMissiles) {
        playerPos.x = model->player->pos.x;
        playerPos.y = model->player->pos.y;
        if (ele->turned != 0) {
            ele->turned--;
        } else {
            ele->turned = 3;
            int dir1 = (ele->direction + 1) % 24;
            int dir2 = (ele->direction - 1);
            if (dir2 < 0) dir2 = 23;
            // set values
            //current dir

            ux = ele->directions[ele->direction][0];
            uy = ele->directions[ele->direction][1];


            //player

            switch (playerQuadrant) {
                case 1:
                    minDistance = sqrt(
                            pow((model->player->pos.x - ele->pos.x), 2) + pow((model->player->pos.y - ele->pos.y), 2));
                    testDistance = sqrt(pow((model->player->pos.x + MAP_WIDTH - ele->pos.x), 2) +
                                        pow((model->player->pos.y - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x + MAP_WIDTH;
                        playerPos.y = model->player->pos.y;
                    }
                    testDistance = sqrt(pow((model->player->pos.x - ele->pos.x), 2) +
                                        pow((model->player->pos.y + MAP_HEIGHT - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x;
                        playerPos.y = model->player->pos.y + MAP_HEIGHT;
                    }
                    testDistance = sqrt(pow((model->player->pos.x + MAP_WIDTH - ele->pos.x), 2) +
                                        pow((model->player->pos.y + MAP_HEIGHT - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x + MAP_WIDTH;
                        playerPos.y = model->player->pos.y + MAP_HEIGHT;
                    }
                    break;
                case 2:
                    minDistance = sqrt(
                            pow((model->player->pos.x - ele->pos.x), 2) + pow((model->player->pos.y - ele->pos.y), 2));
                    testDistance = sqrt(pow((model->player->pos.x - MAP_WIDTH - ele->pos.x), 2) +
                                        pow((model->player->pos.y - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x - MAP_WIDTH;
                        playerPos.y = model->player->pos.y;
                    }
                    testDistance = sqrt(pow((model->player->pos.x - ele->pos.x), 2) +
                                        pow((model->player->pos.y + MAP_HEIGHT - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x;
                        playerPos.y = model->player->pos.y + MAP_HEIGHT;
                    }
                    testDistance = sqrt(pow((model->player->pos.x - MAP_WIDTH - ele->pos.x), 2) +
                                        pow((model->player->pos.y + MAP_HEIGHT - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x - MAP_WIDTH;
                        playerPos.y = model->player->pos.y + MAP_HEIGHT;
                    }
                    break;
                case 3:
                    minDistance = sqrt(
                            pow((model->player->pos.x - ele->pos.x), 2) + pow((model->player->pos.y - ele->pos.y), 2));
                    testDistance = sqrt(pow((model->player->pos.x + MAP_WIDTH - ele->pos.x), 2) +
                                        pow((model->player->pos.y - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x + MAP_WIDTH;
                        playerPos.y = model->player->pos.y;
                    }
                    testDistance = sqrt(pow((model->player->pos.x - ele->pos.x), 2) +
                                        pow((model->player->pos.y - MAP_HEIGHT - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x;
                        playerPos.y = model->player->pos.y - MAP_HEIGHT;
                    }
                    testDistance = sqrt(pow((model->player->pos.x + MAP_WIDTH - ele->pos.x), 2) +
                                        pow((model->player->pos.y - MAP_HEIGHT - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x + MAP_WIDTH;
                        playerPos.y = model->player->pos.y - MAP_HEIGHT;
                    }
                    break;
                case 4:
                    minDistance = sqrt(
                            pow((model->player->pos.x - ele->pos.x), 2) + pow((model->player->pos.y - ele->pos.y), 2));
                    testDistance = sqrt(pow((model->player->pos.x - MAP_WIDTH - ele->pos.x), 2) +
                                        pow((model->player->pos.y - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x - MAP_WIDTH;
                        playerPos.y = model->player->pos.y;
                    }
                    testDistance = sqrt(pow((model->player->pos.x - ele->pos.x), 2) +
                                        pow((model->player->pos.y - MAP_HEIGHT - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x;
                        playerPos.y = model->player->pos.y - MAP_HEIGHT;
                    }
                    testDistance = sqrt(pow((model->player->pos.x - MAP_WIDTH - ele->pos.x), 2) +
                                        pow((model->player->pos.y - MAP_HEIGHT - ele->pos.y), 2));
                    if (testDistance < minDistance) {
                        minDistance = testDistance;
                        playerPos.x = model->player->pos.x - MAP_WIDTH;
                        playerPos.y = model->player->pos.y - MAP_HEIGHT;
                    }
                    break;
                default:
                    printf("ERROR in var PlayerQuadrant\n");
            }
            vx = playerPos.x - ele->pos.x;
            vy = playerPos.y - ele->pos.y;

            // calc degree
            degO = acos(((ux * vx) + (uy * vy))
                        / (sqrt(pow(ux, 2) + pow(uy, 2))
                           * sqrt(pow(vx, 2) + pow(vy, 2)))) * 180 / (2 * acos(0.0));

            // set values
            //enemy
            ux = ele->directions[dir1][0];
            uy = ele->directions[dir1][1];
//        printf("%f",ux);
//        printf("%f\n",uy);
//        printf("%f",ele->directions[dir1][0]);
//        printf("%f\n",ele->directions[dir1][1]);
            // calc degree
            degL = acos(((ux * vx) + (uy * vy))
                        / (sqrt(pow(ux, 2) + pow(uy, 2))
                           * sqrt(pow(vx, 2) + pow(vy, 2)))) * 180 / (2 * acos(0.0));

            // set values
            // new double vx,vy;
            ux = ele->directions[dir2][0];
            uy = ele->directions[dir2][1];
//        printf("%f",ux);
//        printf("%f\n",uy);
//        printf("%f",ele->directions[dir2][0]);
//        printf("%f\n",ele->directions[dir2][1]);
            // calc degree
            degR = acos(((ux * vx) + (uy * vy))
                        / (sqrt(pow(ux, 2) + pow(uy, 2))
                           * sqrt(pow(vx, 2) + pow(vy, 2)))) * 180 / (2 * acos(0.0));

            // compare direction

            if (degL < degR && degL < degO) {
                ele->direction = dir1;
            }

            if (degR < degL && degR < degO) {
                ele->direction = dir2;
            } else if (degL < degO) {
                ele->direction = dir1;
            }

//        printf("New Frame\n");
//        printf("dir1 %d\n",dir1);
//        printf("dir2 %d\n",dir2);
//        printf("degO %f\n",degO);
//        printf("degL %f\n",degL);
//        printf("degR %f\n",degR);
//        printf("new Direction %d\n\n",ele->direction);
        }
    }
//     apply movement
    double normalize = 1;
    for(ITypeMissile* ele: model->iTypeMissiles) {
        normalize = sqrt((pow(ele->directions[ele->direction][0],2)+pow(ele->directions[ele->direction][1],2)));
        ele->pos.x += (ele->directions[ele->direction][0] / normalize) * ele->speed;
        ele->pos.y += (ele->directions[ele->direction][1] / normalize) * ele->speed;
        if(ele->pos.x < 0) ele->pos.x += MAP_WIDTH;
        if(ele->pos.x >= MAP_WIDTH)ele->pos.x -= MAP_WIDTH;
        if(ele->pos.y < 0)ele->pos.y += MAP_HEIGHT;
        if(ele->pos.y >= MAP_HEIGHT)ele->pos.y -= MAP_HEIGHT;
    }


//  base open close
    for(EnemyBase* ele: model->enemyBases) {
        if(ele->isOpen) {
            if(ele->timer++ >= 59) {
                ele->isOpen = false;
                ele->timer = 0;
            }
        } else {
            if(ele->timer++ >= 59) {
                ele->isOpen = true;
                ele->timer = 0;
            }
        }
    }

//  move Frame
    view->moveFrame();

//  prepare new frame
    view->prepareFrame();

//    render background
    for(BackgroundPixel* ele: model->pixelarr[(count/30)]) {
        if(move){
            ele->pos.x -= (model->player->direction[0] / playerDirectionVectorLenght) * 4;
            ele->pos.y -= (model->player->direction[1] / playerDirectionVectorLenght) * 4;

        }
        view->renderStars(ele->pos, ((BackgroundPixel::colors+ele->color)));
    }
    for(BackgroundPixel* ele: model->pixelarr[((count/30)+1)%3]) {
        if(move){
            ele->pos.x -= (model->player->direction[0] / playerDirectionVectorLenght) * 4;
            ele->pos.y -= (model->player->direction[1] / playerDirectionVectorLenght) * 4;

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

//    detect mine Collosion player
    double distance;
    for(auto iterator = model->mines.begin(); iterator!= model->mines.end();) {
        distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - model->player->pos.x,2)+pow(iterator._Ptr->_Myval->pos.y - model->player->pos.y,2));
        if(distance <= 64)  {
            model->player->collision = true;
            iterator._Ptr->_Myval->collision = true;
            model->minesExploding.push_back(iterator._Ptr->_Myval);
            iterator._Ptr->_Myval->pos.x += -32;
            iterator._Ptr->_Myval->pos.y += 32;
            iterator = model->mines.erase(iterator);
        } else
            iterator++;
    }
    //    detect mine Collosion iTypeMissiles
    for(auto iteratoriTypeMissiles = model->iTypeMissiles.begin(); iteratoriTypeMissiles!= model->iTypeMissiles.end();) {

    for(auto iterator = model->mines.begin(); iterator!= model->mines.end();) {

        distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - iteratoriTypeMissiles._Ptr->_Myval->pos.x,2)+pow(iterator._Ptr->_Myval->pos.y - iteratoriTypeMissiles._Ptr->_Myval->pos.y,2));
        if(distance <= 64)  {
            iteratoriTypeMissiles._Ptr->_Myval->collision = true;
            iterator._Ptr->_Myval->collision = true;
            model->minesExploding.push_back(iterator._Ptr->_Myval);
            model->iTypeMissilesExploding.push_back(iteratoriTypeMissiles._Ptr->_Myval);
            iterator._Ptr->_Myval->pos.x += -32;
            iterator._Ptr->_Myval->pos.y += 32;
            iterator = model->mines.erase(iterator);


            break;
        } else
            iterator++;
        }
    if(iteratoriTypeMissiles._Ptr->_Myval->collision){
        iteratoriTypeMissiles  = model->iTypeMissiles.erase(iteratoriTypeMissiles);
    }
    else{
        iteratoriTypeMissiles++;
    }

    }
    //    detect iTypeMissiles Collosion

    for(auto iterator = model->iTypeMissiles.begin(); iterator!= model->iTypeMissiles.end();) {
        distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - model->player->pos.x,2)+pow(iterator._Ptr->_Myval->pos.y - model->player->pos.y,2));
        if(distance <= 64)  {
            model->player->collision = true;
            iterator._Ptr->_Myval->collision = true;
            model->iTypeMissilesExploding.push_back(iterator._Ptr->_Myval);
            iterator._Ptr->_Myval->pos.x += -32;
            iterator._Ptr->_Myval->pos.y += 32;
            iterator = model->iTypeMissiles.erase(iterator);
        } else
            iterator++;
    }

//    detect projectile player
    bool hit = false;
    for(auto iterator = model->projectilesPlayer.begin(); iterator!= model->projectilesPlayer.end();) {
        if(iterator._Ptr->_Myval->traveled <= 22) {

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

            if(!hit) {
                for (auto iterator2 = model->iTypeMissiles.begin(); iterator2 != model->iTypeMissiles.end();) {
                    distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - iterator2._Ptr->_Myval->pos.x, 2) +
                                    pow(iterator._Ptr->_Myval->pos.y - iterator2._Ptr->_Myval->pos.y, 2));
                    if (distance <= 32) {
                        iterator2._Ptr->_Myval->collision = true;
                        model->iTypeMissilesExploding.push_back(iterator2._Ptr->_Myval);
                        iterator2 = model->iTypeMissiles.erase(iterator2);
                        delete (iterator._Ptr->_Myval);
                        iterator = model->projectilesPlayer.erase(iterator);
                        hit = true;

                        break;
                    } else
                        iterator2++;
                }
            }
            if (hit) {
                hit = false;
            } else
                iterator++;
        } else {
            delete (iterator._Ptr->_Myval);
            iterator = model->projectilesPlayer.erase(iterator);
        }
    }

//    render exploding mines
    for(auto iterator = model->minesExploding.begin(); iterator!= model->minesExploding.end();) {
        view->render(iterator._Ptr->_Myval->pos+Mine::drawOffset,Mine::spritesExplosion[iterator._Ptr->_Myval->explosionPhase/10]);
        iterator._Ptr->_Myval->explosionPhase++;
        if(iterator._Ptr->_Myval->explosionPhase >= 30) {
            delete (iterator._Ptr->_Myval);
            iterator = model->minesExploding.erase(iterator);
            model->player->score+=Mine::score;
        }else
            iterator++;
    }



    //render exploding iTypeMissile
    for(auto iterator = model->iTypeMissilesExploding.begin(); iterator!= model->iTypeMissilesExploding.end();) {
        if( iterator._Ptr->_Myval->explosionPhase++!=0){
        normalize = sqrt((pow(iterator._Ptr->_Myval->directions[iterator._Ptr->_Myval->direction][0],2)+pow(iterator._Ptr->_Myval->directions[iterator._Ptr->_Myval->direction][1],2)));
        iterator._Ptr->_Myval->pos.x += (iterator._Ptr->_Myval->directions[iterator._Ptr->_Myval->direction][0] / normalize) * iterator._Ptr->_Myval->speed;
        iterator._Ptr->_Myval->pos.y += (iterator._Ptr->_Myval->directions[iterator._Ptr->_Myval->direction][1] / normalize) * iterator._Ptr->_Myval->speed;
        if(iterator._Ptr->_Myval->pos.x < 0) iterator._Ptr->_Myval->pos.x += MAP_WIDTH;
        if(iterator._Ptr->_Myval->pos.x >= MAP_WIDTH)iterator._Ptr->_Myval->pos.x -= MAP_WIDTH;
        if(iterator._Ptr->_Myval->pos.y < 0)iterator._Ptr->_Myval->pos.y += MAP_HEIGHT;
        if(iterator._Ptr->_Myval->pos.y >= MAP_HEIGHT)iterator._Ptr->_Myval->pos.y -= MAP_HEIGHT;
        }
        view->render(iterator._Ptr->_Myval->pos+EnemyShip::drawOffset,ITypeMissile::spritesExplosion[iterator._Ptr->_Myval->explosionPhase/10]);
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
        view->render(ele->pos+Mine::drawOffset,Mine::sprites);
    }

//    render projectiles from player
    for(ProjectilePlayer* ele: model->projectilesPlayer) {
        view->render(ele->pos+ProjectilePlayer::drawOffset,ele->sprite);
    }

    //render enemy
    for(ITypeMissile* ele: model->iTypeMissiles) {
        view->render(ele->pos + EnemyShip::drawOffset, ele->sprites[ele->direction]);
    }


//    render player
    if(model->player->collision) {
        view->render(model->player->pos + Player::drawOffset,
                     Player::spritesExplosion[model->player->spriteLight/10]);
        if(model->player->spriteLight++ == 29) {
            if(model->player->lifes == 0) {
                view->drawString(Position2D{VIEW_WIDTH/2-(4*32+8),GAME_HEIGHT/2-32},"GAME OVER");
                inGame=false;
                model->player->collision = false;
                glfwSwapBuffers(view->window);
                model->player->resetPosition();
                view->resetFrame();
                _sleep(2000);

                glClear(GL_COLOR_BUFFER_BIT);
                return;
            }
            model->player->collision = false;
            model->player->spriteLight = 0;
            model->player->lifes--;
            model->player->resetPosition();
            view->resetFrame();
        }
    } else {
        view->render(model->player->pos+Player::drawOffset,Player::sprites[model->player->spriteDirection][model->player->spriteLight]);
        if(count%30 == 0) {
            model->player->spriteLight = (model->player->spriteLight + 1) % 2;
        }
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
    }






//    draw background right side

    glColor3f(0, 0, 0);
    glRectd(VIEW_WIDTH-8*32,0,VIEW_WIDTH,VIEW_HEIGHT);

    //    draw map
//    view->renderGameInfos(Position2D{1280-300,300},Model::map);
    glRasterPos2d(MAP_POS_X,MAP_POS_Y);
    glDrawPixels(256,400,GL_RGBA,GL_UNSIGNED_BYTE,Model::map);
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
        view->renderGameInfos(Position2D{(double)LIFES_POS_X + (i * 64), LIFES_POS_Y}, Player::sprites[0][0]);
    }


//    testviewpos
    x = view->viewportpos[0] /10;
    y = view->viewportpos[1] /13;
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);
    x = view->viewportpos[2] /10;
    y = view->viewportpos[1] /13;
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);
    x = view->viewportpos[0] /10;
    y = view->viewportpos[3] /13;
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);
    x = view->viewportpos[2] /10;
    y = view->viewportpos[3] /13;
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);

//    draw round
    Position2D roundpos = {ROUND_POS_X,ROUND_POS_Y};
    view->drawString(roundpos,"ROUND 1");
//    set highscore
    if(model->highScore<model->player->score)
        model->highScore = model->player->score;
//    draw highscore
    Position2D highscorePos = {VIEW_WIDTH-(8*32),0+8+32};
    view->drawString(highscorePos,"HI-SCORE");
    Position2D highScorePos = {VIEW_WIDTH-32,0+8+32+32};
    view->drawNumber(highScorePos,model->highScore);
    Position2D oneUp = {VIEW_WIDTH-(6*32),0+8+32+32+32};
    view->drawString(oneUp,"1UP");
    Position2D scorePos = {VIEW_WIDTH-32,0+8+32+32+64};
    view->drawNumber(scorePos,model->player->score);
    Position2D conditionPos = {VIEW_WIDTH-9*32,0+8+32+32+7*32};
    view->drawString(conditionPos,"CONDITION");
    glColor3f(0, 1, 0);
    glRectd(VIEW_WIDTH-8*32,0+8+32+32+7*32+16,VIEW_WIDTH,0+8+32+32+7*32+16+32+16);
    Position2D conditionTypePos = {VIEW_WIDTH-6*32-16,0+8+32+32+7*32+16+32+8};
    view->drawString(conditionTypePos,"GREEN");
    glRasterPos2d(400,400);



}

void Controller::calcCollision(GameObject* ele, std::list<GameObject*> list, bool *isHit) {

}



void Controller::loadSprites() {

//    Lifes
   //getSprite(Model::lifes,"../App_Data/ship_final/life.bmp");


//    Player
    getSprite(Player::sprites[SpriteDirection::up][0],"../App_Data/ship_final/ship_up_light_off.bmp");
    getSprite(Player::sprites[SpriteDirection::up][1],"../App_Data/ship_final/ship_up_light_on.bmp");

    getSprite(Player::sprites[SpriteDirection::upright][1], "../App_Data/ship_final/ship_up_right_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::upright][0], "../App_Data/ship_final/ship_up_right_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::right][1], "../App_Data/ship_final/ship_right_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::right][0], "../App_Data/ship_final/ship_right_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::downright][1], "../App_Data/ship_final/ship_down_right_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::downright][0], "../App_Data/ship_final/ship_down_right_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::down][1], "../App_Data/ship_final/ship_down_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::down][0], "../App_Data/ship_final/ship_down_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::downleft][1], "../App_Data/ship_final/ship_down_left_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::downleft][0], "../App_Data/ship_final/ship_down_left_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::left][1], "../App_Data/ship_final/ship_left_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::left][0], "../App_Data/ship_final/ship_left_light_off.bmp");

    getSprite(Player::sprites[SpriteDirection::upleft][1], "../App_Data/ship_final/ship_up_left_light_on.bmp");
    getSprite(Player::sprites[SpriteDirection::upleft][0], "../App_Data/ship_final/ship_up_left_light_off.bmp");

//    Player explosion
    getSprite(Player::spritesExplosion[0], "../App_Data/ship_explosion_final/ship-explosion-1.bmp");
    getSprite(Player::spritesExplosion[1], "../App_Data/ship_explosion_final/ship-explosion-2.bmp");
    getSprite(Player::spritesExplosion[2], "../App_Data/ship_explosion_final/ship-explosion-3.bmp");

//    Mine and explosion
    getSprite(Mine::sprites, "../App_Data/mine_final/mine.bmp");
    getSprite(Mine::spritesExplosion[0], "../App_Data/mine_explosion_final/mine_explosion_1.bmp");
    getSprite(Mine::spritesExplosion[1], "../App_Data/mine_explosion_final/mine_explosion_2.bmp");
    getSprite(Mine::spritesExplosion[2], "../App_Data/mine_explosion_final/mine_explosion_3.bmp");

//    asteriods and explosion
    getSprite(Asteroid::sprites[0], "../App_Data/asteroid_final/asteroid_1.bmp");
    getSprite(Asteroid::sprites[1], "../App_Data/asteroid_final/asteroid_2.bmp");
    getSprite(Asteroid::sprites[2], "../App_Data/asteroid_final/asteroid_3.bmp");
    getSprite(Asteroid::spritesExplosion[0], "../App_Data/asteroid_explosion_final/asteroid_explosion_1.bmp");
    getSprite(Asteroid::spritesExplosion[1], "../App_Data/asteroid_explosion_final/asteroid_explosion_2.bmp");
    getSprite(Asteroid::spritesExplosion[2], "../App_Data/asteroid_explosion_final/asteroid_explosion_3.bmp");
//    Projectile
    getSprite(ProjectilePlayer::sprites[0], "../App_Data/projectile_final/projectile-1.bmp");
    getSprite(ProjectilePlayer::sprites[1], "../App_Data/projectile_final/projectile-4.bmp");
    getSprite(ProjectilePlayer::sprites[2], "../App_Data/projectile_final/projectile-3.bmp");
    getSprite(ProjectilePlayer::sprites[3], "../App_Data/projectile_final/projectile-2.bmp");

//    enemy Explosion
    getSprite(EnemyShip::spritesExplosion[0], "../App_Data/enemy_explosion_final/enemy-explosion-1.bmp");
    getSprite(EnemyShip::spritesExplosion[1], "../App_Data/enemy_explosion_final/enemy-explosion-2.bmp");
    getSprite(EnemyShip::spritesExplosion[2], "../App_Data/enemy_explosion_final/enemy-explosion-3.bmp");

//    enemyPink
    getSprite(ITypeMissile::sprites[0], "../App_Data/enemy_pink_final/enemy-pink-1.bmp");
    getSprite(ITypeMissile::sprites[1], "../App_Data/enemy_pink_final/enemy-pink-2.bmp");
    getSprite(ITypeMissile::sprites[2], "../App_Data/enemy_pink_final/enemy-pink-3.bmp");
    getSprite(ITypeMissile::sprites[3], "../App_Data/enemy_pink_final/enemy-pink-4.bmp");
    getSprite(ITypeMissile::sprites[4], "../App_Data/enemy_pink_final/enemy-pink-5.bmp");
    getSprite(ITypeMissile::sprites[5], "../App_Data/enemy_pink_final/enemy-pink-6.bmp");
    getSprite(ITypeMissile::sprites[6], "../App_Data/enemy_pink_final/enemy-pink-7.bmp");
    getSprite(ITypeMissile::sprites[7], "../App_Data/enemy_pink_final/enemy-pink-8.bmp");
    getSprite(ITypeMissile::sprites[8], "../App_Data/enemy_pink_final/enemy-pink-9.bmp");
    getSprite(ITypeMissile::sprites[9], "../App_Data/enemy_pink_final/enemy-pink-10.bmp");
    getSprite(ITypeMissile::sprites[10], "../App_Data/enemy_pink_final/enemy-pink-11.bmp");
    getSprite(ITypeMissile::sprites[11], "../App_Data/enemy_pink_final/enemy-pink-12.bmp");
    getSprite(ITypeMissile::sprites[12], "../App_Data/enemy_pink_final/enemy-pink-13.bmp");
    getSprite(ITypeMissile::sprites[13], "../App_Data/enemy_pink_final/enemy-pink-14.bmp");
    getSprite(ITypeMissile::sprites[14], "../App_Data/enemy_pink_final/enemy-pink-15.bmp");
    getSprite(ITypeMissile::sprites[15], "../App_Data/enemy_pink_final/enemy-pink-16.bmp");
    getSprite(ITypeMissile::sprites[16], "../App_Data/enemy_pink_final/enemy-pink-17.bmp");
    getSprite(ITypeMissile::sprites[17], "../App_Data/enemy_pink_final/enemy-pink-18.bmp");
    getSprite(ITypeMissile::sprites[18], "../App_Data/enemy_pink_final/enemy-pink-19.bmp");
    getSprite(ITypeMissile::sprites[19], "../App_Data/enemy_pink_final/enemy-pink-20.bmp");
    getSprite(ITypeMissile::sprites[20], "../App_Data/enemy_pink_final/enemy-pink-21.bmp");
    getSprite(ITypeMissile::sprites[21], "../App_Data/enemy_pink_final/enemy-pink-22.bmp");
    getSprite(ITypeMissile::sprites[22], "../App_Data/enemy_pink_final/enemy-pink-23.bmp");
    getSprite(ITypeMissile::sprites[23], "../App_Data/enemy_pink_final/enemy-pink-24.bmp");

//    base
    getSprite(EnemyBase::sprites[0], "../App_Data/base_final/base-1.bmp");
    getSprite(EnemyBase::sprites[1], "../App_Data/base_final/base-2.bmp");
    getSprite(EnemyBase::sprites[2], "../App_Data/base_final/base-3.bmp");
    getSprite(EnemyBase::sprites[3], "../App_Data/base_final/base-4.bmp");
    getSprite(EnemyBase::sprites[4], "../App_Data/base_final/baseDoor-1.bmp");
    getSprite(EnemyBase::sprites[5], "../App_Data/base_final/baseDoor-2.bmp");
    getSprite(EnemyBase::sprites[6], "../App_Data/base_final/baseDoor-3.bmp");
    getSprite(EnemyBase::sprites[7], "../App_Data/base_final/baseDoor-4.bmp");
    getSprite(EnemyBase::sprites[8], "../App_Data/base_final/baseDoor-5.bmp");
    getSprite(EnemyBase::sprites[10], "../App_Data/base_final/baseDoor-1.bmp");
    getSprite(EnemyBase::sprites[11], "../App_Data/base_final/baseDoor-2.bmp");
    getSprite(EnemyBase::sprites[12], "../App_Data/base_final/baseDoor-3.bmp");
    getSprite(EnemyBase::sprites[13], "../App_Data/base_final/baseDoor-4.bmp");
    getSprite(EnemyBase::sprites[14], "../App_Data/base_final/baseDoor-5.bmp");

//    base explo
    getSprite(EnemyBase::spritesExplosion[0], "../App_Data/base_explosion_final/base-explosion-1.bmp");
    getSprite(EnemyBase::spritesExplosion[1], "../App_Data/base_explosion_final/base-explosion-2.bmp");
    getSprite(EnemyBase::spritesExplosion[2], "../App_Data/base_explosion_final/base-explosion-3.bmp");

//      enemyGreen
//    getSprite(EnemyShip::sprites[0], "../App_Data/enemy_green_final/enemy-green-1.bmp");
//    getSprite(EnemyShip::sprites[1], "../App_Data/enemy_green_final/enemy-green-2.bmp");
//    getSprite(EnemyShip::sprites[2], "../App_Data/enemy_green_final/enemy-green-3.bmp");
//    getSprite(EnemyShip::sprites[3], "../App_Data/enemy_green_final/enemy-green-4.bmp");
//    getSprite(EnemyShip::sprites[4], "../App_Data/enemy_green_final/enemy-green-5.bmp");
//    getSprite(EnemyShip::sprites[5], "../App_Data/enemy_green_final/enemy-green-6.bmp");
//    getSprite(EnemyShip::sprites[6], "../App_Data/enemy_green_final/enemy-green-7.bmp");
//    getSprite(EnemyShip::sprites[7], "../App_Data/enemy_green_final/enemy-green-8.bmp");
//    getSprite(EnemyShip::sprites[8], "../App_Data/enemy_green_final/enemy-green-9.bmp");
//    getSprite(EnemyShip::sprites[9], "../App_Data/enemy_green_final/enemy-green-10.bmp");
//    getSprite(EnemyShip::sprites[10], "../App_Data/enemy_green_final/enemy-green-11.bmp");
//    getSprite(EnemyShip::sprites[11], "../App_Data/enemy_green_final/enemy-green-12.bmp");
//    getSprite(EnemyShip::sprites[12], "../App_Data/enemy_green_final/enemy-green-13.bmp");
//    getSprite(EnemyShip::sprites[13], "../App_Data/enemy_green_final/enemy-green-14.bmp");
//    getSprite(EnemyShip::sprites[14], "../App_Data/enemy_green_final/enemy-green-15.bmp");
//    getSprite(EnemyShip::sprites[15], "../App_Data/enemy_green_final/enemy-green-16.bmp");
//    getSprite(EnemyShip::sprites[16], "../App_Data/enemy_green_final/enemy-green-17.bmp");
//    getSprite(EnemyShip::sprites[17], "../App_Data/enemy_green_final/enemy-green-18.bmp");
//    getSprite(EnemyShip::sprites[18], "../App_Data/enemy_green_final/enemy-green-19.bmp");
//    getSprite(EnemyShip::sprites[19], "../App_Data/enemy_green_final/enemy-green-20.bmp");
//    getSprite(EnemyShip::sprites[20], "../App_Data/enemy_green_final/enemy-green-21.bmp");
//    getSprite(EnemyShip::sprites[21], "../App_Data/enemy_green_final/enemy-green-22.bmp");
//    getSprite(EnemyShip::sprites[22], "../App_Data/enemy_green_final/enemy-green-23.bmp");
//    getSprite(EnemyShip::sprites[23], "../App_Data/enemy_green_final/enemy-green-24.bmp");

//    enemyBlue
    getSprite(PTypeMissile::sprites[0], "../App_Data/enemy_blue_final/enemy-blue-1.bmp");
    getSprite(PTypeMissile::sprites[1], "../App_Data/enemy_blue_final/enemy-blue-2.bmp");
    getSprite(PTypeMissile::sprites[2], "../App_Data/enemy_blue_final/enemy-blue-3.bmp");
    getSprite(PTypeMissile::sprites[3], "../App_Data/enemy_blue_final/enemy-blue-4.bmp");
    getSprite(PTypeMissile::sprites[4], "../App_Data/enemy_blue_final/enemy-blue-5.bmp");
    getSprite(PTypeMissile::sprites[5], "../App_Data/enemy_blue_final/enemy-blue-6.bmp");
    getSprite(PTypeMissile::sprites[6], "../App_Data/enemy_blue_final/enemy-blue-7.bmp");
    getSprite(PTypeMissile::sprites[7], "../App_Data/enemy_blue_final/enemy-blue-8.bmp");
    getSprite(PTypeMissile::sprites[8], "../App_Data/enemy_blue_final/enemy-blue-9.bmp");
    getSprite(PTypeMissile::sprites[9], "../App_Data/enemy_blue_final/enemy-blue-10.bmp");
    getSprite(PTypeMissile::sprites[10], "../App_Data/enemy_blue_final/enemy-blue-11.bmp");
    getSprite(PTypeMissile::sprites[11], "../App_Data/enemy_blue_final/enemy-blue-12.bmp");
    getSprite(PTypeMissile::sprites[12], "../App_Data/enemy_blue_final/enemy-blue-13.bmp");
    getSprite(PTypeMissile::sprites[13], "../App_Data/enemy_blue_final/enemy-blue-14.bmp");
    getSprite(PTypeMissile::sprites[14], "../App_Data/enemy_blue_final/enemy-blue-15.bmp");
    getSprite(PTypeMissile::sprites[15], "../App_Data/enemy_blue_final/enemy-blue-16.bmp");
    getSprite(PTypeMissile::sprites[16], "../App_Data/enemy_blue_final/enemy-blue-17.bmp");
    getSprite(PTypeMissile::sprites[17], "../App_Data/enemy_blue_final/enemy-blue-18.bmp");
    getSprite(PTypeMissile::sprites[18], "../App_Data/enemy_blue_final/enemy-blue-19.bmp");
    getSprite(PTypeMissile::sprites[19], "../App_Data/enemy_blue_final/enemy-blue-20.bmp");
    getSprite(PTypeMissile::sprites[20], "../App_Data/enemy_blue_final/enemy-blue-21.bmp");
    getSprite(PTypeMissile::sprites[21], "../App_Data/enemy_blue_final/enemy-blue-22.bmp");
    getSprite(PTypeMissile::sprites[22], "../App_Data/enemy_blue_final/enemy-blue-23.bmp");
    getSprite(PTypeMissile::sprites[23], "../App_Data/enemy_blue_final/enemy-blue-24.bmp");

//    enemyOrange
//    getSprite(EnemyShip::sprites[0], "../App_Data/enemy_orange_final/enemy-orange-1.bmp");
//    getSprite(EnemyShip::sprites[1], "../App_Data/enemy_orange_final/enemy-orange-2.bmp");
//    getSprite(EnemyShip::sprites[2], "../App_Data/enemy_orange_final/enemy-orange-3.bmp");
//    getSprite(EnemyShip::sprites[3], "../App_Data/enemy_orange_final/enemy-orange-4.bmp");
//    getSprite(EnemyShip::sprites[4], "../App_Data/enemy_orange_final/enemy-orange-5.bmp");
//    getSprite(EnemyShip::sprites[5], "../App_Data/enemy_orange_final/enemy-orange-6.bmp");
//    getSprite(EnemyShip::sprites[6], "../App_Data/enemy_orange_final/enemy-orange-7.bmp");
//    getSprite(EnemyShip::sprites[7], "../App_Data/enemy_orange_final/enemy-orange-8.bmp");
//    getSprite(EnemyShip::sprites[8], "../App_Data/enemy_orange_final/enemy-orange-9.bmp");
//    getSprite(EnemyShip::sprites[9], "../App_Data/enemy_orange_final/enemy-orange-10.bmp");
//    getSprite(EnemyShip::sprites[10], "../App_Data/enemy_orange_final/enemy-orange-11.bmp");
//    getSprite(EnemyShip::sprites[11], "../App_Data/enemy_orange_final/enemy-orange-12.bmp");
//    getSprite(EnemyShip::sprites[12], "../App_Data/enemy_orange_final/enemy-orange-13.bmp");
//    getSprite(EnemyShip::sprites[13], "../App_Data/enemy_orange_final/enemy-orange-14.bmp");
//    getSprite(EnemyShip::sprites[14], "../App_Data/enemy_orange_final/enemy-orange-15.bmp");
//    getSprite(EnemyShip::sprites[15], "../App_Data/enemy_orange_final/enemy-orange-16.bmp");
//    getSprite(EnemyShip::sprites[16], "../App_Data/enemy_orange_final/enemy-orange-17.bmp");
//    getSprite(EnemyShip::sprites[17], "../App_Data/enemy_orange_final/enemy-orange-18.bmp");
//    getSprite(EnemyShip::sprites[18], "../App_Data/enemy_orange_final/enemy-orange-19.bmp");
//    getSprite(EnemyShip::sprites[19], "../App_Data/enemy_orange_final/enemy-orange-20.bmp");
//    getSprite(EnemyShip::sprites[20], "../App_Data/enemy_orange_final/enemy-orange-21.bmp");
//    getSprite(EnemyShip::sprites[21], "../App_Data/enemy_orange_final/enemy-orange-22.bmp");
//    getSprite(EnemyShip::sprites[22], "../App_Data/enemy_orange_final/enemy-orange-23.bmp");
//    getSprite(EnemyShip::sprites[23], "../App_Data/enemy_orange_final/enemy-orange-24.bmp");

//    bomb_orange
    getSprite(ETypeMissile::sprites[0], "../App_Data/bomb_orange_final/bomb-orange-1.bmp");
    getSprite(ETypeMissile::sprites[1], "../App_Data/bomb_orange_final/bomb-orange-2.bmp");
    getSprite(ETypeMissile::sprites[2], "../App_Data/bomb_orange_final/bomb-orange-3.bmp");
    getSprite(ETypeMissile::sprites[3], "../App_Data/bomb_orange_final/bomb-orange-4.bmp");
    getSprite(ETypeMissile::sprites[4], "../App_Data/bomb_orange_final/bomb-orange-5.bmp");
    getSprite(ETypeMissile::sprites[5], "../App_Data/bomb_orange_final/bomb-orange-6.bmp");
    getSprite(ETypeMissile::sprites[6], "../App_Data/bomb_orange_final/bomb-orange-7.bmp");
    getSprite(ETypeMissile::sprites[7], "../App_Data/bomb_orange_final/bomb-orange-8.bmp");
    getSprite(ETypeMissile::sprites[8], "../App_Data/bomb_orange_final/bomb-orange-9.bmp");
    getSprite(ETypeMissile::sprites[9], "../App_Data/bomb_orange_final/bomb-orange-10.bmp");
    getSprite(ETypeMissile::sprites[10], "../App_Data/bomb_orange_final/bomb-orange-11.bmp");
    getSprite(ETypeMissile::sprites[11], "../App_Data/bomb_orange_final/bomb-orange-12.bmp");
    getSprite(ETypeMissile::sprites[12], "../App_Data/bomb_orange_final/bomb-orange-13.bmp");
    getSprite(ETypeMissile::sprites[13], "../App_Data/bomb_orange_final/bomb-orange-14.bmp");
    getSprite(ETypeMissile::sprites[14], "../App_Data/bomb_orange_final/bomb-orange-15.bmp");
    getSprite(ETypeMissile::sprites[15], "../App_Data/bomb_orange_final/bomb-orange-16.bmp");
    getSprite(ETypeMissile::sprites[16], "../App_Data/bomb_orange_final/bomb-orange-17.bmp");
    getSprite(ETypeMissile::sprites[17], "../App_Data/bomb_orange_final/bomb-orange-18.bmp");
    getSprite(ETypeMissile::sprites[18], "../App_Data/bomb_orange_final/bomb-orange-19.bmp");
    getSprite(ETypeMissile::sprites[19], "../App_Data/bomb_orange_final/bomb-orange-20.bmp");
    getSprite(ETypeMissile::sprites[20], "../App_Data/bomb_orange_final/bomb-orange-21.bmp");
    getSprite(ETypeMissile::sprites[21], "../App_Data/bomb_orange_final/bomb-orange-22.bmp");
    getSprite(ETypeMissile::sprites[22], "../App_Data/bomb_orange_final/bomb-orange-23.bmp");
    getSprite(ETypeMissile::sprites[23], "../App_Data/bomb_orange_final/bomb-orange-24.bmp");

//    bomb_green
//    getSprite(EnemyShip::sprites[0], "../App_Data/bomb_green_final/bomb-green-1.bmp");
//    getSprite(EnemyShip::sprites[1], "../App_Data/bomb_green_final/bomb-green-2.bmp");
//    getSprite(EnemyShip::sprites[2], "../App_Data/bomb_green_final/bomb-green-3.bmp");
//    getSprite(EnemyShip::sprites[3], "../App_Data/bomb_green_final/bomb-green-4.bmp");
//    getSprite(EnemyShip::sprites[4], "../App_Data/bomb_green_final/bomb-green-5.bmp");
//    getSprite(EnemyShip::sprites[5], "../App_Data/bomb_green_final/bomb-green-6.bmp");
//    getSprite(EnemyShip::sprites[6], "../App_Data/bomb_green_final/bomb-green-7.bmp");
//    getSprite(EnemyShip::sprites[7], "../App_Data/bomb_green_final/bomb-green-8.bmp");
//    getSprite(EnemyShip::sprites[8], "../App_Data/bomb_green_final/bomb-green-9.bmp");
//    getSprite(EnemyShip::sprites[9], "../App_Data/bomb_green_final/bomb-green-10.bmp");
//    getSprite(EnemyShip::sprites[10], "../App_Data/bomb_green_final/bomb-green-11.bmp");
//    getSprite(EnemyShip::sprites[11], "../App_Data/bomb_green_final/bomb-green-12.bmp");
//    getSprite(EnemyShip::sprites[12], "../App_Data/bomb_green_final/bomb-green-13.bmp");
//    getSprite(EnemyShip::sprites[13], "../App_Data/bomb_green_final/bomb-green-14.bmp");
//    getSprite(EnemyShip::sprites[14], "../App_Data/bomb_green_final/bomb-green-15.bmp");
//    getSprite(EnemyShip::sprites[15], "../App_Data/bomb_green_final/bomb-green-16.bmp");
//    getSprite(EnemyShip::sprites[16], "../App_Data/bomb_green_final/bomb-green-17.bmp");
//    getSprite(EnemyShip::sprites[17], "../App_Data/bomb_green_final/bomb-green-18.bmp");
//    getSprite(EnemyShip::sprites[18], "../App_Data/bomb_green_final/bomb-green-19.bmp");
//    getSprite(EnemyShip::sprites[19], "../App_Data/bomb_green_final/bomb-green-20.bmp");
//    getSprite(EnemyShip::sprites[20], "../App_Data/bomb_green_final/bomb-green-21.bmp");
//    getSprite(EnemyShip::sprites[21], "../App_Data/bomb_green_final/bomb-green-22.bmp");
//    getSprite(EnemyShip::sprites[22], "../App_Data/bomb_green_final/bomb-green-23.bmp");
//    getSprite(EnemyShip::sprites[23], "../App_Data/bomb_green_final/bomb-green-24.bmp");

//    numbers
    getSprite(Model::numbers[0],"../App_Data/numbers_final/Numbers-0.bmp" );
    getSprite(Model::numbers[1],"../App_Data/numbers_final/Numbers-1.bmp" );
    getSprite(Model::numbers[2],"../App_Data/numbers_final/Numbers-2.bmp" );
    getSprite(Model::numbers[3],"../App_Data/numbers_final/Numbers-3.bmp" );
    getSprite(Model::numbers[4],"../App_Data/numbers_final/Numbers-4.bmp" );
    getSprite(Model::numbers[5],"../App_Data/numbers_final/Numbers-5.bmp" );
    getSprite(Model::numbers[6],"../App_Data/numbers_final/Numbers-6.bmp" );
    getSprite(Model::numbers[7],"../App_Data/numbers_final/Numbers-7.bmp" );
    getSprite(Model::numbers[8],"../App_Data/numbers_final/Numbers-8.bmp" );
    getSprite(Model::numbers[9],"../App_Data/numbers_final/Numbers-9.bmp" );


//    alphabet white
    getSprite(Model::alphabetWhite[0],"../App_Data/alphabet_white_final/alphabet_white-1.bmp" );
    getSprite(Model::alphabetWhite[1],"../App_Data/alphabet_white_final/alphabet_white-2.bmp" );
    getSprite(Model::alphabetWhite[2],"../App_Data/alphabet_white_final/alphabet_white-3.bmp" );
    getSprite(Model::alphabetWhite[3],"../App_Data/alphabet_white_final/alphabet_white-4.bmp" );
    getSprite(Model::alphabetWhite[4],"../App_Data/alphabet_white_final/alphabet_white-5.bmp" );
    getSprite(Model::alphabetWhite[5],"../App_Data/alphabet_white_final/alphabet_white-6.bmp" );
    getSprite(Model::alphabetWhite[6],"../App_Data/alphabet_white_final/alphabet_white-7.bmp" );
    getSprite(Model::alphabetWhite[7],"../App_Data/alphabet_white_final/alphabet_white-8.bmp" );
    getSprite(Model::alphabetWhite[8],"../App_Data/alphabet_white_final/alphabet_white-9.bmp" );
    getSprite(Model::alphabetWhite[9],"../App_Data/alphabet_white_final/alphabet_white-10.bmp" );
    getSprite(Model::alphabetWhite[10],"../App_Data/alphabet_white_final/alphabet_white-11.bmp" );
    getSprite(Model::alphabetWhite[11],"../App_Data/alphabet_white_final/alphabet_white-12.bmp" );
    getSprite(Model::alphabetWhite[12],"../App_Data/alphabet_white_final/alphabet_white-13.bmp" );
    getSprite(Model::alphabetWhite[13],"../App_Data/alphabet_white_final/alphabet_white-14.bmp" );
    getSprite(Model::alphabetWhite[14],"../App_Data/alphabet_white_final/alphabet_white-15.bmp" );
    getSprite(Model::alphabetWhite[15],"../App_Data/alphabet_white_final/alphabet_white-16.bmp" );
    getSprite(Model::alphabetWhite[16],"../App_Data/alphabet_white_final/alphabet_white-17.bmp" );
    getSprite(Model::alphabetWhite[17],"../App_Data/alphabet_white_final/alphabet_white-18.bmp" );
    getSprite(Model::alphabetWhite[18],"../App_Data/alphabet_white_final/alphabet_white-19.bmp" );
    getSprite(Model::alphabetWhite[19],"../App_Data/alphabet_white_final/alphabet_white-20.bmp" );
    getSprite(Model::alphabetWhite[20],"../App_Data/alphabet_white_final/alphabet_white-21.bmp" );
    getSprite(Model::alphabetWhite[21],"../App_Data/alphabet_white_final/alphabet_white-22.bmp" );
    getSprite(Model::alphabetWhite[22],"../App_Data/alphabet_white_final/alphabet_white-23.bmp" );
    getSprite(Model::alphabetWhite[23],"../App_Data/alphabet_white_final/alphabet_white-24.bmp" );
    getSprite(Model::alphabetWhite[24],"../App_Data/alphabet_white_final/alphabet_white-25.bmp" );
    getSprite(Model::alphabetWhite[25],"../App_Data/alphabet_white_final/alphabet_white-26.bmp" );
    getSprite(Model::alphabetWhite[26],"../App_Data/alphabet_white_final/alphabet_white-27.bmp" );
    getSprite(Model::alphabetWhite[27],"../App_Data/alphabet_white_final/alphabet_white-28.bmp" );
    getSprite(Model::alphabetWhite[28],"../App_Data/alphabet_white_final/alphabet_white-29.bmp" );

    //    alphabet white
//    getSprite(Model::alphabetBlackNoBorder[0],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-1.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[1],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-2.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[2],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-3.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[3],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-4.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[4],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-5.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[5],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-6.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[6],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-7.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[7],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-8.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[8],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-9.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[9],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-10.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[10],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-11.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[11],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-12.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[12],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-13.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[13],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-14.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[14],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-15.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[15],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-16.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[16],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-17.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[17],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-18.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[18],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-19.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[19],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-20.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[20],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-21.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[21],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-22.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[22],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-23.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[23],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-24.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[24],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-25.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[25],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-26.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[26],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-27.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[27],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-28.bmp" );
//    getSprite(Model::alphabetBlackNoBorder[28],"../App_Data/alphabet_black_no_border_final/alphabet_black_no_border-29.bmp" );

//    alphabet black
    getSprite(Model::alphabetBlack[0],"../App_Data/alphabet_black_final/alphabet_black-1.bmp" );
    getSprite(Model::alphabetBlack[1],"../App_Data/alphabet_black_final/alphabet_black-2.bmp" );
    getSprite(Model::alphabetBlack[2],"../App_Data/alphabet_black_final/alphabet_black-3.bmp" );
    getSprite(Model::alphabetBlack[3],"../App_Data/alphabet_black_final/alphabet_black-4.bmp" );
    getSprite(Model::alphabetBlack[4],"../App_Data/alphabet_black_final/alphabet_black-5.bmp" );
    getSprite(Model::alphabetBlack[5],"../App_Data/alphabet_black_final/alphabet_black-6.bmp" );
    getSprite(Model::alphabetBlack[6],"../App_Data/alphabet_black_final/alphabet_black-7.bmp" );
    getSprite(Model::alphabetBlack[7],"../App_Data/alphabet_black_final/alphabet_black-8.bmp" );
    getSprite(Model::alphabetBlack[8],"../App_Data/alphabet_black_final/alphabet_black-9.bmp" );
    getSprite(Model::alphabetBlack[9],"../App_Data/alphabet_black_final/alphabet_black-10.bmp" );
    getSprite(Model::alphabetBlack[10],"../App_Data/alphabet_black_final/alphabet_black-11.bmp" );
    getSprite(Model::alphabetBlack[11],"../App_Data/alphabet_black_final/alphabet_black-12.bmp" );
    getSprite(Model::alphabetBlack[12],"../App_Data/alphabet_black_final/alphabet_black-13.bmp" );
    getSprite(Model::alphabetBlack[13],"../App_Data/alphabet_black_final/alphabet_black-14.bmp" );
    getSprite(Model::alphabetBlack[14],"../App_Data/alphabet_black_final/alphabet_black-15.bmp" );
    getSprite(Model::alphabetBlack[15],"../App_Data/alphabet_black_final/alphabet_black-16.bmp" );
    getSprite(Model::alphabetBlack[16],"../App_Data/alphabet_black_final/alphabet_black-17.bmp" );
    getSprite(Model::alphabetBlack[17],"../App_Data/alphabet_black_final/alphabet_black-18.bmp" );
    getSprite(Model::alphabetBlack[18],"../App_Data/alphabet_black_final/alphabet_black-19.bmp" );
    getSprite(Model::alphabetBlack[19],"../App_Data/alphabet_black_final/alphabet_black-20.bmp" );
    getSprite(Model::alphabetBlack[20],"../App_Data/alphabet_black_final/alphabet_black-21.bmp" );
    getSprite(Model::alphabetBlack[21],"../App_Data/alphabet_black_final/alphabet_black-22.bmp" );
    getSprite(Model::alphabetBlack[22],"../App_Data/alphabet_black_final/alphabet_black-23.bmp" );
    getSprite(Model::alphabetBlack[23],"../App_Data/alphabet_black_final/alphabet_black-24.bmp" );
    getSprite(Model::alphabetBlack[24],"../App_Data/alphabet_black_final/alphabet_black-25.bmp" );
    getSprite(Model::alphabetBlack[25],"../App_Data/alphabet_black_final/alphabet_black-26.bmp" );
    getSprite(Model::alphabetBlack[26],"../App_Data/alphabet_black_final/alphabet_black-27.bmp" );
    getSprite(Model::alphabetBlack[27],"../App_Data/alphabet_black_final/alphabet_black-28.bmp" );
    getSprite(Model::alphabetBlack[28],"../App_Data/alphabet_black_final/alphabet_black-29.bmp" );

    Model::map = new GLubyte[256*400*4];
    for(int x = 0; x < 256*400*4; x+=4) {
            Model::map[x+0] = 125;
            Model::map[x+1] = 0;
            Model::map[x+2] = 125;
            Model::map[x+3] = 255;
    }
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

    for(int i = 8; i < filesize; i+=4) {
        swap = dst[i];
        dst[i] = dst[i+2];
        dst[i+2] = swap;
    }

    fclose(file);
    return 0;
}
