//
//  gfx.hpp
//  WaterRipple3
//
//  Created by Marat Isaw on 30.11.19.
//  Copyright © 2019 Marat Isaw. All rights reserved.
//

#ifndef gfx_hpp
#define gfx_hpp

#include <iostream>
#include <cmath>


struct Vertex
{
    int x;
    int y;
    uint32_t extra;
};

extern int gfx_WIDTH;
extern int gfx_HEIGHT;

void __gfx_init__(int w, int h);

void __gfx_clear__(uint32_t* pixels, uint32_t color);

void __gfx_sortVerticesByY__(Vertex arr[], int n);

void __gfx_drawLine__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2);
void __gfx_drawLineN__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2);
void __gfx_drawLineAdd__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2);
void __gfx_drawLine__(uint32_t* pixels, uint32_t color, Vertex v1, Vertex v2);

void __gfx_fillBottomFlatTriangle__(uint32_t* pixels, uint32_t c1, uint32_t c2, uint32_t c3, int x1, int y1, int x2, int y2, int x3, int y3);
void __gfx_fillBottomFlatTriangle__(uint32_t* pixels, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3, int a1, int a2, int a3, int x1, int y1, int x2, int y2, int x3, int y3);
void __gfx_fillBottomFlatTriangle__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3);

void __gfx_fillTopFlatTriangle__(uint32_t* pixels, uint32_t c1, uint32_t c2, uint32_t c3, int x1, int y1, int x2, int y2, int x3, int y3);
void __gfx_fillTopFlatTriangle__(uint32_t* pixels, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3, int a1, int a2, int a3, int x1, int y1, int x2, int y2, int x3, int y3);
void __gfx_fillTopFlatTriangle__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3);

void __gfx_drawTriangle__(uint32_t* pixels, uint32_t c1, uint32_t c2, uint32_t c3, int x1, int y1, int x2, int y2, int x3, int y3);
void __gfx_drawTriangle__(uint32_t* pixels, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3, int x1, int y1, int x2, int y2, int x3, int y3);
void __gfx_drawTriangle__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3);

void __gfx_drawTriangleOutline__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3);
void __gfx_drawTriangleOutlineAdd__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3);

void __gfx_fillRectangle__(uint32_t* pixels, uint32_t color, int x, int y, int w, int h);
void __gfx_fillRectangleAdd__(uint32_t* pixels, uint32_t color, int x, int y, int w, int h);
void __gfx_drawRectangle__(uint32_t* pixels, uint32_t color, int x, int y, int w, int h);

#endif /* gfx_hpp */
