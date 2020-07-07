//
//  gameEventHandler.cpp
//  Voksel
//
//  Created by Marat Isaw on 07.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "gameEventHandler.hpp"

void GameEventHandler::ProcessInput(Player& player, const EventHandler& eh, float elapsedTime) {
    mousePrevious = mouseCurrent;
    mouseCurrent.x = eh.GetMouseX();
    mouseCurrent.y = eh.GetMouseY();
    
    
    float cosAngle = cos(player.angularPosition.y);
    float sinAngle = sin(player.angularPosition.y);
    
    if(eh.IsKeyDown(SDL_SCANCODE_W)) {
        player.position.x += sinAngle * elapsedTime / 25.f;
        player.position.y += -cosAngle * elapsedTime / 25.f;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_S)) {
        player.position.x -= sinAngle * elapsedTime / 25.f;
        player.position.y -= -cosAngle * elapsedTime / 25.f;
    }

    if(eh.IsKeyDown(SDL_SCANCODE_A)) {
        player.angularPosition.y -= M_PI / 360.f * elapsedTime;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_D)) {
        player.angularPosition.y += M_PI / 360.f * elapsedTime;
    }

    
    if(eh.IsKeyDown(SDL_SCANCODE_SPACE)) {
        player.position.z += 3;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_LSHIFT)) {
        player.position.z -= 3;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_Q)) {
        player.angularPosition.x -= 10;
    }
    if(eh.IsKeyDown(SDL_SCANCODE_E)) {
        player.angularPosition.x += 10;
    }
}
