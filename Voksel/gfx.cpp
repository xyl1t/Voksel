//
//  gfx.cpp
//  WaterRipple3
//
//  Created by Marat Isaw on 30.11.19.
//  Copyright © 2019 Marat Isaw. All rights reserved.
//

#include <iostream>
#include "gfx.hpp"
#include "util.hpp"

int gfx_WIDTH = -1;
int gfx_HEIGHT = -1;

void __gfx_init__(int w, int h) {
    gfx_WIDTH = w;
    gfx_HEIGHT = h;
}

void __gfx_clear__(uint32_t* pixels, uint32_t color) {
    for (uint32_t i = 0; i < gfx_WIDTH * gfx_HEIGHT; i++) {
        pixels[i] = color;
    }
}

void __gfx_sortVerticesByY__(Vertex arr[], int n)
{
    int i, j, min_idx;
  
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j].y < arr[min_idx].y)
                min_idx = j;
  
        // Swap the found minimum element with the first element
        Vertex t = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = t;
//        swap(&arr[min_idx], &arr[i]);
    }
}

void __gfx_drawLine__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2)
{
    int rise = y2 - y1;
    int run = x2 - x1;

    // Vertical
    if(run == 0) {
        if(y2 < y1) {
            std::swap(y1, y2);
        }
        for(int y = y1; y < y2; y++) {
            if(x1 >= 0 && x1 < gfx_WIDTH && y >= 0 && y < gfx_HEIGHT)
                pixels[x1 + y * gfx_WIDTH] = color;
        }
    }
    else {
        float m = rise / (float)run;
        int adjust = (m >= 0) ? 1 : -1;
        int offset = 0;

        if(m <= 1 && m >= -1) {
            int delta = std::abs(rise) * 2;
            int threshold = abs(run);
            int thresholdInc = abs(run) * 2;
            int y = y1;
            if(x2 < x1) {
                std::swap(x1, x2);
                y = y2;
            }
            for(int x = x1; x < x2; x++) {
                if(x >= 0 && x < gfx_WIDTH && y >= 0 && y < gfx_HEIGHT)
                    pixels[x + y * gfx_WIDTH] = color;
                offset += delta;
                if(offset >= threshold) {
                    y += adjust;
                    threshold += thresholdInc;
                }
            }
        }
        else {
            int delta = abs(run) * 2;
            int threshold = abs(rise);
            int thresholdInc = abs(rise) * 2;
            int x = x1;
            if(y2 < y1) {
                std::swap(y1, y2);
                x = x2;
            }
            for(int y = y1; y < y2; y++) {
                if(x >= 0 && x < gfx_WIDTH && y >= 0 && y < gfx_HEIGHT)
                    pixels[x + y * gfx_WIDTH] = color;
                offset += delta;
                if(offset >= threshold) {
                    x += adjust;
                    threshold += thresholdInc;
                }
            }
        }
    }

    return;
    
    
    float dx = x2 - x1;
    float dy = y2 - y1;

//    if(x1 >= 0 && x1 < gfx_WIDTH && y1 >= 0 && y1 < gfx_HEIGHT)
//        pixels[x1 + y1 * gfx_WIDTH] = color;
//    if(x2 >= 0 && x2 < gfx_WIDTH && y2 >= 0 && y2 < gfx_HEIGHT)
//        pixels[x2 + y2 * gfx_WIDTH] = color;
    
    // vertical line
    if(dx == 0)
    {
        dy = abs(dy);
        
        int y = fmax(y1, y2);
        
        while(dy > 0)
        {
            if(x1 >= 0    && y >= 0 &&
               x1 < gfx_WIDTH && y < gfx_HEIGHT)
                pixels[x1 + y * gfx_WIDTH] = color;
            y--;
            --dy;
        }
    }
    // horizontal line
    else if(dy == 0)
    {
        dx = abs(dx);
        
        int x = fmax(x1, x2);
        
        while(dx > 0)
        {
            if(x >= 0    && y1 >= 0 &&
               x < gfx_WIDTH && y1 < gfx_HEIGHT)
                pixels[x + y1 * gfx_WIDTH] = color;
            x--;
            --dx;
        }
    }
    else
    {
        float m = dy / dx;
        
        float b = y1 - m * x1;
        
        // steep
        if(abs(m) > 1.0f)
        {
            dy = abs(dy);
            
            int y = fmax(y1, y2);
            
            while(dy > 0)
            {
                int x = roundf((y - b) / m);
                if(x >= 0    && y >= 0 &&
                   x < gfx_WIDTH && y < gfx_HEIGHT)
                    pixels[x + y * gfx_WIDTH] = color;
                y--;
                --dy;
            }
        }
        else
        {
            dx = abs(dx);
            
            int x = fmax(x1, x2);
            
            while(dx > 0)
            {
                int y = roundf(m * x + b);
                
                if(x >= 0    && y >= 0 &&
                   x < gfx_WIDTH && y < gfx_HEIGHT)
                    pixels[x + y * gfx_WIDTH] = color;
                x--;
                --dx;
            }
        }
    }
}
void __gfx_drawLineN__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

