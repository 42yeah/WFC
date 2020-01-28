//
//  WFC.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "WFC.hpp"


OutputTile::OutputTile(std::vector<std::pair<char, int> > candidates) : candidates(candidates) {
    
}

// === WFC === //
WFC::WFC(Input *input) : input(input), outputSize(0, 0) {
    
}

void WFC::generate(Vec2 size) {
    outputSize = size;
    
}

