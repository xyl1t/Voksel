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
    
//    mat3x3 mat = mat3x3(1.0f);
//
//    mat.rotate(M_PI / 2);
//
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            std::cout << mat[i + j * 3] << " ";
//        }
//        std::cout << std::endl;
//    }
//
    
    SDL_Init(SDL_INIT_EVERYTHING);

    Display display(800, 600, "Voksel");
    Game game(display, { 300, 200, 150.f }, 1000);

    while(!display.IsClosed()) {

        game.Update();

    }

    SDL_Quit();
    
    return 0;
}
