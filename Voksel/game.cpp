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
#include <algorithm>

#include "gameSettings.hpp"
#include "tensorMath.hpp"
#include "util.hpp"
using namespace tem;

/*
 1. fly near mountains and water
 2. fly up - demonstrate fog
 3. fly down on the temple
 */

Game::Game(Display& display)
    : display (display),
    renderer (display.GetWidth(), display.GetHeight(), display.GetPixels()),
    player()
{
    player.position = Settings::spawnPoint;
    player.angularPosition.x = 300;
    distance = Settings::renderDistance;
    
    int nrChannels;
    uint8_t* rawColormap = stbi_load("/Users/maratisaw/Home/Documents/Programming/C++/Projects/SDL/Voksel/Voksel/res/C13.png", &mapWidth, &mapHeight, &nrChannels, 0);
    uint8_t* rawHeightmap = stbi_load("/Users/maratisaw/Home/Documents/Programming/C++/Projects/SDL/Voksel/Voksel/res/D13.png", &mapWidth, &mapHeight, &nrChannels, 0);
    
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


void Game::Update(float elapsedTime) {
    float cosAngle = cos(player.angularPosition.y);
    float sinAngle = sin(player.angularPosition.y);
    
    if(tiltFront > -0.01 && tiltFront < 0.01) tiltFront = 0;
    if(tiltSide > -0.1 && tiltSide < 0.1) tiltSide = 0;
    
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_W)) {
        if(tiltFront < 1) {
            tiltFront += .1f;
        }
    }
    else if(tiltFront > 0) {
        tiltFront -= .1f;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_S)) {
        if(abs(tiltFront) < 1) {
            tiltFront -= 0.1f;
        }
    }
    else if(tiltFront < 0) {
        tiltFront += .1f;
    }
    player.position.x += sinAngle * 3 * tiltFront * elapsedTime / 25.f;
    player.position.y += -cosAngle * 3 * tiltFront * elapsedTime / 25.f;

    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_A)) {
        if(tiltSide < 1)
            tiltSide += .1f;
    }
    else if(tiltSide > 0) {
        tiltSide -= .1f;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_D)) {
        if(abs(tiltSide) < 1)
            tiltSide -= .1f;
    }
    else if(tiltSide < 0) {
        tiltSide += .1f;
    }

    player.angularPosition.y -= M_PI / 55.f * tiltSide * elapsedTime / 20.f;
    
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_SPACE)) {
        player.position.z += 3;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_LSHIFT)) {
        player.position.z -= 3;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_Q)) {
        player.angularPosition.x -= 10;
    }
    if(display.GetEventHandler().IsKeyDown(SDL_SCANCODE_E)) {
        player.angularPosition.x += 10;
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
    
    double a = 0;
    double val = 0;
    for (int i = -30; i < 31; i++) {
        for (int j = -30; j < 31; j++) {
            if(i * i + j * j <= 30 * 30) {
                float sat = pow(1.f - sqrt(i * i + j * j) / 30.f, 1);
                val += getHeightmapValue(player.position.x + i, player.position.y + j)*sat;
                a += sat;
            }
        }
    }
    val /= (double)a;
    
    
    if(player.position.z <= val + 50) {
        player.position.z = val + 50;
    }

    
//    display.Clear(RGB{ 0xDC,0xD8,0xaD });
//
//    float start = distance / 10;
//    float end = distance;
//    
//    for (int i = 0; i < mapWidth; i++) {
//        zBuffer[i] = display.GetHeight();
//    }
//    float di = 1.f;
//    float opt = 0;
//    for (float i = 1; i < distance; i += (di), di += 0.0075f) {
//        vec2 leftPoint = {
//            (-i * cosAngle + -i * (-sinAngle)) + player.position.x,
//            (-i * sinAngle + -i * cosAngle)+ player.position.y
//        };
//        vec2 rightPoint = {
//            (+i * cosAngle + -i * (-sinAngle))+ player.position.x,
//            (+i * sinAngle + -i * cosAngle)+ player.position.y
//        };
//
//        float distbetweenpoints = sqrt(std::pow(rightPoint.x - leftPoint.x, 2) + std::pow(rightPoint.y - leftPoint.y, 2));
//
//        opt = i / (float)distance;
//        float numb = util_lerp(1, 1, opt);
//        float dx = (rightPoint.x - leftPoint.x) / (display.GetWidth());
//        float dy = (rightPoint.y - leftPoint.y) / (display.GetWidth());
//        
//        if(dx == 0 && dy == 0) continue;
//
//        for(int j = 0; j < display.GetWidth(); j++) {
////            display.SetPixel(
////                             newLeftPoint.x,
////                             newLeftPoint.y, (RGB) {
////                heightmap[(int)newLeftPoint.x + (int)newLeftPoint.y * mapWidth],
////                heightmap[(int)newLeftPoint.x + (int)newLeftPoint.y * mapWidth],
////                heightmap[(int)newLeftPoint.x + (int)newLeftPoint.y * mapWidth]});
////            int a =(int)newLeftPoint.x + (int)newLeftPoint.y * mapWidth;
////            display.SetPixel(
////                             newLeftPoint.x / 3,
////                             newLeftPoint.y / 3, colormap[((int)abs(newLeftPoint.x) % mapWidth) + ((int)abs(newLeftPoint.y) % mapHeight * mapWidth)]);
//            if(!(j % (int)numb)) {
//                leftPoint.x += dx * (int)numb;
//                leftPoint.y += dy * (int)numb;
//            }
//            
//            float h = heightmap[((uint32_t)(leftPoint.x) % mapWidth) + ((uint32_t)(leftPoint.y) % mapHeight * mapWidth)];
//
////            float hb = heightmap[((uint32_t)(leftPoint.x - sinAngle) % mapWidth) + ((uint32_t)(leftPoint.y - -cosAngle) % mapHeight * mapWidth)];
////
////            float ha = heightmap[((uint32_t)(leftPoint.x + sinAngle) % mapWidth) + ((uint32_t)(leftPoint.y + -cosAngle) % mapHeight * mapWidth)];
//            
//            float height_on_screen = (float)((player.position.z - h)) / (float)(i) * 250.0f + 100 * -tiltFront/2 + player.angularPosition.x;
//
//            float distance = sqrt(std::pow(i, 2) +
//                                  std::pow(j / (float)display.GetWidth() * distbetweenpoints - distbetweenpoints / 2, 2) +
//                                  std::pow(player.position.z, 2));
//            
////            float f = (end - distance) / (end - start);
//            float density = 0.002f;
//            float gradient = 3;
//            float f = 1.f / std::pow(EulerConstant, std::pow((distance * density), gradient));
////            float f = 1.f / 1 * std::pow(cosf(distance/mapWidth), 5);
//            f = (f < 0) ? 0 : f;
//            f = (f > 1) ? 1 : f;
////            f = 1;
//            RGB groundColor = colormap[((uint32_t)(leftPoint.x) % mapWidth) + ( (uint32_t)(leftPoint.y) % mapHeight * mapWidth)];
//            RGB skyColor = { 0xDC,0xD8,0xaD };
//            RGB result;
//            result.r = util_lerp(skyColor.r, groundColor.r, f);
//            result.g = util_lerp(skyColor.g, groundColor.g, f);
//            result.b = util_lerp(skyColor.b, groundColor.b, f);
//            
//            /*
//             * tilt screen (roll):
//             * height_on_screen - j / 10
//             * or
//             * height_on_screen + j / 10
//             */
//            
//            
//            drawLineDown(j, height_on_screen + (j - display.GetWidth() / 2) / 10 * tiltSide, zBuffer[j], result);
//            
//            if(height_on_screen + (j - display.GetWidth() / 2) / 10 * tiltSide < zBuffer[j]) {
//                zBuffer[j] = height_on_screen + (j - display.GetWidth() / 2) / 10 * tiltSide;
//            }
//        }
//    }
//    
//    display.Update();
}