//    if(x1 >= 0 && x1 < gfx_WIDTH && y1 >= 0 && y1 < gfx_HEIGHT)
//        pixels[x1 + y1 * gfx_WIDTH] = color;
//    if(x2 >= 0 && x2 < gfx_WIDTH && y2 >= 0 && y2 < gfx_HEIGHT)
//        pixels[x2 + y2 * gfx_WIDTH] = color;
    
    // vertical line
    if(dx == 0)
    {
        dy = abs(dy);
        
        int y = fmax(y1, y2);
        
        while(dy > 0)
        {
            if(x1 >= 0    && y >= 0 &&
               x1 < gfx_WIDTH && y < gfx_HEIGHT)
                pixels[x1 + y * gfx_WIDTH] = color;
            y--;
            --dy;
        }
    }
    // horizontal line
    else if(dy == 0)
    {
        dx = abs(dx);
        
        int x = fmax(x1, x2);
        
        while(dx > 0)
        {
            if(x >= 0    && y1 >= 0 &&
               x < gfx_WIDTH && y1 < gfx_HEIGHT)
                pixels[x + y1 * gfx_WIDTH] = color;
            x--;
            --dx;
        }
    }
    else
    {
        float m = dy / dx;
        
        float b = y1 - m * x1;
        
        // steep
        if(abs(m) > 1.0f)
        {
            dy = abs(dy);
            
            int y = fmax(y1, y2);
            
            while(dy > 0)
            {
                int x = roundf((y - b) / m);
                if(x >= 0    && y >= 0 &&
                   x < gfx_WIDTH && y < gfx_HEIGHT)
                    pixels[x + y * gfx_WIDTH] = color;
                y--;
                --dy;
            }
        }
        else
        {
            dx = abs(dx);
            
            int x = fmax(x1, x2);
            
            while(dx > 0)
            {
                int y = roundf(m * x + b);
                
                if(x >= 0    && y >= 0 &&
                   x < gfx_WIDTH && y < gfx_HEIGHT)
                    pixels[x + y * gfx_WIDTH] = color;
                x--;
                --dx;
            }
        }
    }
}

