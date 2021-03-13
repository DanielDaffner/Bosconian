//
// Created by basti on 03.01.2021.
//

#include "../../include/model/EnemyBasePart.h"

Position2D EnemyBasePart::drawOffset[] = {Position2D{112,-144},
                                          Position2D{16,-160},
                                          Position2D{16,-34},
                                          Position2D{112,0},
                                          Position2D{176,-34},
                                          Position2D{176,-160},

                                          Position2D{0,-112},
                                          Position2D{34,-16},
                                          Position2D{160,-16},
                                          Position2D{144,-112},
                                          Position2D{160,-176},
                                          Position2D{34,-176}
};
EnemyBasePart::EnemyBasePart(double x, double y, int direct) : GameObject() {
    dir = direct;
    pos.x = x;
    pos.y = y;
    score = 200;
}