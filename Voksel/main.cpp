//
//  main.cpp
//  Voksel
//
//  Created by Marat Isaw on 16.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <SDL2/SDL.h>
#include "display.hpp"
#include "game.hpp"
#include "tensorMath.hpp"
using namespace tem;

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    
    Display display(800, 600, "Voksel");
    Game game(display);
    
    float currentTime = 0.f;
    float previousTime = 0.f;
    float delta = 0.f;
    int timer = 0;
    while(!display.IsClosed()) {

        currentTime = SDL_GetTicks();
        delta = currentTime - previousTime;
        previousTime = currentTime;
        if(currentTime / 1000 > timer) {
            std::clog << "FPS: " << 1000.f / delta  << std::endl;
            timer++;
        }

        game.Update(delta);
        game.Render();
        
    }
    
    SDL_Quit();
    
    return 0;
}
