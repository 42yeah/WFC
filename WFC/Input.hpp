//
//  Input.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <string>
#include "Vec2.hpp"


/**
 The input model of the WFC. We will process patterns from here.
 After that the input would be fed into the output.
 */
class Input {
public:
    Input() {}
    Input(std::string path);
    
    char at(Vec2 pos);

private:
    void processFile(std::string path);

    int modelWidth, modelHeight;
    char **map;
};

#endif /* Input_hpp */
