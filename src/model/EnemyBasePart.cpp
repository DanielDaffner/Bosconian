//
// Created by basti on 03.01.2021.
//

#include "../../include/model/EnemyBasePart.h"

int EnemyBasePart::score = 200;
Position2D EnemyBasePart::drawOffset[] = {Position2D{112,-144},
                                          Position2D{16,-162},
                                          Position2D{16,-34},
                                          Position2D{112,0},
                                          Position2D{176,-34},
                                          Position2D{176,-162}
};
EnemyBasePart::EnemyBasePart(double x, double y, int direct) : GameObject() {
    dir = direct;
    pos.x = x;
    pos.y = y;
}