//
//  WFC.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef WFC_hpp
#define WFC_hpp

#include <iostream>
#include <random>
#include "Input.hpp"
#include "Vec2.hpp"
#include "OutputTile.hpp"


enum WFCState {
    FINE, DONE, CONTRADICTION
};

/**
 The core algorithm. Here's where the fun lies.
 We are only implementing the overlapping model, though.
 */
class WFC {
public:
    WFC() {}
    WFC(Input *input);
    
    void generate(Vec2 size);
    
    void printRaw(std::ostream &ostream);
    
private:
    WFCState observe();
    void propagate();
    void ban();

    std::vector<Vec2> findLowestEntropyTiles();
    OutputTile *at(Vec2 pos);
    
    Input *input;
    Vec2 outputSize;
    OutputTile **output;
    
    std::uniform_int_distribution<> distrib;
    std::random_device dev;
};

#endif /* WFC_hpp */
