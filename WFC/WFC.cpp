//
//  WFC.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/29.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "WFC.hpp"


WFC::WFC(Model *model) : model(model), wave(nullptr) {

}

void WFC::generate(Vec2 size) {
    waveSize = size;
    wave = new Cell*[size.y];
    std::vector<Pattern *> patterns; // Use pointer to avoid boom in size
    for (int i = 0; i < model->patterns.size(); i++) {
        patterns.push_back(&model->patterns[i]);
    }
    for (int y = 0; y < size.y; y++) {
        wave[y] = new Cell[size.x];
        for (int x = 0; x < size.x; x++) {
            wave[y][x] = patterns;
        }
    }
    wave[0][0].finalize();
}

std::vector<Vec2> WFC::findLowestEntropyCells() {
    int lo = -1;
    std::vector<Vec2> positions;
    
    for (int y = 0; y < waveSize.y; y++) {
        for (int x = 0; x < waveSize.x; x++) {
            Cell &cell = wave[y][x];
            Vec2 pos(x, y);
            if (cell.isDefinite()) { continue; }
            if (lo == -1 || lo > cell.getEntropy()) {
                positions.clear();
                lo = cell.getEntropy();
            }
            if (lo == cell.getEntropy()) {
                positions.push_back(pos);
            }
        }
    }
    return positions;
}

ObserveState WFC::observe() { 
    std::vector<Vec2> optimals = findLowestEntropyCells();
    if (optimals.size() <= 0) { return DONE; }
    if (at(optimals[0])->isContradictive()) { return CONTRADICTION; }
    std::uniform_int_distribution<> distrib(0, (int) optimals.size() - 1);
    int index = distrib(dev);
    at(optimals[index])->finalize();
    return FINE;
}

Cell *WFC::at(Vec2 pos) {
    if (!pos.boundaryCheck(waveSize)) { return nullptr; }
    return &wave[pos.y][pos.x];
}
