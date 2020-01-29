//
//  WFC.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/29.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef WFC_hpp
#define WFC_hpp

#include <iostream>
#include <random>
#include "Model.hpp"
#include "Cell.hpp"
#include "Vec2.hpp"


enum ObserveResult {
    FINE, DONE, CONTRADICTION
};

class WFC {
public:
    WFC() {}
    WFC(Model *model);
    
    void generate(Vec2 size);
    ObserveResult observe();
    void propagate();
    
    Cell *at(Vec2 pos);
    
    void printRaw(std::ostream &ostream);

private:
    std::vector<Vec2> findLowestEntropyCells();
    std::random_device dev;

    Model *model;
    Cell **wave;
    Vec2 waveSize;
    
    std::vector<Vec2> updates;
    
    ObserveResult latestResult;
};

#endif /* WFC_hpp */
