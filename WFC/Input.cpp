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
