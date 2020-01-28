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
    std::uniform_int_distribution<> distrib = std::uniform_int_distribution<>(0, (int) indices.size() - 1);
    Vec2 pos = indices[distrib(dev)];
    ban(pos);
    propagate(pos - input->patternSize + Vec2(1, 1), pos + Vec2(1, 1));
    return FINE;
}

/**
 Ban a tile to its definite state, regardless of everything else.
 */
void WFC::ban(Vec2 pos) {
    OutputTile *tile = at(pos);
    if (!tile) { return; } // What the hell?
    int entropy = tile->getEntropy();
    std::uniform_int_distribution<> distrib = std::uniform_int_distribution<>(0, entropy - 1);
    int selection = distrib(dev);
    for (int i = 0; i < tile->candidates.size(); i++) {
        selection -= tile->candidates[i].second;
        if (selection <= 0) {
            tile->definiteValue = tile->candidates[i].first;
            return;
        }
    }
    // Shouldn't be here
    return;
}

void WFC::propagate(Vec2 si, Vec2 ee) {
    // From the start inclusive area to the end exclusive area...
    for (int y = si.y; y < ee.y; y++) {
        for (int x = si.x; x < ee.x; x++) {
            // For every pattern tiles...
            for (int b = 0; b < input->patternSize.y; b++) {
                for (int a = 0; a < input->patternSize.x; a++) {
                    // We assume a finalized value for it.
                    
                }
            }
        }
    }
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
