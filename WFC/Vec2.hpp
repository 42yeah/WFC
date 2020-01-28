//
//  Vec2.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef Vec2_hpp
#define Vec2_hpp


class Vec2 {
public:
    void rot90(Vec2 size);
    void rot180(Vec2 size);
    void rot270(Vec2 size);

    Vec2 operator+(Vec2 another);
    Vec2 operator-(Vec2 another);
    Vec2 &operator+=(Vec2 another);
    Vec2 &operator-=(Vec2 another);
    
    bool operator==(Vec2 another);

    bool boundaryCheck(Vec2 size);

    Vec2() {}
    Vec2(int x, int y);
    
    int x, y;
};

#endif /* Vec2_hpp */
