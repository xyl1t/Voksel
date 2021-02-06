//
//  renderer.hpp
//  Voksel
//
//  Created by Marat Isaw on 04.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp
#include "player.hpp"
#include "color.hpp"
#include "sprite.hpp"
#include "tensorMath.hpp"
using namespace tem;

// TODO: Mark function parameters as const

class Renderer {
public:
    Renderer(int width, int height, uint32_t* pixels);
    ~Renderer();
    
    inline void SetPixel(int x, int y, RGB color) {
        if(x >= 0 && y >= 0 && x < screenWidth && y < screenHeight)
            pixels[x + y * screenWidth] = color.GetUint32();
    }

    void DrawFrame(RGB skyColor, RGB* colormap, uint8_t* heightmap, int mapWidth, int mapHeight, const Player& player, int renderDistance, int horizon);
    void DrawRectangle(int x, int y, int w, int h, RGB color);
    
    void DrawSprite(const Sprite& sprite, int x, int y, float xScale, float yScale, float rot);
    void DrawSprite(const Sprite& sprite, int x, int y, float rot);
    void DrawSprite(const Sprite& sprite, int x, int y);

    inline uint32_t* GetPixels() {
        return pixels;
    }

    //test
    uint32_t* pixels;
private:
    int screenWidth;
    int screenHeight;
    
    float* zBuffer;

    void drawLineDown(int x, int y, float z, RGB color);
};


#endif /* renderer_hpp */
