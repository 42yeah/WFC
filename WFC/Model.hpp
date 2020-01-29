//
//  Model.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <iostream>
#include <string>
#include <vector>
#include "Pattern.hpp"
#include "Vec2.hpp"


/**
 The model model of the WFC. We will process patterns from here.
 After that the model would be fed into the output.
 */
class Model {
public:
    Model() {}
    Model(std::string path);
    
    void processPatterns(Vec2 size);
    
    char at(Vec2 pos);
    void printRaw(std::ostream &ostream);
    
    std::vector<std::pair<char, int> > frequencies;
    Vec2 patternSize;

private:
    void processFile(std::string path);
    void pushFrequency(char val, int freq);

    int modelWidth, modelHeight;
    char **map;
    std::vector<Pattern> patterns;
};

#endif /* Model_hpp */
