//
// Created by basti on 11.12.2020.
//
#include "../../libs/glfw-3.3.2/include/GLFW/glfw3.h"
#include <gl/GL.h>
#include "../model/Model.h"

#ifndef BOSCONIAN_VIEW_H
#define BOSCONIAN_VIEW_H


class View{
public:
    View(Model* modl);
    Model* model;
    GLFWwindow* window{};
    double viewportpos[4]{};
    bool backgroundmove;
    Position2D enemyPos= {-300,100};
    int count = 0;
    int createMainWindow();
    void prepareFrame();
    void moveFrame();
    void update(bool &inGame);
    void updateMainwindow();
    void loadSprites();
    void loadSprite(GLubyte* &dst, char* filepath);
    void render(Position2D pos, GLubyte* bitmap);
    void renderGameInfos(Position2D pos, GLubyte* bitmap);
    void renderStars(Position2D pos, GLubyte* bitmap);
    void drawString(Position2D pos, char* input);
    void drawNumber(Position2D pos,int number);
    void resetFrame();

    GLubyte* asteroidsSprites[3];
    GLubyte* asteroidsSpritesExplosion[3];
    GLubyte* enemyBaseSprites[16];
    GLubyte* enemyBaseSpritesExplosion[3];
    GLubyte* enemyShipSpritesExplosion[3];
    GLubyte* enemyShipSprites[3][24];
    GLubyte* enemyShipLeaderSprites[3][24];
    GLubyte* minesSprite;
    GLubyte* mineSpritesExplosion[3];
    GLubyte* playerSprites[9][2];
    GLubyte* playerSpritesExplosion[3];
    GLubyte* playerProjectileSprites[4];
    GLubyte* spyshipSprites[24];
    GLubyte* alphabetWhite[29];
    GLubyte* alphabetBlack[29];
    //GLubyte* alphabetBlackNoBorder[29];
    GLubyte* numbers[10];
    GLubyte* map;
    GLubyte* lives;
};
#endif //BOSCONIAN_VIEW_H
