//
//  WFC.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/29.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef WFC_hpp
#define WFC_hpp

#include <random>
#include "Model.hpp"
#include "Cell.hpp"
#include "Vec2.hpp"


enum ObserveState {
    FINE, DONE, CONTRADICTION
};

class WFC {
public:
    WFC() {}
    WFC(Model *model);
    
    void generate(Vec2 size);
    ObserveState observe();
    void propagate();

private:
    std::vector<Vec2> findLowestEntropyCells();
    Cell *at(Vec2 pos);
    std::random_device dev;

    Model *model;
    Cell **wave;
    Vec2 waveSize;
    
    std::vector<Vec2> updates;
};

#endif /* WFC_hpp */
