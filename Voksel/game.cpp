//
//  game.cpp
//  Voksel
//
//  Created by Marat Isaw on 18.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "game.hpp"
#include <SDL2/SDL.h>
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

Game::Game(Display& display, vec3 spawnPoint, int distance) : display(display), playerPosition(spawnPoint), playerAngleYaw(135.f * M_PI/180), playerAnglePitch(100), distance(distance), minimapWidth(128), minimapHeight(128) {
    int nrChannels;
    uint8_t* rawColormap = stbi_load("/Users/maratisaw/Home/Documents/Programming/C++/Projects/SDL/Voksel/Voksel/res/C1W.png", &mapWidth, &mapHeight, &nrChannels, 0);
    uint8_t* rawHeightmap = stbi_load("/Users/maratisaw/Home/Documents/Programming/C++/Projects/SDL/Voksel/Voksel/res/D1.png", &mapWidth, &mapHeight, &nrChannels, 0);
    
    
    this->pixelWidth = mapWidth / minimapWidth;
    this->pixelHeight = mapHeight / minimapHeight;
    
    std::cout << nrChannels << std::endl;
    
    colormap = new RGB[mapWidth * mapHeight];
    heightmap = new uint8_t[mapWidth * mapHeight];
    zBuffer = new float[mapWidth];
    for (int i = 0; i < mapWidth; i++) {
        zBuffer[i] = display.GetHeight();
    }
    
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
    delete[] zBuffer;
}

/*
 * +- -+   +-        -+   +-                  -+
 * | x | * | cos -sin | = | x * cos + y * -sin |
 * | y |   | sin  cos |   | x * sin + y *  cos |
 * +- -+   +-        -+   +-                  -+
 */


void Game::Update() {
    
    float cosAngle = cos(playerAngleYaw);
    float sinAngle = sin(playerAngleYaw);
    
    
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_W)) {
        playerPosition.x += sinAngle * 3;
        playerPosition.y += -cosAngle * 3;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_S)) {
        playerPosition.x -= sinAngle * 3;
        playerPosition.y -= -cosAngle * 3;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_A)) {
        playerAngleYaw -= M_PI / 45.f;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_D)) {
        playerAngleYaw += M_PI / 45.f;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_R)) {
        playerPosition.z += 2;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_F)) {
        playerPosition.z -= 2;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_Q)) {
        playerAnglePitch -= 10;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_E)) {
        playerAnglePitch += 10;
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
    
    if(playerPosition.z <= heightmap[((int)abs(playerPosition.x) % mapWidth) + ((int)abs(playerPosition.y) % mapHeight * mapWidth)] + 10) {
        playerPosition.z = heightmap[((int)abs(playerPosition.x) % mapWidth) + ((int)abs(playerPosition.y) % mapHeight * mapWidth)] + 10;
    }

    
    display.Clear(RGB{ 0x69, 0xA5, 0xFC });

    float start = 0;
    float end = distance;
    
    for (int i = 0; i < mapWidth; i++) {
        zBuffer[i] = display.GetHeight();
    }
    float di = 1.f;
    for (float i = 1; i < distance; i += (di), di += 0.0075f) {
        vec2 leftPoint = {
            (-i * cosAngle + -i * (-sinAngle)) + playerPosition.x,
            (-i * sinAngle + -i * cosAngle)+ playerPosition.y
        };
        vec2 rightPoint = {
            (+i * cosAngle + -i * (-sinAngle))+ playerPosition.x,
            (+i * sinAngle + -i * cosAngle)+ playerPosition.y
        };
        
        float dx = (rightPoint.x - leftPoint.x) / display.GetWidth();
        float dy = (rightPoint.y - leftPoint.y) / display.GetWidth();
        
        if(dx == 0 && dy == 0) continue;

        for(int j = 0; j < display.GetWidth(); j++) {
//            display.SetPixel(
//                             newLeftPoint.x,
//                             newLeftPoint.y, (RGB) {
//                heightmap[(int)newLeftPoint.x + (int)newLeftPoint.y * mapWidth],
//                heightmap[(int)newLeftPoint.x + (int)newLeftPoint.y * mapWidth],
//                heightmap[(int)newLeftPoint.x + (int)newLeftPoint.y * mapWidth]});
//            int a =(int)newLeftPoint.x + (int)newLeftPoint.y * mapWidth;
//            display.SetPixel(
//                             newLeftPoint.x / 3,
//                             newLeftPoint.y / 3, colormap[((int)abs(newLeftPoint.x) % mapWidth) + ((int)abs(newLeftPoint.y) % mapHeight * mapWidth)]);
            
            leftPoint.x += dx;
            leftPoint.y += dy;
            
            float h = heightmap[((int)abs(leftPoint.x) % mapWidth) + ((int)abs(leftPoint.y) % mapHeight * mapWidth)];
            
            float height_on_screen = (float)((playerPosition.z - h)) / (float)i * 400.0f + playerAnglePitch;

            float distance = sqrt(i * i + playerPosition.z * playerPosition.z);
            
//            float f = (end - i) / (end - start);
            float density = 0.0015f;
            float gradient = 4;
            float f = 1.f / std::pow(EulerConstant, std::pow((distance * density), gradient));
            f = (f < 0) ? 0 : f;
            f = (f > 1) ? 1 : f;
            
            RGB groundColor = colormap[((int)abs(leftPoint.x) % mapWidth) + ((int)abs(leftPoint.y) % mapHeight * mapWidth)];
            RGB skyColor = { 0x69, 0xA5, 0xFC };
            RGB result;
            result.r = util_lerp(skyColor.r, groundColor.r, f);
            result.g = util_lerp(skyColor.g, groundColor.g, f);
            result.b = util_lerp(skyColor.b, groundColor.b, f);
            
            drawLineDown(j, height_on_screen, zBuffer[j], result);
            
            if(height_on_screen < zBuffer[j]) {
                zBuffer[j] = height_on_screen;
            }
        }
    }
    
    display.Update();
}

void Game::drawLineDown(int x, int y, float z, RGB color) {
    for(int i = 0; i < display.GetHeight() - y; i++) {
        if(y + i > z) return;
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
