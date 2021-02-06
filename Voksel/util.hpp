//
//  util.hpp
//  Voksel
//
//  Created by Marat Isaw on 04.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include <cmath>

namespace util {
    inline float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }
    inline float fade(float x)
    {
        return x * x * x * (x * (x * 6 - 15) + 10);
    }
    inline float fadeEnd(float x)
    {
        float n = -(1-x)*(1-x)+1;
        return (1-x)*n+x*x;
    }
    inline float fadeControl(float x, float a, float b)
    {
        float powXA = pow(x, a);
        return powXA / (powXA + pow(b - b * x, a));
    }
    inline float fadeControlEndHeight(float x, float a, float b, float c)
    {
        float powXA = pow(x, a);
        return powXA / (powXA / c + pow(b - b * x, a));
    }
    inline float clamp(float x, float lowerlimit, float upperlimit)
    {
        if (x < lowerlimit)
            x = lowerlimit;
        if (x > upperlimit)
            x = upperlimit;
        return x;
    }
    inline float smoothstep(float edge0, float edge1, float x)
    {
        // Scale, and clamp x to 0..1 range
        x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
        // Evaluate polynomial
        return x * x * x * (x * (x * 6 - 15) + 10);
    }
    inline float radInDeg(float angle) {
        return angle * 180.f/3.1415926535897932384626433832795028841971693993751058209749445923078164062f;
    }
    inline float DegInRad(float angle) {
        return angle * 3.1415926535897932384626433832795028841971693993751058209749445923078164062f/180.f;
    }
}

#endif /* util_hpp */