void __gfx_drawLineAdd__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    
    uint32_t cr = (color >> 24) & 0xff;
    uint32_t cg = (color >> 16) & 0xff;
    uint32_t cb = (color >> 8) & 0xff;
    uint32_t ca = (color) & 0xff;
    
    
    
    // vertical line
    if(dx == 0)
    {
        dy = abs(dy);
        
        int y = fmax(y1, y2);
        
        while(dy > 0)
        {
            if(x1 + (y - 1) * gfx_WIDTH > 0 && x1 + (y - 1) * gfx_WIDTH < gfx_WIDTH * gfx_HEIGHT)
            {
                int index = x1 + y-- * gfx_WIDTH;
                uint32_t newr = util::clamp(((pixels[index] >> 24) & 0xff) + cr, 0, 255);
                uint32_t newg = util::clamp(((pixels[index] >> 16) & 0xff) + cg, 0, 255);
                uint32_t newb = util::clamp(((pixels[index] >>  8) & 0xff) + cb, 0, 255);
                uint32_t newa = util::clamp(((pixels[index]      ) & 0xff) + ca, 0, 255);
                pixels[index] = (newr << 24) + (newg << 16) + (newb << 8) + newa;
            }
            --dy;
        }
    }
    // horizontal line
    else if(dy == 0)
    {
        dx = abs(dx);
        
        int x = fmax(x1, x2);
        
        while(dx > 0)
        {
            if((x - 1) + y1 * gfx_WIDTH > 0 && (x - 1) + y1 * gfx_WIDTH < gfx_WIDTH * gfx_HEIGHT)
            {
                int index = x-- + y1 * gfx_WIDTH;
                uint32_t newr = util::clamp(((pixels[index] >> 24) & 0xff) + cr, 0, 255);
                uint32_t newg = util::clamp(((pixels[index] >> 16) & 0xff) + cg, 0, 255);
                uint32_t newb = util::clamp(((pixels[index] >>  8) & 0xff) + cb, 0, 255);
                uint32_t newa = util::clamp(((pixels[index]      ) & 0xff) + ca, 0, 255);
                pixels[index] = (newr << 24) + (newg << 16) + (newb << 8) + newa;
                
                pixels[index] = color;
            }
            --dx;
        }
    }
    else
    {
        float m = dy / dx;
        
        float b = y1 - m * x1;
        
        // steep
        if(abs(m) > 1.0f)
        {
            dy = abs(dy);
            
            int y = fmax(y1, y2);
            
            while(dy > 0)
            {
                int x = roundf((y - b) / m);
                if(x + (y - 1) * gfx_WIDTH > 0 && x + (y - 1) * gfx_WIDTH < gfx_WIDTH * gfx_HEIGHT)
                {
                    int index = x + y-- * gfx_WIDTH;
                    uint32_t newr = util::clamp(((pixels[index] >> 24) & 0xff) + cr, 0, 255);
                    uint32_t newg = util::clamp(((pixels[index] >> 16) & 0xff) + cg, 0, 255);
                    uint32_t newb = util::clamp(((pixels[index] >>  8) & 0xff) + cb, 0, 255);
                    uint32_t newa = util::clamp(((pixels[index]      ) & 0xff) + ca, 0, 255);
                    pixels[index] = (newr << 24) + (newg << 16) + (newb << 8) + newa;
                }
                --dy;
            }
        }
        else
        {
            dx = abs(dx);
            
            int x = fmax(x1, x2);
            
            while(dx > 0)
            {
                int y = roundf(m * x + b);
                
                if((x - 1) + y * gfx_WIDTH > 0 && (x - 1) + y * gfx_WIDTH < gfx_WIDTH * gfx_HEIGHT)
                {
                    int index = x-- + y * gfx_WIDTH;
                    uint32_t newr = util::clamp(((pixels[index] >> 24) & 0xff) + cr, 0, 255);
                    uint32_t newg = util::clamp(((pixels[index] >> 16) & 0xff) + cg, 0, 255);
                    uint32_t newb = util::clamp(((pixels[index] >>  8) & 0xff) + cb, 0, 255);
                    uint32_t newa = util::clamp(((pixels[index]      ) & 0xff) + ca, 0, 255);
                    pixels[index] = (newr << 24) + (newg << 16) + (newb << 8) + newa;
                }
                --dx;
            }
        }
    }
}

void __gfx_drawLine__(uint32_t* pixels, uint32_t color, Vertex v1, Vertex v2)
{
    __gfx_drawLine__(pixels, color, v1.x, v1.y, v2.x, v2.y);
}

