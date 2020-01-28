//
//  Input.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include "Input.hpp"
#include <fstream>
#include <iostream>


Input::Input(std::string path) {
    processFile(path);
}

void Input::processFile(std::string path) { 
    std::ifstream f(path);
    if (!f.good()) {
        return;
    }
    std::string line = "";
    std::getline(f, line, '\n'); // We get the first line first
    modelWidth = modelHeight = (int) line.length(); // And we assume the model w/h
    map = new char*[modelHeight];
    for (int i = 0; i < modelHeight; i++) {
        map[i] = new char[modelWidth];
        if (i != 0) {
            std::getline(f, line, '\n');
        }
        for (int j = 0; j < modelWidth; j++) {
            map[i][j] = line[j];
        }
    }
}

char Input::at(Vec2 pos) { 
    if (!pos.boundaryCheck(Vec2(modelWidth, modelHeight))) {
        return 0; // Nothing? Empty?
    }
    return map[pos.y][pos.x];
}

void Input::printRaw(std::ostream &ostream) {
    ostream << "#Patterns: " << patterns.size() << std::endl;
    for (int i = 0; i < patterns.size(); i++) {
        patterns[i].printRaw(ostream);
    }
    ostream << std::endl;
    ostream << "Frequencies:" << std::endl;
    for (int i = 0; i < frequencies.size(); i++) {
        ostream << frequencies[i].first << ": " << frequencies[i].second << std::endl;
    }
    ostream << "Raw:" << std::endl;
    for (int y = 0; y < modelHeight; y++) {
        for (int x = 0; x < modelWidth; x++) {
            ostream << at(Vec2(x, y));
        }
        ostream << std::endl;
    }
}

void Input::processPatterns(Vec2 size) {
    patternSize = size;
    patterns.clear();
    frequencies.clear();
    
    // Add patterns to list
    for (int y = 0; y < modelHeight - size.y + 1; y++) {
        for (int x = 0; x < modelWidth - size.x + 1; x++) {
            patterns.push_back(Pattern(this, patternSize, Vec2(x, y), NOPE));
            patterns.push_back(Pattern(this, patternSize, Vec2(x, y), ROT90));
            patterns.push_back(Pattern(this, patternSize, Vec2(x, y), ROT180));
            patterns.push_back(Pattern(this, patternSize, Vec2(x, y), ROT270));
        }
    }
    // Eliminate the same
    for (int i = 0; i < patterns.size(); i++) {
        for (int j = i + 1; j < patterns.size(); j++) {
            if (patterns[i] == patterns[j]) {
                patterns.erase(patterns.begin() + j, patterns.begin() + j + 1);
                patterns[i].frequency++;
                j--;
                continue;
            }
        }
    }
    // Compute frequencies
    for (int i = 0; i < patterns.size(); i++) {
        for (int y = 0; y < patternSize.y; y++) {
            for (int x = 0; x < patternSize.x; x++) {
                char val = patterns[i].at(Vec2(x, y));
                pushFrequency(val, patterns[i].frequency);
            }
        }
    }
}

void Input::pushFrequency(char val, int freq) {
    for (int i = 0; i < frequencies.size(); i++) {
        if (frequencies[i].first == val) {
            frequencies[i].second += freq;
            return;
        }
    }
    frequencies.push_back(std::pair<char, int>(val, freq));
}
