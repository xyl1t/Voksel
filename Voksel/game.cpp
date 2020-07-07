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
    
    // smooth movement
    double a = 0;
    double val = 0;
    for (int i = -25; i < 26; i++) {
        for (int j = -25; j < 26; j++) {
            if(i * i + j * j <= 25 * 25) {
                float sat = pow(1.f - sqrt(i * i + j * j) / 25.f, 1.5);
                val += getHeightmapValue(player.position.x + i, player.position.y + j)*sat;
                a += sat * sat * 1.75f;
            }
        }
    }
    val /= (double)a;
    
    
    if(player.position.z <= val + 20) {
        player.position.z = val + 20;
    }
}

void Game::Render() {
    display.Clear(RGB{ 0xDC,0xD8,0xaD });
    renderer.DrawFrame(colormap, heightmap, mapWidth, mapHeight, player, Settings::renderDistance, player.angularPosition.x);
    
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