/* fillBottomFlatTriangle */
void __gfx_fillBottomFlatTriangle__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3)
{
    Vertex vertices[3] =
    {
        Vertex { x1, y1 },
        Vertex { x2, y2 },
        Vertex { x3, y3 }
    };
    __gfx_sortVerticesByY__(vertices, 3);
    y1 = vertices[0].y;
    x1 = vertices[0].x;
    y2 = vertices[1].y;
    x2 = vertices[1].x;
    y3 = vertices[2].y;
    x3 = vertices[2].x;
    
    float invslope1 = (x2 - x1) / (float)(y2 - y1);
    float invslope2 = (x3 - x1) / (float)(y3 - y1);

    float curx1 = x1;
    float curx2 = x1;
    
    
    for (int scanlineY = y1; scanlineY < y2; scanlineY++)
    {
        for (int x = fmin(curx1, curx2); x <= fmax(curx1, curx2); x++)
            pixels[x + scanlineY * gfx_WIDTH] = color;
        
        curx1 += invslope1;
        curx2 += invslope2;
    }
}
void __gfx_fillBottomFlatTriangle__(uint32_t* pixels, uint32_t c1, uint32_t c2, uint32_t c3, int x1, int y1, int x2, int y2, int x3, int y3)
{
    Vertex vertices[3] =
    {
        Vertex { x1, y1 },
        Vertex { x2, y2 },
        Vertex { x3, y3 }
    };
    __gfx_sortVerticesByY__(vertices, 3);
    y1 = vertices[0].y;
    x1 = vertices[0].x;
    y2 = vertices[1].y;
    x2 = vertices[1].x;
    y3 = vertices[2].y;
    x3 = vertices[2].x;
    
    float invslope1 = (x2 - x1) / (float)(y2 - y1);
    float invslope2 = (x3 - x1) / (float)(y3 - y1);

    float curx1 = x1;
    float curx2 = x1;

    for (int scanlineY = y1; scanlineY <= y2; scanlineY++)
    {
        uint32_t c;
        for (int x = fmin(curx1, curx2); x < fmax(curx1, curx2); x++)
        {
            float w1 = ((y2 - y3) * (x - x3) + (x3 - x2) * (scanlineY - y3))
                     / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
            
            float w2 = ((y3 - y1) * (x - x3) + (x1 - x3) * (scanlineY - y3))
                     / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3)) ;
            
            if(w2 < 0)
                w2 = 0;
            if(w2 > 1)
                w2 = 1;
            if(w1 < 0)
                w1 = 0;
            if(w1 > 1)
                w1 = 1;
            
            float w3 = 1 - w1 - w2;
            
            int r = abs(w1 * (c1 >> 24 & 0xff) + w2 * (c2 >> 24 & 0xff) + w3 * (c3 >> 24 & 0xff));
            int g = abs(w1 * (c1 >> 16 & 0xff) + w2 * (c2 >> 16 & 0xff) + w3 * (c3 >> 16 & 0xff));
            int b = abs(w1 * (c1 >> 8 & 0xff) + w2 * (c2 >> 8 & 0xff) + w3 * (c3 >> 8 & 0xff));
            int a = abs(w1 * (c1 >> 0 & 0xff) + w2 * (c2 >> 0 & 0xff) + w3 * (c3 >> 0 & 0xff));
            
            c = (r << 24) +
                (g << 16) +
                (b << 8) +
                (a);
            
            if(x >= 0 && x < gfx_WIDTH && scanlineY >= 0 && scanlineY < gfx_HEIGHT)
                pixels[x + scanlineY * gfx_WIDTH] = c;
        }
        curx1 += invslope1;
        curx2 += invslope2;
    }
}
void __gfx_fillBottomFlatTriangle__(uint32_t* pixels, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3, int a1, int a2, int a3, int x1, int y1, int x2, int y2, int x3, int y3)
{
    __gfx_fillBottomFlatTriangle__(pixels,
                           (r1 << 24) + (g1 << 16) + (b1 << 8) + (a1),
                           (r2 << 24) + (g2 << 16) + (b2 << 8) + (a2),
                           (r3 << 24) + (g3 << 16) + (b3 << 8) + (a3),
                           x1, y1,
                           x2, y2,
                           x3, y3);
}
void fillBottomFlatTriangle(uint32_t* pixels, uint32_t color, Vertex v1, Vertex v2, Vertex v3)
{
    __gfx_fillBottomFlatTriangle__(pixels, color, v1.x, v1.y, v2.x, v2.y, v2.x, v2.y);
}

