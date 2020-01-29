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
    
    while (true) {
        latestResult = observe();
        if (latestResult == DONE || latestResult == CONTRADICTION) { break; }
        propagate();
    }
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

Cell *WFC::at(Vec2 pos) {
    if (!pos.boundaryCheck(waveSize)) { return nullptr; }
    return &wave[pos.y][pos.x];
}

ObserveResult WFC::observe() { 
    std::vector<Vec2> optimals = findLowestEntropyCells();
    if (optimals.size() <= 0) { return DONE; }
    if (at(optimals[0])->isContradictive()) { return CONTRADICTION; }
    std::uniform_int_distribution<> distrib(0, (int) optimals.size() - 1);
    int index = distrib(dev);
    Vec2 finalizedPos = optimals[index];
    at(finalizedPos)->finalize();
    
    // flag updates
    for (int y = -model->patternSize.y + 1; y < model->patternSize.y; y++) {
        for (int x = -model->patternSize.x + 1; x < model->patternSize.x; x++) {
            Vec2 pos(finalizedPos.x + x, finalizedPos.y + y);
            Cell *cell = at(pos);
            if (!cell || cell->isDefinite()) { continue; }
            updates.push_back(pos);
        }
    }
    return FINE;
}

void WFC::propagate() {
    int count = 0;
    while (updates.size() > 0) {
        std::cout << "Propagation " << count++ << " is done" << std::endl;
//        for (int y = 0; y < waveSize.y; y++) {
//            for (int x = 0; x < waveSize.x; x++) {
//                std::cout << at(Vec2(x, y))->toChar(Vec2(x, y), model->patternSize, waveSize);
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
        Vec2 pos = updates[0]; // Get the first
        updates.erase(updates.begin()); // And remove it (queue)
        Cell *cell = at(pos);
        if(cell->update(this, pos)) {
            for (int y = -model->patternSize.y + 1; y < model->patternSize.y; y++) {
                for (int x = -model->patternSize.x + 1; x < model->patternSize.x; x++) {
                    Vec2 p(pos.x + x, pos.y + y);
                    Cell *cell = at(p);
                    if (!cell || cell->isDefinite()) { continue; }
                    updates.push_back(p);
                }
            }
        }
    }
    std::cout << "Propagation is done" << std::endl;
}

void WFC::printRaw(std::ostream &ostream) { 
    ostream << "Latest result: ";
    switch (latestResult) {
        case FINE:
            ostream << "FINE";
            break;
            
        case DONE:
            ostream << "DONE";
            break;
            
        case CONTRADICTION:
            ostream << "CONTRADICTION";
            break;
    }
    ostream << std::endl;
    
    for (int y = 0; y < waveSize.y; y++) {
        for (int x = 0; x < waveSize.x; x++) {
            ostream << at(Vec2(x, y))->toChar(Vec2(x, y), model->patternSize, waveSize);
        }
        ostream << std::endl;
    }
    ostream << std::endl;
}
