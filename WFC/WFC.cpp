//
//  WFC.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "WFC.hpp"


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
    
    observe();
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

WFCState WFC::observe() {
    std::vector<Vec2> indices = findLowestEntropyTiles();
    if (indices.size() <= 0) {
        return DONE;
    } else if (at(indices[0])->getEntropy() <= 0) {
        return CONTRADICTION;
    }
    
    // Just grab one
    
    
    return FINE;
}

void WFC::ban() { 
    
}

void WFC::propagate() {
    
}

std::vector<Vec2> WFC::findLowestEntropyTiles() {
    std::vector<Vec2> indices;
    int lo = -1; // An impossible entropy for easy initialization
    for (int y = 0; y < outputSize.y; y++) {
        for (int x = 0; x < outputSize.x; x++) {
            OutputTile &tile = output[y][x];
            if (tile.definiteValue != 0) { continue; } // We don't care about definite tiles
            int e = output[y][x].getEntropy();
            if (lo == -1 || e < lo) {
                indices.clear();
                lo = e;
            }
            if (e <= lo) {
                indices.push_back(Vec2(x, y));
            }
        }
    }
    return indices;
}

OutputTile *WFC::at(Vec2 pos) {
    if (!pos.boundaryCheck(outputSize)) {
        return nullptr;
    }
    return &output[pos.y][pos.x];
}