void __gfx_fillTopFlatTriangle__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3)
{
    Vertex vertices[3] =
    {
        Vertex { x1, y1 },
        Vertex { x2, y2 },
        Vertex { x3, y3 }
    };
    __gfx_sortVerticesByY__(vertices, 3);
    y1 = vertices[0].y;
    x1 = vertices[0].x;
    y2 = vertices[1].y;
    x2 = vertices[1].x;
    y3 = vertices[2].y;
    x3 = vertices[2].x;
    
    float invslope1 = (x3 - x1) / (float)(y3 - y1);
    float invslope2 = (x3 - x2) / (float)(y3 - y2);

    float curx1 = x3;
    float curx2 = x3;

    int max = fmax(y1, fmax(y2, y3));
    int min = fmin(y1, fmin(y2, y3));
    
    for (int scanlineY = max; scanlineY > min; scanlineY--)
    {
        for (int x = fmin(curx1, curx2); x < fmax(curx1, curx2); x++)
            pixels[x + scanlineY * gfx_WIDTH] = color;
        
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
    
//    drawLine(pixels, 0xff0000ff, x1, y1, x2, y2);
//    drawLine(pixels, 0x0000ffff, x2, y2, x3, y3);
//    drawLine(pixels, 0x00ff00ff, x3, y3, x1, y1);
}
void __gfx_fillTopFlatTriangle__(uint32_t* pixels, uint32_t c1, uint32_t c2, uint32_t c3, int x1, int y1, int x2, int y2, int x3, int y3)
{
    Vertex vertices[3] =
    {
        Vertex { x1, y1 },
        Vertex { x2, y2 },
        Vertex { x3, y3 }
    };
    __gfx_sortVerticesByY__(vertices, 3);
    y1 = vertices[0].y;
    x1 = vertices[0].x;
    y2 = vertices[1].y;
    x2 = vertices[1].x;
    y3 = vertices[2].y;
    x3 = vertices[2].x;
    
    float invslope1 = (x3 - x1) / (float)(y3 - y1);
    float invslope2 = (x3 - x2) / (float)(y3 - y2);

    float curx1 = x3;
    float curx2 = x3;

    for (int scanlineY = y3; scanlineY > y1; scanlineY--)
    {
        uint32_t c;
        for (int x = fmin(curx1, curx2); x < fmax(curx1, curx2); x++)
        {
//            float dist1 = sqrt((x1 - x)*(x1 - x) + (y1 - scanlineY)*(y1 - scanlineY));
//            float dist2 = sqrt((x2 - x)*(x2 - x) + (y2 - scanlineY)*(y2 - scanlineY));
//            float dist3 = sqrt((x3 - x)*(x3 - x) + (y3 - scanlineY)*(y3 - scanlineY));
//            float w1 = 1 / dist1;
//            float w2 = 1 / dist2;
//            float w3 = 1 / dist3;
            float w1 = ((y2 - y3) * (x - x3) + (x3 - x2) * (scanlineY - y3))
                     / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
            
            float w2 = ((y3 - y1) * (x - x3) + (x1 - x3) * (scanlineY - y3))
                     / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3)) ;
            
            if(w2 < 0)
                w2 = 0;
            if(w2 > 1)
                w2 = 1;
            if(w1 < 0)
                w1 = 0;
            if(w1 > 1)
                w1 = 1;
            
            float w3 = 1 - w1 - w2;
            
            
            int r = abs(w1 * (c1 >> 24 & 0xff) + w2 * (c2 >> 24 & 0xff) + w3 * (c3 >> 24 & 0xff));
            int g = abs(w1 * (c1 >> 16 & 0xff) + w2 * (c2 >> 16 & 0xff) + w3 * (c3 >> 16 & 0xff));
            int b = abs(w1 * (c1 >> 8 & 0xff) + w2 * (c2 >> 8 & 0xff) + w3 * (c3 >> 8 & 0xff));
            int a = abs(w1 * (c1 >> 0 & 0xff) + w2 * (c2 >> 0 & 0xff) + w3 * (c3 >> 0 & 0xff));
            
            c = ((int)(r ) << 24) +
                ((int)(g ) << 16) +
                ((int)(b ) << 8) +
                (a);
            
            if(x >= 0 && x < gfx_WIDTH && scanlineY >= 0 && scanlineY < gfx_HEIGHT)
                pixels[x + (scanlineY) * gfx_WIDTH] = c;
        }
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void __gfx_fillTopFlatTriangle__(uint32_t* pixels, int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3, int a1, int a2, int a3, int x1, int y1, int x2, int y2, int x3, int y3)
{
    __gfx_fillBottomFlatTriangle__(pixels,
                           (r1 << 24) + (g1 << 16) + (b1 << 8) + (a1),
                           (r2 << 24) + (g2 << 16) + (b2 << 8) + (a2),
                           (r3 << 24) + (g3 << 16) + (b3 << 8) + (a3),
                           x1, y1,
                           x2, y2,
                           x3, y3);
}
void fillTopFlatTriangle(uint32_t* pixels, uint32_t color, Vertex v1, Vertex v2, Vertex v3)
{
    __gfx_fillTopFlatTriangle__(pixels, color, v1.x, v1.y, v2.x, v2.y, v2.x, v2.y);
}

void __gfx_drawTriangle__(uint32_t* pixels, uint32_t c1, uint32_t c2, uint32_t c3, int x1, int y1, int x2, int y2, int x3, int y3)
{
    Vertex vertices[3] =
    {
        Vertex { x1, y1, c1 },
        Vertex { x2, y2, c2 },
        Vertex { x3, y3, c3 }
    };
    
    __gfx_sortVerticesByY__(vertices, 3);
    
    y1 = vertices[0].y;
    x1 = vertices[0].x;
    c1 = vertices[0].extra;
    
    y2 = vertices[1].y;
    x2 = vertices[1].x;
    c2 = vertices[1].extra;
    
    y3 = vertices[2].y;
    x3 = vertices[2].x;
    c3 = vertices[2].extra;
    
    //    delete vertices;
    
    /* here we know that v1.y <= v2.y <= v3.y */
    /* check for trivial case of bottom-flat triangle */
    if (y2 == y3)
    {
        __gfx_fillBottomFlatTriangle__(pixels,
                               c1, c2, c3,
                               x1, y1,
                               x2, y2,
                               x3, y3);
    }
    /* check for trivial case of top-flat triangle */
    else if (y1 == y2)
    {
        __gfx_fillTopFlatTriangle__(pixels,
                            c1, c2, c3,
                            x1, y1,
                            x2, y2,
                            x3, y3);
        
    }
    else
    {
        /* general case - split the triangle in a topflat and bottom-flat one */
//        Vertice v4 = new Vertice(
//          (int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x)), vt2.y);
        float x4 = (int)(x1 + ((float)(y2 - y1) / (float)(y3 - y1)) * (x3 - x1));
        float y4 = y2;
        
        float w1 = ((y2 - y3) * (x4 - x3) + (x3 - x2) * (y4 - y3))
            / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));

        float w2 = ((y3 - y1) * (x4 - x3) + (x1 - x3) * (y4 - y3))
            / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3)) ;

        if(w2 < 0)
            w2 = 0;
        if(w2 > 1)
            w2 = 1;
        if(w1 < 0)
            w1 = 0;
        if(w1 > 1)
            w1 = 1;

        float w3 = 1 - w1 - w2;

        int r4 = abs(w1 * (c1 >> 24 & 0xff) + w2 * (c2 >> 24 & 0xff) + w3 * (c3 >> 24 & 0xff));
        int g4 = abs(w1 * (c1 >> 16 & 0xff) + w2 * (c2 >> 16 & 0xff) + w3 * (c3 >> 16 & 0xff));
        int b4 = abs(w1 * (c1 >> 8 & 0xff) + w2 * (c2 >> 8 & 0xff) + w3 * (c3 >> 8 & 0xff));
        int a4 = abs(w1 * (c1 >> 0 & 0xff) + w2 * (c2 >> 0 & 0xff) + w3 * (c3 >> 0 & 0xff));
        int c4 = ((int)(r4) << 24) + ((int)(g4) << 16) + ((int)(b4) << 8) + (a4);
        
        __gfx_fillBottomFlatTriangle__(pixels,
                               c1,
                               c2,
                               c4,
                               x1, y1,
                               x2, y2,
                               x4, y4);
        
        __gfx_fillTopFlatTriangle__(pixels,
                            c2,
                            c4,
                            c3,
                            x2, y2,
                            x4, y4,
                            x3, y3);
        
