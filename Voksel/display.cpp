//
//  display.cpp
//  Voksel
//
//  Created by Marat Isaw on 18.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "display.hpp"

#include <iostream>

Display::Display(int width, int height, const std::string& title) : width(width), height(height), title(title), eventHandler(EventHandler::GetInstance()) {
    if(!SDL_WasInit(SDL_INIT_EVERYTHING)) {
        isInit = false;
        return;
    }
    
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR32, SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    
    this->pixels = new uint32_t[width * height];
    memset(pixels, 0, width*height*sizeof(uint32_t));
    
//    int pitch = 0;
//    SDL_LockTexture(texture, nullptr, (void**)&this->pixels, &pitch);
    
    
    isClosed = false;
    isInit = true;
}

Display::~Display() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete[] pixels;
}


void Display::Update() {
    eventHandler.Update();
    
    
//    SDL_UnlockTexture(texture);

    SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
//    int pitch = 0;
//    SDL_LockTexture(texture, nullptr, (void**)&this->pixels, &pitch);

    if(eventHandler.IsEvent(SDL_QUIT)) {
        isClosed = true;
    }
}

void Display::Clear() {
    memset(this->pixels, 0, width * height * sizeof(uint32_t));
}
void Display::Clear(RGB color) {
    for (int i = 0; i < width*height; i++)
        pixels[i] = color.GetUint32();
}
void Display::Clear(RGBA color) {
    for (int i = 0; i < width*height; i++)
        pixels[i] = color.GetUint32();
}

void Display::Abort() {
    isClosed = true;
}
