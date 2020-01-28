//
//  OutputTile.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef OutputTile_hpp
#define OutputTile_hpp

#include <vector>


struct OutputTile {
    OutputTile() : definiteValue(0) {}
    OutputTile(std::vector<std::pair<char, int> > candidates);
    
    OutputTile &operator=(std::vector<std::pair<char, int> > candidates);

    int getEntropy();
    
    char definiteValue;
    std::vector<std::pair<char, int> > candidates;
};

#endif /* OutputTile_hpp */