//        drawLine(pixels, 0xffffffff, x1, y1, x2, y2);
//        drawLine(pixels, 0xffffffff, x2, y2, x3, y3);
//        drawLine(pixels, 0xffffffff, x3, y3, x1, y1);
//        drawLine(pixels, 0xffffffff, x2, y2, x4, y4);
        
    }
}

void __gfx_drawTriangle__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3)
{
//    std::cout << "STARTING TO RENDER TRIANGLE" << std::endl;
//
//    std::cout << "BEFORE SORTING: " << std::endl;
//    std::cout << "y1: " << y1 << std::endl;
//    std::cout << "y2: " << y2 << std::endl;
//    std::cout << "y3: " << y3 << std::endl << std::endl;
    
    /* at first sort the three vertices by y-coordinate ascending so v1 is the topmost vertice */
    Vertex vertices[3] =
    {
        Vertex { x1, y1 },
        Vertex { x2, y2 },
        Vertex { x3, y3 }
    };
    
    __gfx_sortVerticesByY__(vertices, 3);
    y1 = vertices[0].y;
    x1 = vertices[0].x;
    y2 = vertices[1].y;
    x2 = vertices[1].x;
    y3 = vertices[2].y;
    x3 = vertices[2].x;
    
    
    
//    delete vertices;
    
    /* here we know that v1.y <= v2.y <= v3.y */
    /* check for trivial case of bottom-flat triangle */
    if (y2 == y3)
    {
        __gfx_fillBottomFlatTriangle__(pixels, color, x1, y1, x2, y2, x3, y3);
    }
    /* check for trivial case of top-flat triangle */
    else if (y1 == y2)
    {
        __gfx_fillTopFlatTriangle__(pixels, color, x1, y1, x2, y2, x3, y3);
    }
    else
    {
        /* general case - split the triangle in a topflat and bottom-flat one */
//        Vertice v4 = new Vertice(
//          (int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x)), vt2.y);
        float x4 = (int)(x1 + ((float)(y2 - y1) / (float)(y3 - y1)) * (x3 - x1));
        float y4 = y2;
        __gfx_fillBottomFlatTriangle__(pixels, color, x1, y1, x2, y2, x4, y4);
        __gfx_fillTopFlatTriangle__(pixels, color, x2, y2, x4, y4, x3, y3);
    }
}


