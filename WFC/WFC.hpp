//
//  WFC.hpp
//  WFC
//
//  Created by 周昊 on 2020/1/29.
//  Copyright © 2020 aiofwa. All rights reserved.
//

#ifndef WFC_hpp
#define WFC_hpp

#include "Model.hpp"
#include "Cell.hpp"
#include "Vec2.hpp"


class WFC {
public:
    WFC() {}
    WFC(Model *model);
    
    void generate(Vec2 size);

private:
    Model *model;
    Cell **wave;
};

#endif /* WFC_hpp */
