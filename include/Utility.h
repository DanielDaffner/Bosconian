//
// Created by basti on 14.12.2020.
//

#ifndef BOSCONIAN_UTILITY_H
#define BOSCONIAN_UTILITY_H

#define VIEW_WIDTH 1280
#define VIEW_HEIGHT 960
#define PADDING 4

#define GAME_WIDTH (VIEW_WIDTH-PADDING-256)
#define GAME_HEIGHT 960

#define MAP_WIDTH 2560
#define MAP_HEIGHT 5120

#define ROUND_POS_X (VIEW_WIDTH-PADDING-256)
#define ROUND_POS_Y (VIEW_HEIGHT-5)

#define LIFES_POS_X (VIEW_WIDTH-PADDING-256)
#define LIFES_POS_Y (VIEW_HEIGHT-74)

#define MAP_POS_X (VIEW_WIDTH-PADDING-256)
#define MAP_POS_Y (VIEW_HEIGHT-142)


struct Position2D{
    double x;
    double y;

    Position2D operator+(const Position2D& a) const
    {
        return Position2D{x+a.x, y+a.y};
    }
//    Position2D operator/(double a) const
//    {
//        return Position2D{x/a, y/a};
//    }
};

#endif //BOSCONIAN_UTILITY_H