void __gfx_drawTriangle__(uint32_t* pixels,
                  int r1, int g1, int b1,
                  int r2, int g2, int b2,
                  int r3, int g3, int b3,
                  int x1, int y1,
                  int x2, int y2,
                  int x3, int y3)
{
    //    std::cout << "STARTING TO RENDER TRIANGLE" << std::endl;
    //
    //    std::cout << "BEFORE SORTING: " << std::endl;
    //    std::cout << "y1: " << y1 << std::endl;
    //    std::cout << "y2: " << y2 << std::endl;
    //    std::cout << "y3: " << y3 << std::endl << std::endl;
        
    /* at first sort the three vertices by y-coordinate ascending so v1 is the topmost vertice */
    Vertex vertices[3] =
    {
        Vertex { x1, y1, (uint32_t)(r1 << 16) + (g1 << 8) + b1 },
        Vertex { x2, y2, (uint32_t)(r2 << 16) + (g2 << 8) + b2 },
        Vertex { x3, y3, (uint32_t)(r3 << 16) + (g3 << 8) + b3 }
    };
    
    
    
    
    __gfx_sortVerticesByY__(vertices, 3);
    
    y1 = vertices[0].y;
    x1 = vertices[0].x;
    r1 = vertices[0].extra >> 16 & 0xff;
    g1 = vertices[0].extra >> 8 & 0xff;
    b1 = vertices[0].extra & 0xff;
    
    y2 = vertices[1].y;
    x2 = vertices[1].x;
    r2 = vertices[1].extra >> 16 & 0xff;
    g2 = vertices[1].extra >> 8 & 0xff;
    b2 = vertices[1].extra & 0xff;
    
    y3 = vertices[2].y;
    x3 = vertices[2].x;
    r3 = vertices[2].extra >> 16 & 0xff;
    g3 = vertices[2].extra >> 8 & 0xff;
    b3 = vertices[2].extra & 0xff;
    
    //    delete vertices;
    
    /* here we know that v1.y <= v2.y <= v3.y */
    /* check for trivial case of bottom-flat triangle */
    if (y2 == y3)
    {
        __gfx_fillBottomFlatTriangle__(pixels,
                               r1, g1, b1,
                               r2, g2, b2,
                               r3, g3, b3,
                               0xff, 0xff, 0xff,
                               x1, y1,
                               x2, y2,
                               x3, y3);
    }
    /* check for trivial case of top-flat triangle */
    else if (y1 == y2)
    {
        __gfx_fillTopFlatTriangle__(pixels,
                            r1, g1, b1,
                            r2, g2, b2,
                            r3, g3, b3,
                            0xff, 0xff, 0xff,
                            x1, y1,
                            x2, y2,
                            x3, y3);
        
    }
    else
    {
        /* general case - split the triangle in a topflat and bottom-flat one */
//        Vertice v4 = new Vertice(
//          (int)(vt1.x + ((float)(vt2.y - vt1.y) / (float)(vt3.y - vt1.y)) * (vt3.x - vt1.x)), vt2.y);
        float x4 = (int)(x1 + ((float)(y2 - y1) / (float)(y3 - y1)) * (x3 - x1));
        float y4 = y2;
        
        float w1 = ((y2 - y3) * (x4 - x3) + (x3 - x2) * (y4 - y3))
            / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));

        float w2 = ((y3 - y1) * (x4 - x3) + (x1 - x3) * (y4 - y3))
            / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3)) ;

        if(w2 < 0)
            w2 = 0;
        if(w2 > 1)
            w2 = 1;
        if(w1 < 0)
            w1 = 0;
        if(w1 > 1)
            w1 = 1;

        float w3 = 1 - w1 - w2;

        int r4 = w1 * r1 + w2 * r2 + w3 * r3;
        int g4 = w1 * g1 + w2 * g2 + w3 * g3;
        int b4 = w1 * b1 + w2 * b2 + w3 * b3;
        
        
        __gfx_fillBottomFlatTriangle__(pixels,
                               r1, g1, b1,
                               r2, g2, b2,
                               r4, g4, b4,
                               0xff, 0xff, 0xff,
                               x1, y1,
                               x2, y2,
                               x4, y4);
        
        __gfx_fillTopFlatTriangle__(pixels,
                            r2, g2, b2,
                            r4, g4, b4,
                            r3, g3, b3,
                            0xff, 0xff, 0xff,
                            x2, y2,
                            x4, y4,
                            x3, y3);
        