void Game::Render() {
    display.Clear(RGB{ 0xDC,0xD8,0xaD });
//    for (int j = 0; j < 100; j++)
//    for(int i = 0; i < display.GetWidth() * display.GetHeight();i++)
//        renderer.SetPixel(i % display.GetWidth(), i/display.GetWidth(), (RGB){0,255,0});
    renderer.DrawFrame(colormap, heightmap, mapWidth, mapHeight, player, Settings::renderDistance, player.angularPosition.x);

//    float cosAngle = cos(-player.angularPosition.y + (0 * (180 / M_PI)));
//    float sinAngle = sin(+player.angularPosition.y - (0 * (180 / M_PI)));

    float val = 0;
    for (int i = -100; i < 100; i++) {
        for (int j = -100; j < 100; j++) {
            if(i * i + j * j <= 100 * 100) {
                float sat = pow(1.f - sqrt(i * i + j * j) / 100.f, 1);
                val = (getHeightmapValue(player.position.x + i, player.position.y + j))/ 255.f;
                sat *= val * 2;
                sat += (val * 255 - player.position.z / 3) / 255.f;
                sat = sat > 1 ? 1 : sat;
                sat = sat < 0 ? 0 : sat;


//                int ni = (i * cosAngle + j * (sinAngle));
//                int nj = (i * -sinAngle + j * cosAngle);

                renderer.SetPixel(i + 100, j + 100, RGB{0, (uint8_t)(sat * 255),0});
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

     int playerX = player.position.x;
     int playerY = player.position.y;

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
