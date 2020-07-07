//
//  color.hpp
//  Voksel
//
//  Created by Marat Isaw on 18.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    inline uint32_t GetUint32() {
        return (r << 24) + (g << 16) + (b << 8) + 255;
    }
    inline uint32_t GetUint32WithoutAlpha() {
        return (r << 16) + (g << 8) + b;
    }

};

struct RGBA: public RGB {
    uint8_t a;
    
    inline uint32_t GetUint32() {
        return (r << 24) + (g << 16) + (b << 8) + a;
    }
};


#endif /* COLOR_HPP */
