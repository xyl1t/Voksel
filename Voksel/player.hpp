//
//  player.hpp
//  Voksel
//
//  Created by Marat Isaw on 01.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "tensorMath.hpp"
using namespace tem;

class Player {
public:
    Player(vec3 position = vec3(), vec3 velocity = vec3(), vec3 acceleration = vec3(),
           vec3 angularPosition = vec3(), vec3 angularVelocity = vec3(), vec3 angularAcceleration = vec3());
    
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    vec3 angularPosition;
    vec3 angularVelocity;
    vec3 angularAcceleration;

    void Update(float elapsedTime);
};

#endif /* PLAYER_HPP */
