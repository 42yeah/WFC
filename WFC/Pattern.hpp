//
//  Pattern.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef Pattern_hpp
#define Pattern_hpp

#include "Vec2.hpp"
#include <iostream>


class Model;

enum PatternTransformation {
    NOPE, ROT90, ROT180, ROT270
};

class Pattern {
public:
    Pattern() {}
    Pattern(Model *model, Vec2 size, Vec2 basePos, PatternTransformation transformation);

    void printRaw(std::ostream &ostream);
    char at(Vec2 pos);
    Vec2 getPatternSize();

    bool operator==(Pattern &another);

    int frequency;

private:
    PatternTransformation transformation;
    Vec2 size;
    char **rawPattern;
};

#endif /* Pattern_hpp */
