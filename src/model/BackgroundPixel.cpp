//
// Created by basti on 15.12.2020.
//
#include "../../include/model/BackgroundPixel.h"
#include <stdlib.h>

unsigned int BackgroundPixel::colors[8][4] = {
        {0xff0000ff,0xff0000ff,0xff0000ff,0xff0000ff},
        {0x509351ff,0x509351ff,0x509351ff,0x509351ff},
        {0x2d92c1ff,0x2d92c1ff,0x2d92c1ff,0x2d92c1ff},
        {0x08326eff,0x08326eff,0x08326eff,0x08326eff},
        {0xcaede6ff,0xcaede6ff,0xcaede6ff,0xcaede6ff},
        {0x000063ff,0x000063ff,0x000063ff,0x000063ff},
        {0x5a0002ff,0x5a0002ff,0x5a0002ff,0x5a0002ff}
};
BackgroundPixel::BackgroundPixel() : GameObject() {
//    color = rand() % 8;
    color = 0;
    pos.x = rand() % 1280;
    pos.y = rand() % 760;
}