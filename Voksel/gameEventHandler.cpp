//
//  gameEventHandler.cpp
//  Voksel
//
//  Created by Marat Isaw on 07.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "gameEventHandler.hpp"
#include "util.hpp"
#include "gameSettings.hpp"
#include "game.hpp"
#include <cstdlib>

void GameEventHandler::ProcessInput(Game& game, Player& player, const EventHandler& eh, float elapsedTime) {
    mousePrevious = mouseCurrent;
    mouseCurrent.x = eh.GetMouseX();
    mouseCurrent.y = eh.GetMouseY();

    player.jetForce.x = 0;
    player.jetForce.y = 0;

    player.angularAcceleration.y = 0;
    
    if(eh.IsKeyDown(SDL_SCANCODE_UP)) {
        player.jetForce.x = 90000 + player.velocity.y * player.velocity.y;
        player.jetForce.y = 90000 + player.velocity.y * player.velocity.y;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_DOWN)) {
        player.jetForce.x = -(90000/1.5f + player.velocity.y * player.velocity.y);
        player.jetForce.y = -(90000/1.5f + player.velocity.y * player.velocity.y);
    }

    if(eh.IsKeyDown(SDL_SCANCODE_LEFT)) {
        player.angularAcceleration.y = -util::DegInRad(350);
    }
    if(eh.IsKeyDown(SDL_SCANCODE_RIGHT)) {
        player.angularAcceleration.y = util::DegInRad(350);
    }

    
    player.acceleration.z = 0;
    if(eh.IsKeyDown(SDL_SCANCODE_SPACE)) {
        player.acceleration.z = 500;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_LSHIFT)) {
        player.acceleration.z = -500;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_Z)) {
        player.staticPitch -= 10;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_X)) {
        player.staticPitch += 10;
    }
    
    if(eh.IsKeyPressed(SDL_SCANCODE_0)) {
        game.LoadMap(Settings::resPath + "mapp.dat", true);
        game.SkyColor = {0x6E,0xBE,0xFC};
    }
    if(eh.IsKeyPressed(SDL_SCANCODE_1)) {
        game.LoadMap(Settings::resPath + "1", false);
        game.SkyColor = {0x6E,0xBE,0xFC};
    }
    if(eh.IsKeyPressed(SDL_SCANCODE_2)) {
        game.LoadMap(Settings::resPath + "2", false);
        game.SkyColor = {0x77,0xDD,0xE8};
    }
    if(eh.IsKeyPressed(SDL_SCANCODE_3)) {
        game.LoadMap(Settings::resPath + "3", false);
        game.SkyColor = {0xBE,0xDE,0xFF};
    }
    if(eh.IsKeyPressed(SDL_SCANCODE_4)) {
        game.LoadMap(Settings::resPath + "4", false);
        game.SkyColor = {0xDC,0xD8,0xaD};
    }
    if(eh.IsKeyPressed(SDL_SCANCODE_5)) {
        game.LoadMap(Settings::resPath + "5", false);
        game.SkyColor = {0xB5,0x30,0x26};
    }
    if(eh.IsKeyPressed(SDL_SCANCODE_6)) {
        game.LoadMap(Settings::resPath + "6", false);
        game.SkyColor = {0x6E,0xBE,0xFC};
    }
    
    if(eh.IsKeyPressed(SDL_SCANCODE_Q)) {
        if(game.minimapZoomLevel < 8)
            game.minimapZoomLevel++;
    }
    if(eh.IsKeyPressed(SDL_SCANCODE_E)) {
        if(game.minimapZoomLevel > 1)
            game.minimapZoomLevel--;
    }
    
    if(eh.IsKeyDown(SDL_SCANCODE_W)) {
        if(Settings::renderDistance < 3000)
            Settings::renderDistance += 10;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_S)) {
        if(Settings::renderDistance > 10)
            Settings::renderDistance -= 10;
    }
    
    static uint8_t r = 0;
    static uint8_t g = 0;
    static uint8_t b = 0;
    if(eh.IsKeyDown(SDL_SCANCODE_R)) {
        game.SkyColor = {r,g,b};
        r += 10;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_G)) {
        game.SkyColor = {r,g,b};
        g += 10;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_B)) {
        game.SkyColor = {r,g,b};
        b += 10;
    }

}
