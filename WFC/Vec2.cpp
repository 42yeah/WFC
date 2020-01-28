//
//  Vec2.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "Vec2.hpp"


Vec2::Vec2(int x, int y) : x(x), y(y) {

}

Vec2 Vec2::operator+(Vec2 another) {
    return Vec2(x + another.x, y + another.y);
}

Vec2 &Vec2::operator+=(Vec2 another) {
    x += another.x;
    y += another.y;
    return *this;
}

Vec2 Vec2::operator-(Vec2 another) {
    return Vec2(x - another.x, y - another.y);
}

Vec2 &Vec2::operator-=(Vec2 another) {
    x -= another.x;
    y -= another.y;
    return *this;
}

/**
 Flip x/y coord, then mirror x.
 */
void Vec2::rot90(Vec2 size) {
    Vec2 nVec(y, x);
    nVec.x = size.x - nVec.x + 1;
    x = nVec.x;
    y = nVec.y;
}

/**
 Just mirror y.
 */
void Vec2::rot180(Vec2 size) {
    Vec2 nVec(size.y - y + 1, x);
    x = nVec.x;
    y = nVec.y;
}

/**
 Flip x/y coord, then mirror y.
 */
void Vec2::rot270(Vec2 size) {
    Vec2 nVec(y, x);
    nVec.y = size.y - nVec.y + 1;
    x = nVec.x;
    y = nVec.y;
}

bool Vec2::boundaryCheck(Vec2 size) {
    return !(x < 0 || y < 0 || x >= size.x || y >= size.y);
}
