//
//  Cell.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/29.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "Cell.hpp"
#include "WFC.hpp"
#include <random>


Cell &Cell::operator=(std::vector<Pattern *> patterns) { 
    this->patterns = patterns;
    return *this;
}

void Cell::collapse(Pattern *pattern) { 
    for (int i = 0; i < patterns.size(); i++) {
        if (patterns[i] == pattern) {
            patterns.erase(patterns.begin(), patterns.begin() + 1);
            return;
        }
    }
}

void Cell::finalize() {
    std::uniform_int_distribution<> distrib(0, getEntropy());
    std::random_device dev;
    int selection = distrib(dev);
    int index = 0;
    while (true) {
        selection -= patterns[index]->frequency;
        if (selection <= 0) { break; }
        index++;
    }
    // Erase all except this one
    patterns.erase(patterns.begin(), patterns.begin() + index);
    patterns.erase(patterns.begin() + 1, patterns.end());
}

int Cell::getEntropy() {
    int e = 0;
    for (int i = 0; i < patterns.size(); i++) {
        e += patterns[i]->frequency;
    }
    return e;
}

bool Cell::isContradictive() { 
    return patterns.size() == 0;
}


bool Cell::isDefinite() { 
    return patterns.size() == 1;
}

bool Cell::update(WFC *wfc, Vec2 basePos) {
    // Iterate through all available patterns, check whether one has violated the overlap rule
    bool dirty = false;
    for (int i = 0; i < patterns.size(); i++) {
        bool legit = true;
        // Only if ALL overlap rules are satisfied, could this thing be legit.
        for (int j = 0; j < patterns[i]->overlaps.size() && legit; j++) {
            Overlaps &rules = patterns[i]->overlaps[j];
            Vec2 offset = rules.offset;
            Cell *cell = wfc->at(basePos + offset);
            if (!cell) { continue; }
            bool sated = false;
            // If ANY of the neighboring rules apply, then this passes.
            for (int k = 0; k < rules.patterns.size(); k++) {
                if (cell->has(rules.patterns[k])) {
                    sated = true;
                    break;
                }
            }
            if (!sated) {
                legit = false;
                break;
            }
        }
        if (!legit) {
            dirty = true;
            patterns.erase(patterns.begin() + i, patterns.begin() + i + 1);
            i--;
            continue;
        }
    }
    return dirty;
}

bool Cell::has(Pattern *pattern) { 
    for (int i = 0; i < patterns.size(); i++) {
        if (pattern == patterns[i]) { return true; }
    }
    return false;
}

char Cell::toChar(Vec2 pos, Vec2 patternSize, Vec2 mapSize) {
    if (patterns.size() == 0) {
        return 'X';
    } else if (patterns.size() == 1) {
        return patterns[0]->at(Vec2(0, 0));
    } else {
        return '?';
    }
}
