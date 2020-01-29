//
//  Cell.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/29.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include "Pattern.hpp"


class WFC;

/**
 The output cell.
 */
struct Cell {
    Cell() {}
    Cell(std::vector<Pattern *> patterns) : patterns(patterns) {}
    
    Cell &operator=(std::vector<Pattern *> patterns);
    void collapse(Pattern *pattern);
    
    /**
     finalize chooses one out based on pattern weights, and collapse the others.
     */
    void finalize();
    
    /**
     Update this cell, removing all patterns that are not legit.
     */
    bool update(WFC *wfc, Vec2 basePos);
    
    bool isDefinite();
    bool isContradictive();
    
    bool has(Pattern *pattern);
    
    int getEntropy();
    
    char toChar(Vec2 pos, Vec2 patternSize, Vec2 mapSize);

    std::vector<Pattern *> patterns;
};

#endif /* Cell_hpp */