//        std::cout << "x1: " << x1 << '\n';
//        std::cout << "y1: " << y1 << '\n';
//        std::cout << "x2: " << x2 << '\n';
//        std::cout << "y2: " << y2 << '\n';
//        std::cout << "x3: " << x3 << '\n';
//        std::cout << "y3: " << y3 << '\n';
//        std::cout << "x4: " << x4 << '\n';
//        std::cout << "y4: " << y4 << '\n';
        
//        drawLine(pixels, 0xff0000ff, x1, y1, x2, y2);
//        drawLine(pixels, 0x0000ffff, x2, y2, x3, y3);
//        drawLine(pixels, 0x00ff00ff, x3, y3, x1, y1);
//        drawLine(pixels, 0x000000ff, x2, y2, x4, y4);
        
    }
}

void drawTriangle(uint32_t* pixels, uint32_t color, Vertex v1, Vertex v2, Vertex v3)
{
    __gfx_drawTriangle__(pixels, color, v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
}

void __gfx_drawTriangleOutline__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3)
{
    __gfx_drawLine__(pixels, color, x1, y1, x2, y2);
    __gfx_drawLine__(pixels, color, x2, y2, x3, y3);
    __gfx_drawLine__(pixels, color, x3, y3, x1, y1);
}

void __gfx_drawTriangleOutlineAdd__(uint32_t* pixels, uint32_t color, int x1, int y1, int x2, int y2, int x3, int y3)
{
    __gfx_drawLineAdd__(pixels, color, x1, y1, x2, y2);
    __gfx_drawLineAdd__(pixels, color, x2, y2, x3, y3);
    __gfx_drawLineAdd__(pixels, color, x3, y3, x1, y1);
}

void __gfx_fillRectangle__(uint32_t* pixels, uint32_t color, int x, int y, int w, int h)
{
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            pixels[(i + x) + (j + y) * gfx_WIDTH] = color;
        }
    }
}
void __gfx_fillRectangleAdd__(uint32_t* pixels, uint32_t color, int x, int y, int w, int h)
{
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            pixels[(i + x) + (j + y) * gfx_WIDTH] = color;
        }
    }
}
void __gfx_drawRectangle__(uint32_t* pixels, uint32_t color, int x, int y, int w, int h)
{
    for(int i = 0; i < w; i++)
        pixels[(i + x) + y * gfx_WIDTH] = color;
    
    for(int i = 0; i < w; i++)
        pixels[(i + x) + (y+h) * gfx_WIDTH] = color;
    
    for(int j = 0; j < h; j++)
        pixels[x + (j + y) * gfx_WIDTH] = color;
    
    for(int j = 0; j < h; j++)
        pixels[(x + w) + (j + y) * gfx_WIDTH] = color;
}

