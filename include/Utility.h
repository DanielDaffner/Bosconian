//
// Created by basti on 14.12.2020.
//

#ifndef BOSCONIAN_UTILITY_H
#define BOSCONIAN_UTILITY_H

struct Position2D{
    int x;
    int y;

    Position2D operator+(const Position2D& a) const
    {
        return Position2D{x+a.x, y+a.y};
    }
};

#endif //BOSCONIAN_UTILITY_H
