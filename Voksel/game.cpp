//
//  game.cpp
//  Voksel
//
//  Created by Marat Isaw on 18.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "game.hpp"
#include <SDL.h>
#include <iostream>
#include <stb_image.h>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <fstream>

#include "gameSettings.hpp"
#include "tensorMath.hpp"
#include "util.hpp"
#include "gfx.hpp"
using namespace tem;


Game::Game(Display& display)
    : display (display),
    renderer (display.GetWidth(), display.GetHeight(), display.GetPixels()),
    player(),
    gameEventHandler(),
    colormap(nullptr), heightmap(nullptr), zBuffer(nullptr),
    SkyColor{0x6E,0xBE,0xFC},
    minimapZoomLevel(2.f)
{
    player.position = Settings::spawnPoint;
    player.angularPosition.y = util::DegInRad(90);
//    player.position = {1000, 0, 200};
//    player.angularPosition.y = util::DegInRad(0);
    distance = Settings::renderDistance;
    
    //std::string path = "/Users/maratisaw/Home/Documents/Programming/C++/SDL/Voksel/Voksel/res/1";
	std::string path = "./res/1";

    LoadMap(path, false);
    
    
//    if (a == 1) {
//        custom = true;
//    } else if(a == 2) {
//        path1 = "/Users/maratisaw/Home/Documents/Programming/C++/SDL/Voksel/Voksel/res/C13.png";
//        path2 = "/Users/maratisaw/Home/Documents/Programming/C++/SDL/Voksel/Voksel/res/D13.png";
//    }
    
    
    
    __gfx_init__(display.GetWidth(), display.GetHeight());
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

bool Game::LoadMap(const std::string& path, bool customMap) {
    
    if(colormap) delete[] colormap;
    if(heightmap) delete[] heightmap;
    if(zBuffer) delete[] zBuffer;
    
    if(!customMap) {
        int nrChannels;
        uint8_t* rawColormap = stbi_load((std::string {path + "_color.png"}).c_str(), &mapWidth, &mapHeight, &nrChannels, 0);
        uint8_t* rawHeightmap = stbi_load((std::string {path + "_height.png"}).c_str(), &mapWidth, &mapHeight, &nrChannels, 0);
        
		if (!rawColormap || !rawHeightmap) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
				"Missing files",
				"Files for map data are missing (more specifically the \"res\" folder)\n\nPlease refer to the author of the game",
				NULL);
			return false;
		}

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
    } else {
        std::ifstream fin { path, std::ios::binary };
        
		if (!fin) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
				"Missing files",
				"Files for map data are missing (more specifically the \"res\" folder)\n\nPlease refer to the author of the game",
				NULL);
			return false;
		}

        fin.read((char*)&mapWidth, sizeof(mapWidth));
        fin.read((char*)&mapHeight, sizeof(mapHeight));

        colormap = new RGB[mapWidth * mapHeight];
        heightmap = new uint8_t[mapWidth * mapHeight];
        zBuffer = new float[mapWidth];
        for (int i = 0; i < mapWidth; i++) {
            zBuffer[i] = display.GetHeight();
        }

        for(int i = 0; i < mapWidth * mapHeight; i++) {
            uint8_t r, g, b;
            int32_t height;
            fin.read((char*)&r, sizeof(r));
            fin.read((char*)&g, sizeof(g));
            fin.read((char*)&b, sizeof(b));
            fin.read((char*)&height, sizeof(height));
            colormap[i] = { r, g, b };
            heightmap[i] = { (uint8_t)(height/10.f) };
        }
        
        fin.close();
    }
    
    return true;
}

void Game::Update(float elapsedTime) {
    gameEventHandler.ProcessInput(*this, player, display.GetEventHandler(), elapsedTime);

    player.Update(elapsedTime);
    
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
    
    // "smooth z movement" when on ground ground
    double a = 0;
    double val = 0;
    float radius = 50;
    for (float i = -radius; i < radius; i++) {
        for (float j = -radius; j < radius; j++) {
            if(i * i + j * j <= radius * radius) {
                float sat = pow(1.f - (sqrt(std::round(i) * std::round(i) + std::round(j) * std::round(j)) / radius), 4);
                sat = util::smoothstep(0, 1, sat);
                val += getHeightmapValue(std::round(player.position.x + i), std::round(player.position.y + j)) * sat;
                a += sat / 1.1;
            }
        }
    }
    val /= (double)a;
    
    if(player.position.z <= val + 16) {
        player.position.z = val + 16;
    }
}

