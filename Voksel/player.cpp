//
//  player.cpp
//  Voksel
//
//  Created by Marat Isaw on 01.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "player.hpp"
#include <iostream>
#include <cmath>
#include "util.hpp"

Player::Player(vec3 position, vec3 velocity, vec3 acceleration, vec3 jerk,
               vec3 angularPosition, vec3 angularVelocity, vec3 angularAcceleration, vec3 angularJerk)
: position { position }, velocity { velocity }, acceleration { acceleration }, jerk(jerk), angularPosition { angularPosition }, angularVelocity { angularVelocity }, angularAcceleration { angularAcceleration }, angularJerk(jerk) {
    
}

void Player::Update(float elapsedTime) {
    float sinAngleYaw = sin(angularPosition.y);
    float cosAngleYaw = cos(angularPosition.y);
    
    vec3 jetAcc = { jetForce.x / mass, jetForce.y / mass, acceleration.z };
    
    float dragForce = -1000 * velocity.y;
    
    vec3 dragAcc = { dragForce / mass, dragForce / mass, velocity.z * -4.f };
    
    jetAcc += dragAcc;
    acceleration = jetAcc;
    velocity.x += acceleration.x * elapsedTime;
    velocity.y += acceleration.y * elapsedTime;
    velocity.z += acceleration.z * elapsedTime;
    if(abs(velocity.y) < 1 && jetForce.length() == 0) {
        velocity.x = 0;
        velocity.y = 0;
    }
    
    position.x += velocity.x * sinAngleYaw * elapsedTime;
    position.y += velocity.y * -cosAngleYaw * elapsedTime;
    position.z += velocity.z * elapsedTime;
    
    /* Rotational motion */
    float dragForceRotation = -2.f * angularVelocity.y;
    vec3 dragAccRotation = { 0, dragForceRotation, 0 };
    angularAcceleration += dragAccRotation;
    angularVelocity += angularAcceleration * elapsedTime;

    if(abs(angularVelocity.y) < 0.005) {
        angularVelocity.y = 0;
    }
    
    angularPosition += angularVelocity * elapsedTime;
    
    angularPosition.z = -angularVelocity.y * 60;
    angularPosition.x = -velocity.y;
    angularPosition.x += staticPitch;
    
}
