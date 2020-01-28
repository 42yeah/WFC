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

OutputTile &OutputTile::operator=(std::vector<std::pair<char, int> > candidates) { 
    this->candidates = candidates;
    return *this;
}


// === WFC === //
WFC::WFC(Input *input) : input(input), outputSize(0, 0) {
    
}

void WFC::generate(Vec2 size) {
    outputSize = size;
    output = new OutputTile*[size.y];
    for (int y = 0; y < size.y; y++) {
        output[y] = new OutputTile[size.x];
        for (int x = 0; x < size.x; x++) {
            output[y][x] = input->frequencies;
        }
    }
}
