//
//  util.hpp
//  Voksel
//
//  Created by Marat Isaw on 04.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

namespace util {
    inline float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }
    inline float radInDeg(float angle) {
        return angle * 180.f/3.1415926535897932384626433832795028841971693993751058209749445923078164062f;
    }
    inline float DegInRad(float angle) {
        return angle * 3.1415926535897932384626433832795028841971693993751058209749445923078164062f/180.f;
    }
}

#endif /* util_hpp */
