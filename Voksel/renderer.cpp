//
//  renderer.cpp
//  Voksel
//
//  Created by Marat Isaw on 04.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "renderer.hpp"
#include "gameSettings.hpp"
#include "util.hpp"
#include <iostream>

Renderer::Renderer(int width, int height, uint32_t* pixels) : screenWidth { width }, screenHeight { height }, pixels(pixels) {
    zBuffer = new float[screenWidth] { };
}

Renderer::~Renderer() {
    delete[] zBuffer;
}

void Renderer::DrawFrame(RGB* colormap, uint8_t* heightmap, int mapWidth, int mapHeight, const Player& player, int renderDistance, int horizon) {
    float cosAngle = cos(player.angularPosition.y);
    float sinAngle = sin(player.angularPosition.y);

    float start = Settings::renderDistance / 10;
    float end = Settings::renderDistance;
    
    for (int i = 0; i < screenWidth; i++) {
        zBuffer[i] = screenHeight;
    }
    float di = 1.f;
    float opt = 0;
    
    for (float i = 1; i < Settings::renderDistance; i += (di), di += 0.0075f) {
        
        vec2 leftPoint = {
            (-i * cosAngle + -i * (-sinAngle)) + player.position.x,
            (-i * sinAngle + -i * cosAngle)+ player.position.y
        };
        vec2 rightPoint = {
            (+i * cosAngle + -i * (-sinAngle))+ player.position.x,
            (+i * sinAngle + -i * cosAngle)+ player.position.y
        };

        float distbetweenpoints = sqrt(pow(rightPoint.x - leftPoint.x, 2) + pow(rightPoint.y - leftPoint.y, 2));

        opt = i / (float)Settings::renderDistance;
        float numb = util::lerp(1, 1, opt);
        float dx = (rightPoint.x - leftPoint.x) / (screenWidth);
        float dy = (rightPoint.y - leftPoint.y) / (screenWidth);

        if(dx == 0 && dy == 0) continue;

        for(int j = 0; j < screenWidth; j++) {
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
            if(!(j % (int)numb)) {
                leftPoint.x += dx * (int)numb;
                leftPoint.y += dy * (int)numb;
            }
            
            float h = heightmap[((uint32_t)(leftPoint.x) % mapWidth) + ((uint32_t)(leftPoint.y) % mapHeight * mapWidth)];

//            float hb = heightmap[((uint32_t)(leftPoint.x - sinAngle) % mapWidth) + ((uint32_t)(leftPoint.y - -cosAngle) % mapHeight * mapWidth)];
//
//            float ha = heightmap[((uint32_t)(leftPoint.x + sinAngle) % mapWidth) + ((uint32_t)(leftPoint.y + -cosAngle) % mapHeight * mapWidth)];
            
            float height_on_screen = (float)((player.position.z - h)) / (float)(i) * 250.0f + horizon;

            float distance = sqrt(std::pow(i, 2) +
                                  std::pow(j / (float)screenWidth * distbetweenpoints - distbetweenpoints / 2, 2) +
                                  std::pow(player.position.z, 2));
            
//            float f = (end - distance) / (end - start);
            float density = 0.002f;
            float gradient = 3;
            float f = 1.f / std::pow(2.718281828459045235360287f, std::pow((distance * density), gradient));
//            float f = 1.f / 1 * std::pow(cosf(distance/mapWidth), 5);
            f = (f < 0) ? 0 : f;
            f = (f > 1) ? 1 : f;
//            f = 1;
            RGB groundColor = colormap[((uint32_t)(leftPoint.x) % mapWidth) + ( (uint32_t)(leftPoint.y) % mapHeight * mapWidth)];
            RGB skyColor = { 0xDC,0xD8,0xaD };
            RGB result;
            result.r = util::lerp(skyColor.r, groundColor.r, f);
            result.g = util::lerp(skyColor.g, groundColor.g, f);
            result.b = util::lerp(skyColor.b, groundColor.b, f);
            
            /*
             * tilt screen (roll):
             * height_on_screen - j / 10
             * or
             * height_on_screen + j / 10
             */
            
            
            drawLineDown(j, height_on_screen, zBuffer[j], result);
            
            if(height_on_screen < zBuffer[j]) {
                zBuffer[j] = height_on_screen;
            }
        }
    }
}

void Renderer::DrawRectangle(int x, int y, int w, int h, RGB color) {
    for(int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            SetPixel(x + i, y + j, color);
        }
    }
}

void Renderer::DrawSprite(const Sprite& sprite, int x, int y, float xScale, float yScale, float rot) {
    
}
void Renderer::DrawSprite(const Sprite& sprite, int x, int y, float rot) {
    
}
void Renderer::DrawSprite(const Sprite& sprite, int x, int y) {
    
}



void Renderer::drawLineDown(int x, int y, float z, RGB color) {
    for(int i = 0; i < screenHeight - y; i++) {
        if(y + i > z) return;
        if(y + i < 0) continue;
        this->SetPixel(x, y + i, color);
    }
}
