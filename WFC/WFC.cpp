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

