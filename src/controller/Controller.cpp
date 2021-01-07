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
    getSprite(enemyPink,"../App_Data/enemy_pink_final/enemy-pink-16.bmp");
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

    view->render(enemyPos,enemyPink);
    enemyPos.x+=2;
    enemyPos.y+=2;
    if(enemyPos.y >=730) enemyPos = {-300,100};
}

void Controller::onStart(){
    int x;
    int y;
    int distance;
    for(int i = 0; i < 120;i++) {
        x = (rand() % (MAP_WIDTH));
        y = (rand() % (MAP_HEIGHT));
        distance = sqrt(pow(x - model->player->pos.x,2)+pow(y - model->player->pos.y,2));

        if(distance > 64 )
        model->mines.push_back(new Mine(x,y));
        else printf("protected\n");
    }

    model->enemyShipsPink.push_back(new EnemyShip(MAP_WIDTH / 2,(MAP_HEIGHT / 4) * 3,1));
    model->enemyBases.push_back(new EnemyBase(500,500));

};

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
        return;
    }

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

    for(EnemyShip* ele: model->enemyShipsPink) {
        ele->turned--;
        if(ele->turned>0)break;
        ele->turned=3;


        int dir1 = (ele->direction + 1) % 24;
        int dir2 = (ele->direction - 1);
        if(dir2 < 0) dir2 = 23;
        // set values
        //current dir
        int peter = ele->direction;
        ux = ele->directions[peter][0];
        uy = ele->directions[peter][1];


        //player
        vx = model->player->pos.x - ele->pos.x;
        vy = model->player->pos.y - ele->pos.y;
        // calc degree
        degO=     acos(((ux*vx)+(uy*vy))
                  / (sqrt(pow(ux,2)+pow(uy,2))
                  *  sqrt(pow(vx,2)+pow(vy,2))))*180/ (2*acos(0.0));

        // set values
        //enemy
        ux=ele->directions[dir1][0];
        uy=ele->directions[dir1][1];
//        printf("%f",ux);
//        printf("%f\n",uy);
//        printf("%f",ele->directions[dir1][0]);
//        printf("%f\n",ele->directions[dir1][1]);
        // calc degree
        degL=    acos( ((ux*vx)+(uy*vy))
                / (sqrt(pow(ux,2)+pow(uy,2))
                *  sqrt(pow(vx,2)+pow(vy,2)))) *180/ (2*acos(0.0));

        // set values
        // new double vx,vy;
        ux=ele->directions[dir2][0];
        uy=ele->directions[dir2][1];
//        printf("%f",ux);
//        printf("%f\n",uy);
//        printf("%f",ele->directions[dir2][0]);
//        printf("%f\n",ele->directions[dir2][1]);
        // calc degree
        degR=      acos( ((ux*vx)+(uy*vy))
                  / (sqrt(pow(ux,2)+pow(uy,2))
                  *  sqrt(pow(vx,2)+pow(vy,2)))) *180/ (2*acos(0.0));

        // compare direction

        if(degL < degR && degL < degO){
            ele->direction=dir1;
        }

        if(degR < degL && degR < degO){
            ele->direction=dir2;
        }
        else if(degL < degO){
            ele->direction=dir1;
        }

//        printf("New Frame\n");
//        printf("dir1 %d\n",dir1);
//        printf("dir2 %d\n",dir2);
//        printf("degO %f\n",degO);
//        printf("degL %f\n",degL);
//        printf("degR %f\n",degR);
//        printf("new Direction %d\n\n",ele->direction);
    }

    // apply movement
    double normalize = 1;
    for(EnemyShip* ele: model->enemyShipsPink) {
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
                    model->player->score += Mine::score;
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
    for(EnemyShip* ele: model->enemyShipsPink) {
        view->render(ele->pos+EnemyShip::drawOffset,ele->sprites[ele->direction]);
    }


//    render player
    if(model->player->collision) {
        view->render(model->player->pos + Player::drawOffset + Position2D{-32,32},
                     Player::spritesExplosion[model->player->spriteLight/10]);
        if(model->player->spriteLight++ == 29) {
            if(model->player->lifes == 0) {
                view->drawString(model->player->pos+Position2D{-144,-40},"GAME OVER");
                inGame=false;
                model->player->collision = false;
                glfwSwapBuffers(view->window);
                model->player->resetPosition();
                view->resetFrame();
                _sleep(1000);
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
        if(ele->isOpen) {
            view->render(ele->pos + Player::drawOffset, Player::sprites[ele->timer/10+1][0]);
        } else {
            view->render(ele->pos + Player::drawOffset, Player::sprites[0][0]);
        }
        for(EnemyBasePart* ele2: ele->parts) {
            view->render(ele2->pos+Player::drawOffset,Player::sprites[0][0]);
        }
    }

//    draw lifes
    for(int i = 0; i < model->player->lifes; i++) {
        view->renderGameInfos(Position2D{(double)LIFES_POS_X + (i * 64), LIFES_POS_Y}, Player::sprites[SpriteDirection::up][SpriteLights::off]);
    }

//    draw map
//    view->renderGameInfos(Position2D{1280-300,300},Model::map);
    glRasterPos2d(MAP_POS_X,MAP_POS_Y);
    glDrawPixels(256,400,GL_RGBA,GL_UNSIGNED_BYTE,Model::map);
    int x = model->player->pos.x /10;
    int y = model->player->pos.y /13;
    GLubyte testpix[4] = {255,255,255,255};
    glRasterPos2d(MAP_POS_X+x,MAP_POS_Y-400+y);
    glDrawPixels(1,1,GL_RGBA,GL_UNSIGNED_BYTE,testpix);

//    testviewpos todo
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
    view->drawString(roundpos,"ROUND AB");

//    draw highscore
    Position2D highscorePos = {VIEW_WIDTH-(8*32),0+8+32};
    view->drawString(highscorePos,"HI SCORE");
    glRasterPos2d(400,400);

}
void Controller::loadSprites() {

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

    getSprite(Player::spritesExplosion[0], "../App_Data/ship_explosion_final/ship_explosion_1.bmp");
    getSprite(Player::spritesExplosion[1], "../App_Data/ship_explosion_final/ship_explosion_2.bmp");
    getSprite(Player::spritesExplosion[2], "../App_Data/ship_explosion_final/ship_explosion_3.bmp");

    getSprite(Mine::sprites, "../App_Data/mine_final/mine.bmp");
    getSprite(Mine::spritesExplosion[0], "../App_Data/mine_explosion_final/mine_explosion_1.bmp");
    getSprite(Mine::spritesExplosion[1], "../App_Data/mine_explosion_final/mine_explosion_2.bmp");
    getSprite(Mine::spritesExplosion[2], "../App_Data/mine_explosion_final/mine_explosion_3.bmp");

    getSprite(ProjectilePlayer::sprites[0], "../App_Data/projectile_final/projectile-1.bmp");
    getSprite(ProjectilePlayer::sprites[1], "../App_Data/projectile_final/projectile-4.bmp");
    getSprite(ProjectilePlayer::sprites[2], "../App_Data/projectile_final/projectile-3.bmp");
    getSprite(ProjectilePlayer::sprites[3], "../App_Data/projectile_final/projectile-2.bmp");

    //enemyPink
    getSprite(EnemyShip::sprites[0], "../App_Data/enemy_pink_final/enemy-pink-1.bmp");
    getSprite(EnemyShip::sprites[1], "../App_Data/enemy_pink_final/enemy-pink-2.bmp");
    getSprite(EnemyShip::sprites[2], "../App_Data/enemy_pink_final/enemy-pink-3.bmp");
    getSprite(EnemyShip::sprites[3], "../App_Data/enemy_pink_final/enemy-pink-4.bmp");
    getSprite(EnemyShip::sprites[4], "../App_Data/enemy_pink_final/enemy-pink-5.bmp");
    getSprite(EnemyShip::sprites[5], "../App_Data/enemy_pink_final/enemy-pink-6.bmp");
    getSprite(EnemyShip::sprites[6], "../App_Data/enemy_pink_final/enemy-pink-7.bmp");
    getSprite(EnemyShip::sprites[7], "../App_Data/enemy_pink_final/enemy-pink-8.bmp");
    getSprite(EnemyShip::sprites[8], "../App_Data/enemy_pink_final/enemy-pink-9.bmp");
    getSprite(EnemyShip::sprites[9], "../App_Data/enemy_pink_final/enemy-pink-10.bmp");
    getSprite(EnemyShip::sprites[10], "../App_Data/enemy_pink_final/enemy-pink-11.bmp");
    getSprite(EnemyShip::sprites[11], "../App_Data/enemy_pink_final/enemy-pink-12.bmp");
    getSprite(EnemyShip::sprites[12], "../App_Data/enemy_pink_final/enemy-pink-13.bmp");
    getSprite(EnemyShip::sprites[13], "../App_Data/enemy_pink_final/enemy-pink-14.bmp");
    getSprite(EnemyShip::sprites[14], "../App_Data/enemy_pink_final/enemy-pink-15.bmp");
    getSprite(EnemyShip::sprites[15], "../App_Data/enemy_pink_final/enemy-pink-16.bmp");
    getSprite(EnemyShip::sprites[16], "../App_Data/enemy_pink_final/enemy-pink-17.bmp");
    getSprite(EnemyShip::sprites[17], "../App_Data/enemy_pink_final/enemy-pink-18.bmp");
    getSprite(EnemyShip::sprites[18], "../App_Data/enemy_pink_final/enemy-pink-19.bmp");
    getSprite(EnemyShip::sprites[19], "../App_Data/enemy_pink_final/enemy-pink-20.bmp");
    getSprite(EnemyShip::sprites[20], "../App_Data/enemy_pink_final/enemy-pink-21.bmp");
    getSprite(EnemyShip::sprites[21], "../App_Data/enemy_pink_final/enemy-pink-22.bmp");
    getSprite(EnemyShip::sprites[22], "../App_Data/enemy_pink_final/enemy-pink-23.bmp");
    getSprite(EnemyShip::sprites[23], "../App_Data/enemy_pink_final/enemy-pink-24.bmp");

    //alphabet

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

    for(int i = 2; i < filesize; i+=4) {
        swap = dst[i];
        dst[i] = dst[i+2];
        dst[i+2] = swap;
    }

    fclose(file);
    return 0;
}

