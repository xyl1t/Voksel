//
//  sprite.hpp
//  Voksel
//
//  Created by Marat Isaw on 04.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef sprite_hpp
#define sprite_hpp

#include "color.hpp"

class Sprite {
public:
    RGBA GetPixel(int x, int y);
    void SetPixel(RGBA color, int x, int y);
    
private:
    uint32_t* data;
};

#endif /* sprite_hpp */
