//
//  Cell.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/29.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "Cell.hpp"
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
