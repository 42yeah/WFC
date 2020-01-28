//
//  WFC.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "WFC.hpp"


OutputTile::OutputTile(std::vector<std::pair<char, int> > candidates) : candidates(candidates), definiteValue(0) {
    
}

OutputTile &OutputTile::operator=(std::vector<std::pair<char, int> > candidates) {
    definiteValue = 0;
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

void WFC::printRaw(std::ostream &ostream) { 
    // We are not averaging it. We are just taking the most likely candidate from each.
    for (int y = 0; y < outputSize.y; y++) {
        for (int x = 0; x < outputSize.x; x++) {
            OutputTile &tile = output[y][x];
            if (tile.definiteValue != 0) {
                ostream << tile.definiteValue;
            } else if (tile.candidates.size() > 0) {
                std::pair<char, int> &current = tile.candidates[0];
                for (int i = 1; i < tile.candidates.size(); i++) {
                    if (tile.candidates[i].second > current.second) {
                        current = tile.candidates[i];
                    }
                }
                ostream << current.first;
            } else {
                // There is a contradiction here
                ostream << "X";
            }
        }
        ostream << std::endl;
    }
}
