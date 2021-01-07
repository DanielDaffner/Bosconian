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
    model->player->pos.x += model->player->direction[0] * model->player->playerspeed;
    model->player->pos.y += model->player->direction[1] * model->player->playerspeed;

    // here
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
    //  calc direction
    double degL, degR, degO;

    double ux[3] = {};
    double uy[3] = {};
    double vx = {};
    double vy = {};

    for(EnemyShip* ele: model->enemyShipsPink) {

        //turn every 3 ticks

        ele->turned--;
        if(ele->turned>0)break;
        ele->turned=3;

        //possible directions for enemyShip

        int dir0=ele->direction;
        int dir1=(ele->direction + 1)%8;
        int dir2=(ele->direction - 1);

        if(dir2<0)dir2=7;

        int dir[3] = {dir0,dir1,dir2};

        // set values
        //enemy dir
        for(int i = 0; i<3;i++){
        ux[i]= ele->directions[dir[i]][0];
        uy[i]= ele->directions[dir[i]][1];
        }


        //get map quarter
        int qX=0;
        int qY=0;

        if(ele->pos.x>MAP_WIDTH/2){
            qX=1;
        }
        if(ele->pos.y>MAP_HEIGHT/2){
            qY=1;
        }
        //4 virtual ships
        int offsets[4][3][2] = { {{-MAP_WIDTH,-MAP_HEIGHT},{0,-MAP_HEIGHT},{-MAP_WIDTH,0}},
                                 {{0,-MAP_HEIGHT},{MAP_WIDTH,-MAP_HEIGHT},{MAP_WIDTH,0}},
                                 {{-MAP_WIDTH,0},{-MAP_WIDTH,MAP_HEIGHT},{0,MAP_HEIGHT}},
                                 {{MAP_WIDTH,0},{MAP_WIDTH,MAP_HEIGHT},{0,MAP_HEIGHT}}};

        vx = (model->player->pos.x) - ele->pos.x;
        vy = (model->player->pos.y) - ele->pos.y;

        if(qX==0&&qY==0){
           // printf("quarter 1\n");
            for(int i = 1; i <4;i++) {


                double tmpX =  (model->player->pos.x + offsets[0][i-1][0]) - ele->pos.x;
                double tmpY = (model->player->pos.y + offsets[0][i-1][1]) - ele->pos.y;

                double vecOld = sqrt(pow(vx,2)+pow(vy,2));
                double vecNew = sqrt(pow(tmpX,2)+pow(tmpY,2));

                if(vecNew<vecOld ) {
                    vx = tmpX;
                    vy = tmpY;
                   // printf("ship %d\n",i);
                }

            }
        }
        if(qX==1&&qY==0){

            for(int i = 1; i <4;i++) {
                double tmpX =  (model->player->pos.x + offsets[1][i-1][0]) - ele->pos.x;
                double tmpY = (model->player->pos.y + offsets[1][i-1][1]) - ele->pos.y;
                double vecOld = sqrt(pow(vx,2)+pow(vy,2));
                double vecNew = sqrt(pow(tmpX,2)+pow(tmpY,2));

                if(abs(vecNew)<abs(vecOld) ) {
                    vx = tmpX;
                    vy = tmpY;
                 //   printf("ship %d\n",i);
                }

            }
        }
        if(qX==0&&qY==1){

            for(int i = 1; i <4;i++) {
                double tmpX =  (model->player->pos.x + offsets[2][i-1][0]) - ele->pos.x;
                double tmpY =(model->player->pos.y + offsets[2][i-1][1]) - ele->pos.y;
                double vecOld = sqrt(pow(vx,2)+pow(vy,2));
                double vecNew = sqrt(pow(tmpX,2)+pow(tmpY,2));

                if(abs(vecNew)<abs(vecOld) ) {
                    vx = tmpX;
                    vy = tmpY;

                }

            }
        }
        if(qX==1&&qY==1){
           // printf("quarter 4\n");
            for(int i = 1; i <4;i++) {

                double tmpX = (model->player->pos.x + offsets[3][i-1][0]) - ele->pos.x;
                double tmpY = (model->player->pos.y + offsets[3][i-1][1]) - ele->pos.y;
                double vecOld = sqrt(pow(vx,2)+pow(vy,2));
                double vecNew = sqrt(pow(tmpX,2)+pow(tmpY,2));

                if(abs(vecNew)<abs(vecOld) ) {
                vx = tmpX;
                vy = tmpY;
                  //  printf("ship %d\n",i);
                }

            }
        }

        // calc degree
        double deg[3];
        for(int j= 0; j < 3; j++){

        deg[j]=     acos(((ux[j]*vx)+(uy[j]*vy))
                  / (sqrt(pow(ux[j],2)+pow(uy[j],2))
                  *  sqrt(pow(vx,2)+pow(vy,2))))*180/ (2*acos(0.0));
        }

        if(deg[1] < deg[2] && deg[1] < deg[0]){
            ele->direction=dir1;
        }

        if(deg[2] < deg[1] && deg[2] < deg[0]){
            ele->direction=dir2;
        }
        else if(deg[1] < deg[0]){
            ele->direction=dir1;
        }
    }

    // apply movement

    for(EnemyShip* ele: model->enemyShipsPink) {
        ele->pos.x += ele->directions[ele->direction][0] * ele->speed;
        ele->pos.y += ele->directions[ele->direction][1] * ele->speed;
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
        view->renderGameInfos(Position2D{LIFES_POS_X+(i*64), LIFES_POS_Y}, Player::sprites[SpriteDirection::up][SpriteLights::off]);
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

    getSprite(Player::spritesExplosion[0], "../App_Data/ship_explosion_bmp/ship_explosion_1.bmp");
    getSprite(Player::spritesExplosion[1], "../App_Data/ship_explosion_bmp/ship_explosion_2.bmp");
    getSprite(Player::spritesExplosion[2], "../App_Data/ship_explosion_bmp/ship_explosion_3.bmp");

    getSprite(Mine::sprites, "../App_Data/mine_bmp/mine.bmp");
    getSprite(Mine::spritesExplosion[0], "../App_Data/mine_explosion_bmp/mine_explosion_1.bmp");
    getSprite(Mine::spritesExplosion[1], "../App_Data/mine_explosion_bmp/mine_explosion_2.bmp");
    getSprite(Mine::spritesExplosion[2], "../App_Data/mine_explosion_bmp/mine_explosion_3.bmp");

    getSprite(ProjectilePlayer::sprites[0], "../App_Data/projectile_bmp/projectile-1.bmp");
    getSprite(ProjectilePlayer::sprites[1], "../App_Data/projectile_bmp/projectile-4.bmp");
    getSprite(ProjectilePlayer::sprites[2], "../App_Data/projectile_bmp/projectile-3.bmp");
    getSprite(ProjectilePlayer::sprites[3], "../App_Data/projectile_bmp/projectile-2.bmp");

    //enemyPink
    getSprite(EnemyShip::sprites[0], "../App_Data/enemy_pink_bmp/enemy-pink-1.bmp");

    getSprite(EnemyShip::sprites[1], "../App_Data/enemy_pink_bmp/enemy-pink-4.bmp");

    getSprite(EnemyShip::sprites[2], "../App_Data/enemy_pink_bmp/enemy-pink-7.bmp");


    getSprite(EnemyShip::sprites[3], "../App_Data/enemy_pink_bmp/enemy-pink-10.bmp");

    getSprite(EnemyShip::sprites[4], "../App_Data/enemy_pink_bmp/enemy-pink-13.bmp");

    getSprite(EnemyShip::sprites[5], "../App_Data/enemy_pink_bmp/enemy-pink-16.bmp");

    getSprite(EnemyShip::sprites[6], "../App_Data/enemy_pink_bmp/enemy-pink-19.bmp");

    getSprite(EnemyShip::sprites[7], "../App_Data/enemy_pink_bmp/enemy-pink-22.bmp");
    
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

    for(int i = *((uint16_t*)(dst+10)); i < filesize; i+=4) {
        swap = dst[i];
        dst[i] = dst[i+2];
        dst[i+2] = swap;
    }

    fclose(file);
    return 0;
}

