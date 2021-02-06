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
    Player(vec3 position = vec3(), vec3 velocity = vec3(), vec3 acceleration = vec3(), vec3 jerk = vec3(),
           vec3 angularPosition = vec3(), vec3 angularVelocity = vec3(), vec3 angularAcceleration = vec3(), vec3 angularJerk = vec3());
    
    // Linear movement variables
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    vec3 jerk;

    // Rotational movement variables
    vec3 angularPosition;
    vec3 angularVelocity;
    vec3 angularAcceleration;
    vec3 angularJerk;
    float staticPitch{};

    void Update(float elapsedTime);
    
    // testing...
    static constexpr float mass = 2000;
    static constexpr float A = 10;
    vec3 jetForce;
    vec3 jetForceRotation {};
    
private:
    
    const float jetForceStep = 100;
    const float airFriction = 10;
};

#endif /* PLAYER_HPP */
