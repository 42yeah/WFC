//
//  main.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include <iostream>
#include "Input.hpp"
#include "WFC.hpp"


int main(int argc, const char * argv[]) {
    Input input("Assets/default");
    input.processPatterns(Vec2(3, 3)); // N=3
    input.printRaw(std::cout);
    
    WFC output(&input);
    output.generate(Vec2(10, 10)); // 10x10 output
    output.printRaw(std::cout);
    return 0;
}
