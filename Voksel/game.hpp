//
//  game.hpp
//  Voksel
//
//  Created by Marat Isaw on 18.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "color.hpp"
#include "display.hpp"
#include "tensorMath.hpp"
#include <cmath>
using namespace tem;

class Game {
public:
    
    Game(Display& display, vec3 spawnPoint, int distance);
    
    void Update();
    
    ~Game();
    
private:
    
    void drawLineDown(int x, int y, float z, RGB color);
    vec3 playerPosition;
    float playerAngleYaw;
    float playerAnglePitch;
    float playerAngleRoll;
    int distance;
    Display& display;
    RGB* colormap;
    uint8_t* heightmap;
    int mapWidth;
    int mapHeight;
    
    float tiltFront = 0;
    float tiltSide = 0;
    
    float* zBuffer;
    int minimapWidth;    //= 128;
    int minimapHeight;   //= 128;
    float pixelWidth;      //= mapWidth / minimapWidth;
    float pixelHeight;     //= mapHeight / minimapHeight;
    
    static constexpr float EulerConstant = 2.71828182845904523536028747135266249775724709369995f;
};

#endif /* GAME_HPP */
