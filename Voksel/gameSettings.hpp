//
//  gameSettings.hpp
//  Voksel
//
//  Created by Marat Isaw on 05.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef gameSettings_hpp
#define gameSettings_hpp
#include "tensorMath.hpp"
#include <string>
using namespace tem;

namespace Settings {
    inline int renderDistance = 1000;
    inline vec3 spawnPoint = { 433, 168, 64 };
    inline float horizon = { 300 };
    const std::string resPath = {"./res/"};
};

#endif /* gameSettings_hpp */
