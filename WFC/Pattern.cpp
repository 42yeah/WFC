//
//  Pattern.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "Pattern.hpp"
#include "Model.hpp"


Pattern::Pattern(Model *model, Vec2 size, Vec2 basePos, PatternTransformation transformation) : size(size), transformation(transformation), frequency(1) {
    rawPattern = new char*[size.y];
    for (int y = 0; y < size.y; y++) {
        rawPattern[y] = new char[size.x];
        for (int x = 0; x < size.x; x++) {
            Vec2 vec2(x, y);
            switch (transformation) {
                case ROT90:
                    vec2.rot90(size);
                    break;
                    
                case ROT180:
                    vec2.rot180(size);
                    break;
                    
                case ROT270:
                    vec2.rot270(size);
                    break;
                    
                case NOPE:
                default:
                    break;
            }
            rawPattern[y][x] = model->at(basePos + vec2);
        }
    }
}

void Pattern::printRaw(std::ostream &ostream) { 
    ostream << "Pattern size: " << size.x << "x" << size.y << std::endl;
    ostream << "Frequency: " << frequency << std::endl;
    ostream << "Transformation: ";
    switch (transformation) {
        case NOPE:
            ostream << "NOPE" << std::endl;
            break;
            
        case ROT90:
            ostream << "ROT90" << std::endl;
            break;
        
        case ROT180:
            ostream << "ROT180" << std::endl;
            break;
        
        case ROT270:
            ostream << "ROT270" << std::endl;
            break;
        
        default:
            ostream << "DUNNO" << std::endl;
            break;
    }
    ostream << "Pattern:" << std::endl;
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            ostream << at(Vec2(x, y));
        }
        ostream << std::endl;
    }
}

char Pattern::at(Vec2 pos) { 
    if (!pos.boundaryCheck(size)) {
        return 0;
    }
    return rawPattern[pos.y][pos.x];
}

bool Pattern::operator==(Pattern &another) { 
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            Vec2 pos(x, y);
            if (at(pos) != another.at(pos)) {
                return false;
            }
        }
    }
    return true;
}

Vec2 Pattern::getPatternSize() { 
    return size;
}

