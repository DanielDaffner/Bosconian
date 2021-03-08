//
// Created by basti on 11.12.2020.
//
#include "../../include/controller/Controller.h"

#include <iostream>
#include <cmath>
#include <string>
#include <chrono>


Controller::Controller() {
    model = new Model();
    soundControl = new SoundControl();
    inGame = false;
    view = new View(model);
    level = 1;
    view->createMainWindow();
    run();
}
void Controller::run() {
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    int sleeptime = 0;

    while (!glfwWindowShouldClose(view->window )) {
        /* Loop until the user closes the window */
        if(glfwWindowShouldClose(view->window)) {
            glfwTerminate();
            return;
        }

        if (!inGame) {
            /* Render here */
            updateMainWindow();
            /* Swap front and back buffers */
            glfwSwapBuffers(view->window);

            /* Poll for and process events */
            glfwPollEvents();
            _sleep(17);
        }

        if (inGame) {
            start = std::chrono::system_clock::now();

            updateGameWindow();

            glfwSwapBuffers(view->window);

            glfwPollEvents();

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            sleeptime = 8 - (int) (elapsed_seconds.count() * 1000);
            if (sleeptime < 0) {
                printf("%d",sleeptime);
                sleeptime = 0;
                printf("givememoretime\n");
            }
            _sleep(sleeptime);
        }
    }
}

void Controller::updateMainWindow() {
    int space = glfwGetKey(view->window, GLFW_KEY_SPACE);
    if (space == GLFW_PRESS) {
        inGame = true;
        onStart();
    }
    view->updateMainwindow();
}

void Controller::onStart() {

    model->mines.clear();
    model->iTypeMissiles.clear();
    model->minesExploding.clear();
    model->iTypeMissilesExploding.clear();
    model->formations.clear();
    model->enemyBases.clear();
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
    }
    for(int i = 0; i < 5;i++) {
        x = (rand() % (MAP_WIDTH));
        y = (rand() % (MAP_HEIGHT));
        distance = sqrt(pow(x - model->player->pos.x,2)+pow(y - model->player->pos.y,2));

        if(distance > 255 )
            model->iTypeMissiles.push_back(new ITypeMissile(x, y, 1));
    }
//    model->enemyShipsPink.push_back(new ITypeMissile(MAP_WIDTH / 2,(MAP_HEIGHT / 4) * 3,1));
    model->formations.push_back(new Formation(1500,3500,0));
    loadLevel();
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

    model->player->firecd--;
    if (space == GLFW_PRESS) {
        if(model->player->firecd <= 0) {
            soundControl->play(SoundControl::BLAST);
            model->projectilesPlayer.push_back(
                    new ProjectilePlayer((int)model->player->pos.x, (int)model->player->pos.y, model->player->direction[0],
                                         model->player->direction[1], model->player->spriteDirection));
            model->projectilesPlayer.push_back(
                    new ProjectilePlayer((int)model->player->pos.x, (int)model->player->pos.y, model->player->direction[0]*-1,
                                         model->player->direction[1]*-1, model->player->spriteDirection));
            model->player->firecd = 10;
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
    //spawnEnemys();

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

            // calc degree
            degL = acos(((ux * vx) + (uy * vy))
                        / (sqrt(pow(ux, 2) + pow(uy, 2))
                           * sqrt(pow(vx, 2) + pow(vy, 2)))) * 180 / (2 * acos(0.0));

            // set values
            // new double vx,vy;
            ux = ele->directions[dir2][0];
            uy = ele->directions[dir2][1];

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
        }
    }

//     apply movement for iType ships
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
//  calc angle formation and move
    for(Formation* ele: model->formations) {
        int i = 0;
        calcdirection(ele->leader,playerQuadrant);
        normalize = sqrt((pow(ele->leader->directions[ele->leader->direction][0],2)+pow(ele->leader->directions[ele->leader->direction][1],2)));
        ele->leader->pos.x += (ele->leader->directions[ele->leader->direction][0] / normalize) * ele->leader->speed;
        ele->leader->pos.y += (ele->leader->directions[ele->leader->direction][1] / normalize) * ele->leader->speed;
        if(ele->leader->pos.x < 0) ele->leader->pos.x += MAP_WIDTH;
        if(ele->leader->pos.x >= MAP_WIDTH)ele->leader->pos.x -= MAP_WIDTH;
        if(ele->leader->pos.y < 0)ele->leader->pos.y += MAP_HEIGHT;
        if(ele->leader->pos.y >= MAP_HEIGHT)ele->leader->pos.y -= MAP_HEIGHT;
        for(GameObject* ele2: ele->follower) {
            ele2->pos = ele->leader->pos + (Formation::formationOffset[ele->formationType][i++] * 64);
            if(ele2->pos.x < 0) ele2->pos.x += MAP_WIDTH;
            if(ele2->pos.x >= MAP_WIDTH)ele2->pos.x -= MAP_WIDTH;
            if(ele2->pos.y < 0)ele2->pos.y += MAP_HEIGHT;
            if(ele2->pos.y >= MAP_HEIGHT)ele2->pos.y -= MAP_HEIGHT;
        }
    }


//  base open close
    for(EnemyBase* ele: model->enemyBases) {
        if(ele->isOpen) {
            if(ele->timer++ >= 119) {
                ele->isOpen = false;
                ele->timer = 0;
            }
        } else {
            if(ele->timer++ >= 119) {
                ele->isOpen = true;
                ele->timer = 0;
            }
        }
        //printf("timer: %d\n", ele->timer);
    }

//  move Frame
    view->moveFrame();

