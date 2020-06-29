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
    
    isClosed = false;
    
    
    
    isInit = true;
}

Display::~Display() {
//    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


void Display::Update() {
    eventHandler.Update();
    
    SDL_UnlockTexture(texture);
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    int pitch = 0;
    SDL_LockTexture(texture, nullptr, (void**)&this->pixels, &pitch);
    
    
    if(eventHandler.IsEvent(SDL_QUIT)) {
        isClosed = true;
    }
}

void Display::Clear() {
    memset(this->pixels, 0, width * height * sizeof(uint32_t));
}

void Display::Abort() {
    isClosed = true;
}

//// Setters
//void Display::SetPixel(int x, int y, uint32_t c) {
//    this->pixels[x + y * this->width] = c;
//}
//
//// Getters
//bool Display::IsInit() {
//    return isInit;
//}
//int Display::GetWidth() {
//    return width;
//}
//int Display::GetHeight() {
//    return height;
//}
//const std::string& Display::GetTile() {
//    return title;
//}
//uint32_t*& Display::GetPixels() {
//    return this->pixels;
//}
//bool Display::IsClosed() {
//    return isClosed;
//}