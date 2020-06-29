//
//  game.cpp
//  Voksel
//
//  Created by Marat Isaw on 18.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "game.hpp"
#include <iostream>
#include <stb/stb_image.h>
#include <cmath>
#include <cstdint>
#include "tensorMath.hpp"
#include <algorithm>
using namespace tem;

static float util_lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

Game::Game(Display& display, vec3 spawnPoint, int distance) : display(display), playerPosition(spawnPoint), playerAngle(45.f * M_PI/180), distance(distance), minimapWidth(128), minimapHeight(128) {
    int nrChannels;
    uint8_t* rawColormap = stbi_load("/Users/maratisaw/Home/Documents/Programming/C++/Projects/SDL/Voksel/Voksel/res/C1W.png", &mapWidth, &mapHeight, &nrChannels, 0);
    uint8_t* rawHeightmap = stbi_load("/Users/maratisaw/Home/Documents/Programming/C++/Projects/SDL/Voksel/Voksel/res/D1.png", &mapWidth, &mapHeight, &nrChannels, 0);
    
    
    this->pixelWidth = mapWidth / minimapWidth;
    this->pixelHeight = mapHeight / minimapHeight;
    
    std::cout << nrChannels << std::endl;
    
    colormap = new RGB[mapWidth * mapHeight];
    heightmap = new uint8_t[mapWidth * mapHeight];
    
    for(int i = 0; i < mapWidth * mapHeight; i++) {
        colormap[i] = { rawColormap[i * 3 + 0], rawColormap[i * 3 + 1], rawColormap[i * 3 + 2] };
    }
    for(int i = 0; i < mapWidth * mapHeight; i++) {
        heightmap[i] = { rawHeightmap[i] };
    }
    
    stbi_image_free(rawColormap);
    stbi_image_free(rawHeightmap);
}

Game::~Game() {
    delete[] colormap;
    delete[] heightmap;
}

/*
 * +- -+   +-        -+   +-                  -+
 * | x | * | cos -sin | = | x * cos + y * -sin |
 * | y |   | sin  cos |   | x * sin + y *  cos |
 * +- -+   +-        -+   +-                  -+
 */


void Game::Update() {
    
    float cosAngle = cos(playerAngle);
    float sinAngle = sin(playerAngle);
    
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_UP)) {
        playerPosition.x += sinAngle;
        playerPosition.y += -cosAngle;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_DOWN)) {
        playerPosition.x -= sinAngle;
        playerPosition.y -= -cosAngle;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_LEFT)) {
        playerAngle -= M_PI / 135.f;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_RIGHT)) {
        playerAngle += M_PI / 135.f;
    }

    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_1)) {
        minimapWidth -= 1;
        pixelWidth = mapWidth / (float)minimapWidth;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_2)) {
        minimapWidth += 1;
        pixelWidth = mapWidth / (float)minimapWidth;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_3)) {
        minimapHeight -= 1;
        pixelHeight = mapHeight / (float)minimapHeight;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_4)) {
        minimapHeight += 1;
        pixelHeight = mapHeight / (float)minimapHeight;
    }


    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_0)) {
        distance += 1;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_9)) {
        distance -= 1;
    }

    display.Clear();
    
    
    for (int i = distance; i >= 0; i--) {
//        vec2 leftPoint = { playerPosition.x - i, playerPosition.y - i};
//        vec2 rightPoint = { playerPosition.x + i, playerPosition.y - i};

        vec2 newLeftPoint = {
            -i * cosAngle + -i * (-sinAngle),
            -i * sinAngle + -i * cosAngle
        };
        vec2 newRightPoint = {
            +i * cosAngle + -i * (-sinAngle),
            +i * sinAngle + -i * cosAngle
        };
        
        float dx = (newRightPoint.x - newLeftPoint.x) / display.GetWidth();
        float dy = (newRightPoint.y - newLeftPoint.y) / display.GetWidth();
        
        
        
        if(dx == 0 && dy == 0) continue;
        
        
        RGBA fovColor = {0x8a, 0x8a, 0x8a, 0xff};
//        if(i % 2)
        for(int j = 0; j < display.GetWidth(); j++) {
            display.SetPixel(newLeftPoint.x + playerPosition.x, newLeftPoint.y + playerPosition.y, colormap[(int)(newLeftPoint.x + playerPosition.x)+ (int)(newLeftPoint.y + playerPosition.y) * mapWidth]);
            newLeftPoint.x+=dx;
            newLeftPoint.y+=dy;
//            c = (i / 100.f) * 255;
        }
        
//        display.SetPixel(newLeftPoint.x + playerPosition.x, newLeftPoint.y + playerPosition.y, fovColor);
//        display.SetPixel(newRightPoint.x + playerPosition.x, newRightPoint.y + playerPosition.y, fovColor);
    }
        
    display.Update();
}

void Game::drawLineDown(int x, int y, RGBA color) {
    for(int i = 0; i < display.GetHeight() - y; i++) {
        display.SetPixel(x, y + i, color);
    }
}