//  prepare new frame
    view->prepareFrame();

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
            } else {
                iterator++;
            }
        }
        if(iteratoriTypeMissiles._Ptr->_Myval->collision){
            iteratoriTypeMissiles  = model->iTypeMissiles.erase(iteratoriTypeMissiles);
        }
        else {
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
        } else {
            iterator++;
        }
    }

//    detect projectile player
    bool hit = false;
    for(auto iterator = model->projectilesPlayer.begin(); iterator!= model->projectilesPlayer.end();) {
        if(iterator._Ptr->_Myval->traveled <= 22) {
            //check mines
            for (auto iterator2 = model->mines.begin(); iterator2 != model->mines.end();) {
                distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - iterator2._Ptr->_Myval->pos.x, 2) +
                                pow(iterator._Ptr->_Myval->pos.y - iterator2._Ptr->_Myval->pos.y, 2));
                if (distance <= 32) {
                    iterator2._Ptr->_Myval->collision = true;
                    model->minesExploding.push_back(iterator2._Ptr->_Myval);
                    iterator2._Ptr->_Myval->pos.x += -32;
                    iterator2._Ptr->_Myval->pos.y += 32;
                    iterator2 = model->mines.erase(iterator2);
                    hit = true;

                    break;
                } else
                    iterator2++;
            }
            //check enemy bases
            if(!hit) {
                for (auto iterator2 = model->enemyBases.begin(); iterator2 != model->enemyBases.end();) {
                    for (auto iterator3 = iterator2._Ptr->_Myval->parts.begin(); iterator3 != iterator2._Ptr->_Myval->parts.end();) {
                        distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - iterator3._Ptr->_Myval->pos.x, 2) +
                                        pow(iterator._Ptr->_Myval->pos.y - iterator3._Ptr->_Myval->pos.y, 2));
                        if (distance <= 32) {
                            iterator3._Ptr->_Myval->collision = true;
                            model->enemyBasePartsExploding.push_back(iterator3._Ptr->_Myval);
//                            iterator2._Ptr->_Myval->pos.x += -32;
//                            iterator2._Ptr->_Myval->pos.y += 32;
                            iterator3 = iterator2._Ptr->_Myval->parts.erase(iterator3);
                            hit = true;
//
                            break;
                        } else
                            iterator3++;
                    }
                    if(hit){
                        if(iterator2._Ptr->_Myval->parts.empty()) {
                            model->enemyBasesExploding.push_back(iterator2._Ptr->_Myval);
                            model->enemyBases.erase(iterator2);
                        }
                        break;
                    }
                    else iterator2++;
                }
            }
            // check iType Missiles
            if(!hit) {
                for (auto iterator2 = model->iTypeMissiles.begin(); iterator2 != model->iTypeMissiles.end();) {
                    distance = sqrt(pow(iterator._Ptr->_Myval->pos.x - iterator2._Ptr->_Myval->pos.x, 2) +
                                    pow(iterator._Ptr->_Myval->pos.y - iterator2._Ptr->_Myval->pos.y, 2));
                    if (distance <= 32) {
                        iterator2._Ptr->_Myval->collision = true;
                        model->iTypeMissilesExploding.push_back(iterator2._Ptr->_Myval);
                        iterator2 = model->iTypeMissiles.erase(iterator2);
                        hit = true;

                        break;
                    } else
                        iterator2++;
                }
            }
            if (hit) {
                hit = false;
                delete (iterator._Ptr->_Myval);
                iterator = model->projectilesPlayer.erase(iterator);
            } else
                iterator++;
        } else {
            delete (iterator._Ptr->_Myval);
            iterator = model->projectilesPlayer.erase(iterator);
        }
    }
    view->update(inGame);
}

void Controller::calcdirection(EnemyShip* ele, int playerQuadrant) {
    double degL, degR, degO;

    double ux = 0;
    double uy = 0;
    double vx = 0;
    double vy = 0;
    double minDistance = 0;
    double testDistance = 0;

//    Player
    Position2D playerPos{};

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

        // calc degree
        degL = acos(((ux * vx) + (uy * vy))
                    / (sqrt(pow(ux, 2) + pow(uy, 2))
                       * sqrt(pow(vx, 2) + pow(vy, 2)))) * 180 / (2 * acos(0.0));

        // set values
        // new double vx,vy;
        ux = ele->directions[dir2][0];
        uy = ele->directions[dir2][1];

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
    }
}

int Controller::loadLevel() {
    std::string path = "../App_Data/levels/level";
    int filesize;
    path.append(std::to_string(level));
    FILE* file = fopen(path.c_str(), "r");
    fseek(file,0,SEEK_END);
    filesize = ftell(file);
    fseek(file,0,SEEK_SET);
    char* buf = new char[filesize];
    fread(buf, sizeof(GLubyte), filesize, file);
    for(int i = 0; i < filesize/10; i++) {
        int x = (*((uint8_t*)(buf+(i*10)))-'0') * 1000 + (*((uint8_t*)(buf+1+(i*10)))-'0') * 100 + (*((uint8_t*)(buf+2+(i*10)))-'0') * 10 + *((uint8_t*)(buf+3+(i*10)))-'0';
        int y = (*((uint8_t*)(buf+5+(i*10)))-'0') * 1000 + (*((uint8_t*)(buf+6+(i*10)))-'0') * 100 + (*((uint8_t*)(buf+7+(i*10)))-'0') * 10 + *((uint8_t*)(buf+8+(i*10)))-'0';
        model->enemyBases.push_back(new EnemyBase(x,y));
    }
    return 0;
}