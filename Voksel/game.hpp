//
//  game.hpp
//  Voksel
//
//  Created by Marat Isaw on 18.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "renderer.hpp"
#include "player.hpp"
#include "color.hpp"
#include "display.hpp"
#include "tensorMath.hpp"
#include "gameEventHandler.hpp"
#include <cmath>
using namespace tem;

class Game {
public:
    
    Game(Display& display);
    
    void Update(float elapsedTime);
    void Render();
    
    bool LoadMap(const std::string& path, bool customMap);

    RGB SkyColor;

    ~Game();
    
    float minimapZoomLevel;
private:
    Display& display;
    Renderer renderer;
    Player player;
    GameEventHandler gameEventHandler;
    
    int distance;
    RGB* colormap;
    uint8_t* heightmap;
    int mapWidth;
    int mapHeight;
    
    inline uint8_t getHeightmapValue(int x, int y) {
        return heightmap[(uint32_t)x % mapWidth + (uint32_t)y % mapHeight * mapWidth];
    }
    inline const RGB& geColormapValue(int x, int y) {
        return colormap[(uint32_t)x % mapWidth + (uint32_t)y % mapHeight * mapWidth];
    }
    
    float tiltFront = 0;
    float tiltSide = 0;
    
    float* zBuffer;
    int minimapWidth;    //= 128;
    int minimapHeight;   //= 128;
    float pixelWidth;    //= mapWidth / minimapWidth;
    float pixelHeight;   //= mapHeight / minimapHeight;

    static constexpr float EulerConstant = 2.71828182845904523536028747135266249775724709369995f;
    
    void drawLineDown(int x, int y, float z, RGB color);
};

#endif /* GAME_HPP */
