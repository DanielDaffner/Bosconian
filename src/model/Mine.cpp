//
// Created by basti on 13.12.2020.
//
#include "../../include/model/Mine.h"

Mine::Mine(int x, int y) : GameObject() {
    pos.x = x;
    pos.y = y;
    score = 20;
    colliderSize = 32;
}