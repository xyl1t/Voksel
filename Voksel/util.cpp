//
//  util.cpp
//  Voksel
//
//  Created by Marat Isaw on 04.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "util.hpp"

float util_lerp(float a, float b, float t) {
    return a + (b - a) * t;
}
