//
//  player.cpp
//  Voksel
//
//  Created by Marat Isaw on 01.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "player.hpp"

Player::Player(vec3 position, vec3 velocity, vec3 acceleration,
vec3 angularPosition, vec3 angularVelocity, vec3 angularAcceleration) : position { position }, velocity { velocity }, acceleration { acceleration }, angularPosition { angularPosition }, angularVelocity { angularVelocity }, angularAcceleration { angularAcceleration }  {
    
}

void Player::Update(float elapsedTime) {
    velocity += acceleration * elapsedTime;
    position += velocity * elapsedTime;
    angularVelocity += angularAcceleration * elapsedTime;
    angularPosition += angularVelocity * elapsedTime;
}