void Game::Render() {
    display.Clear(SkyColor);
    renderer.DrawFrame(SkyColor, colormap, heightmap, mapWidth, mapHeight, player, Settings::renderDistance, 300);
    
    // Minimap 
    float val = 0;
    int radius = 96;
    int xoffset = 8;
    int yoffset = 16;
    int isometricHeight = 128 / minimapZoomLevel; // cmd + del;
    bool isometric = true;
    float sinVal = std::sin(player.angularPosition.y);
    float cosVal = std::cos(player.angularPosition.y);
    int isoIteration = 32 / minimapZoomLevel; // cmd + del
    int minimapOffset = radius / (1 + 1.5f / minimapZoomLevel);
    for (int i = -radius; i < radius+1; i++) {
        for (int j = -radius; j < radius+1; j++) {
            float x = i * cosVal - (j - minimapOffset) * sinVal;
            float y = i * sinVal + (j - minimapOffset) * cosVal;
            if(i * i + j * j <= radius * radius) {
                if(!isometric) {
                    val = (getHeightmapValue(player.position.x + i, player.position.y + j)) / 255.f;
                    // saturation
                    float sat = pow(1.f - sqrt(i * i + j * j) / radius, 2);
                    sat *= val + 0.3;
                    sat += (val * 255 - player.position.z / 3) / 255.f;
                    sat = sat > 1 ? 1 : sat;
                    sat = sat < 0 ? 0 : sat;
                    
                    RGB color {};
                    color.r = sat * geColormapValue(player.position.x + i, player.position.y + j).r;
                    color.g = sat * geColormapValue(player.position.x + i, player.position.y + j).g;
                    color.b = sat * geColormapValue(player.position.x + i, player.position.y + j).b;
                    
                    renderer.SetPixel(i + radius+8, j + radius+8, RGB{0, (uint8_t)(sat * 255),0});
                } else {
                    val = (getHeightmapValue(player.position.x + x * minimapZoomLevel, player.position.y + y * minimapZoomLevel)) / 255.f;
                    RGB color {geColormapValue(player.position.x + x * minimapZoomLevel, player.position.y + y * minimapZoomLevel)};
                    
                    for(int iso = 0; iso < isoIteration; iso++) {
                        float isoy = j - val * isometricHeight - iso + isoIteration*2;
                        if(!(i * i + isoy * isoy <= radius * radius || isoy + radius + yoffset < radius + yoffset)) continue;
                        if(i * i + (j - minimapOffset) * (j - minimapOffset) <= 16 / minimapZoomLevel && (i + j) % 2) {
                            color = RGB{255,0,0}; // player
                        }
                        renderer.SetPixel(i + radius + xoffset, isoy + radius + yoffset, color);
                    }
                }
            }
        }
    }
    
    bool debug = false;
    if(debug) {
        static float pAcc[800] { };
        static float pVec[800] { };
        static float pAcc2[800] { };
        static float pVec2[800] { };
        static float abc = 0;
        static float abc1 = 1;
        int offset = 150;
        
        for (int i = 0; i < 800; i++) {
            renderer.SetPixel(i, display.GetHeight() / 2, {0,0,0});
            renderer.SetPixel(i, display.GetHeight() / 2 + offset, {0,0,0});
            if(i < abc) {
                __gfx_drawLine__(renderer.GetPixels(), 0x00af00ff,
                                 i - 1, display.GetHeight() / 2 - pAcc[i - 1],
                                 i, display.GetHeight() / 2 - pAcc[i]);
                __gfx_drawLine__(renderer.GetPixels(), 0x0000ffff,
                                 i - 1, display.GetHeight() / 2 - pVec[i - 1],
                                 i, display.GetHeight() / 2 - pVec[i]);
                
                __gfx_drawLine__(renderer.GetPixels(), 0x00af00ff,
                                 i - 1, display.GetHeight() / 2 - pAcc2[i - 1] + offset,
                                 i, display.GetHeight() / 2 - pAcc2[i] + offset);
                __gfx_drawLine__(renderer.GetPixels(), 0x0000ffff,
                                 i - 1, display.GetHeight() / 2 - pVec2[i - 1] + offset,
                                 i, display.GetHeight() / 2 - pVec2[i] + offset);
            }
        }
        
        abc += .5f;
        if(abc >= display.GetWidth()) {
            abc = 0;
            abc1 = 1;
        }
        if(abc > abc1) {
            abc1++;
            pAcc[(int)abc] = player.acceleration.y;
            pVec[(int)abc] = player.velocity.y;

            pAcc2[(int)abc] = player.angularAcceleration.y * 20;
            pVec2[(int)abc] = player.angularVelocity.y * 20;
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
