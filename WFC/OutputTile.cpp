//
//  OutputTile.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "OutputTile.hpp"


OutputTile::OutputTile(std::vector<std::pair<char, int> > candidates) : candidates(candidates), definiteValue(0) {
    
}

OutputTile &OutputTile::operator=(std::vector<std::pair<char, int> > candidates) {
    definiteValue = 0;
    this->candidates = candidates;
    return *this;
}

int OutputTile::getEntropy() { 
    int e = 0;
    for (int i = 0; i < candidates.size(); i++) {
        e += candidates[i].second;
    }
    return e;
}