/*
// for (int i = 0; i < minimapWidth; i++) {
//         for(int j = 0; j < minimapHeight; j++) {
//
//
//             int r = 0, g = 0, b = 0;
//             for (int k = 0; k < pixelWidth; k++) {
//                 for (int l = 0; l < pixelHeight; l++) {
//
//                     int index = (int)(i * pixelWidth + k) + (int)(j * pixelHeight + l) * mapWidth;
//                     r += colormap[index].r;
//                     g += colormap[index].g;
//                     b += colormap[index].b;
//                 }
//             }
//
//             r /= ceil(pixelWidth) * ceil(pixelHeight);
//             g /= ceil(pixelWidth) * ceil(pixelHeight);
//             b /= ceil(pixelWidth) * ceil(pixelHeight);
//
//             if(i == 0 && j == 0) {
//             }
//
//             float iscreen = i - minimapWidth / 2;
//             float jscreen = j - minimapHeight / 2;
//
//
//             iscreen = (1 * iscreen) + (-tan(playerAngle / 2) * jscreen);
//             jscreen = (0 * iscreen) + (                    1 * jscreen);
//
//             iscreen = (               1 * iscreen) + (0 * jscreen);
//             jscreen = (sin(playerAngle) * iscreen) + (1 * jscreen);
//
//             iscreen = (1 * iscreen) + (-tan(playerAngle / 2) * jscreen);
//             jscreen = (0 * iscreen) + (                    1 * jscreen);
//
//
//             mat2x2 mat1 = mat2x2(1);
//             mat1[1] = -tan(playerAngle/2);
//             mat2x2 mat2 = mat2x2(1);
//             mat2[2] = sin(playerAngle);
//             vec2 vec {iscreen, jscreen};
//
//             vec2 nVec = mat1 * mat2 * mat1 * vec;
//
//             display.SetPixel(roundf(nVec.x) + 128, roundf(nVec.y) + 128,
//             { (uint8_t)(r),
//               (uint8_t)(g),
//               (uint8_t)(b), 0xff });
//         }
//     }
     
     mat3x3 matFinal(1.f), matA(1.f), matB(1.f), matC(1.f), matFinalInv(1.f);
     
     matA.translate(-(mapWidth * 0.2)/2.f, -(mapHeight * 0.2)/2.f);
     matB.scale(0.2, 0.2);
     matC.rotate(playerAngle);
     
     matFinal = matC * matA * matB;
     matA.translate(+(mapWidth * 0.2)/2.f, +(mapHeight * 0.2)/2.f);
     matFinal = matA * matFinal;
     
     matFinalInv = matFinal.inverse();
     
     vec3 p;
     float sx, sy;
     float ex, ey;
     
     p = matFinal * (vec3){0, 0, 1};
     sx = p.x;
     sy = p.y;
     ex = p.x;
     ey = p.y;
     p = matFinal * (vec3){(float)mapWidth, (float)mapHeight, 1};
     sx = std::min(sx, p.x);
     sy = std::min(sy, p.y);
     ex = std::max(ex, p.x);
     ey = std::max(ey, p.y);
     p = matFinal * (vec3){(float)0, (float)mapHeight, 1};
     sx = std::min(sx, p.x);
     sy = std::min(sy, p.y);
     ex = std::max(ex, p.x);
     ey = std::max(ey, p.y);
     p = matFinal * (vec3){(float)mapWidth, (float)0, 1};
     sx = std::min(sx, p.x);
     sy = std::min(sy, p.y);
     ex = std::max(ex, p.x);
     ey = std::max(ey, p.y);

     int playerX = playerPosition.x;
     int playerY = playerPosition.y;

     while (playerX < 0)
         playerX += mapWidth-1;
     while (playerY < 0)
         playerY += mapHeight-1;
     while (playerX >= mapWidth-1)
         playerX -= mapWidth-1;
     while (playerY >= mapHeight-1)
         playerX -= mapHeight-1;

     for(int x = 0; x < mapWidth * 0.2; x++) {
         for(int y = 0; y < mapHeight * 0.2; y++) {
             p = matFinalInv * (vec3){(float)x, (float)y, 1};
             
             if(x < 0 || y < 0 || x > display.GetWidth() || y > display.GetHeight()) {
 //                display.SetPixel(x, y, (RGB){255, 255, 255});
                 continue;
             }
             if(p.x < 0)
                 p.x = p.x + mapWidth;
             if(p.y < 0)
                 p.y = p.y + mapHeight;
             if(p.x > mapWidth)
                 p.x = p.x - mapWidth;
             if(p.y > mapHeight)
                 p.y = p.y - mapHeight;

             
             int mx = ((int)p.x + playerX) % mapWidth;
             int my = ((int)p.y + playerY) % mapHeight;
             int index = mx + my * mapWidth;
             RGB pixel = colormap[index];
             display.SetPixel(x, y, pixel);
         }
     }
*/
