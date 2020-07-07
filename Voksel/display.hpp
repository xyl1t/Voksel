//
//  display.hpp
//  Voksel
//
//  Created by Marat Isaw on 18.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SDL2/SDL.h>
#include <string>   
#include "eventHandler.hpp"
#include "color.hpp"

// A wraper for SDL_Window and some other stuff
class Display {
public:
    Display(int width, int height, const std::string& title);
    
    void Update();
    void Clear();
    void Clear(RGB color);
    void Clear(RGBA color);
    void Abort();
    
    inline void SetPixel(int x, int y, RGBA color) {
        this->pixels[x + y * this->width] = color.GetUint32();
    }
    inline void SetPixel(int x, int y, RGB color) {
        if(x >= 0 && y >= 0 && x < width && y < height)
            this->pixels[x + y * this->width] = color.GetUint32();
    }
    inline bool IsInit() const {
        return isInit;
    }
    inline int GetWidth() const  {
        return width;
    }
    inline int GetHeight() const  {
        return height;
    }
    inline const std::string& GetTile() const  {
        return title;
    }
    inline uint32_t* GetPixels() {
        return this->pixels;
    }
    inline bool IsClosed() const  {
        return isClosed;
    }
    inline SDL_Window* GetWindow() const  {
        return window;
    }
    inline EventHandler& GetEventHandler() const  {
        return eventHandler;
    }

    ~Display();
    
private:
    bool isInit;
    
    // window fields
    SDL_Window* window;
    int width;
    int height;
    const std::string title;
    bool isClosed;
    
    // gfx fields
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint32_t* pixels;
    
    // For event handeling
    EventHandler& eventHandler;
};


#endif /* DISPLAY_HPP */
