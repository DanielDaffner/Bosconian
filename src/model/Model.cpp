//
// Created by basti on 14.12.2020.
//

#include "../../include/model/Model.h"
#include "../../include/Utility.h"

Model::Model() {
    player = new Player();
    for(int x = 0; x < 4; x++) {
        for(int y = 0; y < 300; y++) {
            pixelarr[x].push_back(new BackgroundPixel);
        }
    }
}

GLubyte* Model::alphabetWhite[29];
GLubyte* Model::alphabetBlack[29];
GLubyte* Model::numbers[10];
GLubyte* Model::map;
GLubyte* Model::lifes;