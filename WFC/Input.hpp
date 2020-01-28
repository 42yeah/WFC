//
//  Input.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Pattern.hpp"
#include "Vec2.hpp"


/**
 The input model of the WFC. We will process patterns from here.
 After that the input would be fed into the output.
 */
class Input {
public:
    Input() {}
    Input(std::string path);
    
    void processPatterns(Vec2 size);
    
    char at(Vec2 pos);
    void printRaw(std::ostream &ostream);

private:
    void processFile(std::string path);

    int modelWidth, modelHeight;
    Vec2 patternSize;
    char **map;
    std::vector<Pattern> patterns;
};

#endif /* Input_hpp */
