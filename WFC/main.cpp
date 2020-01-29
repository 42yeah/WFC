//
//  main.cpp
//  WFC
//
//  Created by 周昊 on 2020/1/28.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#include <iostream>
#include "Model.hpp"
#include "WFC.hpp"


int main(int argc, const char * argv[]) {
    Model model("Assets/default");
    model.processPatterns(Vec2(3, 3)); // N=3
    model.printRaw(std::cout);
    WFC wfc(&model);
    wfc.generate(Vec2(10, 10));
    return 0;
}
