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
#include "Input.hpp"
#include "Vec2.hpp"


struct OutputTile {
    OutputTile() : definiteValue(0) {}
    OutputTile(std::vector<std::pair<char, int> > candidates);
    
    OutputTile &operator=(std::vector<std::pair<char, int> > candidates);

    char definiteValue;
    std::vector<std::pair<char, int> > candidates;
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
    Input *input;
    Vec2 outputSize;
    OutputTile **output;
};

#endif /* WFC_hpp */
