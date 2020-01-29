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
    
    bool isDefinite();
    bool isContradictive();
    
    int getEntropy();

    std::vector<Pattern *> patterns;
};

#endif /* Cell_hpp */
