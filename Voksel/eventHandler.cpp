//
//  eventHandler.cpp
//  Voxen
//
//  Created by Marat Isaw on 20.04.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "eventHandler.hpp"

#include <iostream>


EventHandler::EventHandler():mouseX(0),mouseY(0),keys(nullptr) {
    keys = (uint8_t*)SDL_GetKeyboardState(nullptr);
}

EventHandler& EventHandler::GetInstance() {
    static EventHandler instance;
    
    return instance;
}

EventHandler::~EventHandler() {
    
}

void EventHandler::Update() {
    memcpy(prevKeys, keys, 284 * sizeof(uint8_t));

    mouseXRel = 0;
    mouseYRel = 0;
    
    for(int i = 0; (i < 16) && SDL_PollEvent(&event); i++) {
        eventType[i] = event.type;

        if (event.type == SDL_MOUSEMOTION) {
            mouseXRel = event.motion.xrel;
            mouseYRel = event.motion.yrel;
        }
    }
    
    keys = (uint8_t*)SDL_GetKeyboardState(nullptr);
    
    isLeftMouseDown = SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT);
    isRightMouseDown = SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT);
    isMiddleMouseDown = SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_MIDDLE);
}

bool EventHandler::IsKeyDown(int key) {
    SDL_PumpEvents();
    memcpy(prevKeys, keys, 284 * sizeof(uint8_t));
    keys = (uint8_t*)SDL_GetKeyboardState(nullptr);
    
    return (keys[key]);
}

bool EventHandler::IsKeyUp(int key) {
    SDL_PumpEvents();
    memcpy(prevKeys, keys, 284 * sizeof(uint8_t));
    keys = (uint8_t*)SDL_GetKeyboardState(nullptr);
    
    return !(keys[key]);
}

bool EventHandler::IsKeyPressed(int key) {
    SDL_PumpEvents();
    memcpy(prevKeys, keys, 284 * sizeof(uint8_t));
    keys = (uint8_t*)SDL_GetKeyboardState(nullptr);
    
    return (!prevKeys[key] && keys[key]);
}


bool EventHandler::IsEvent(uint32_t eventType) {
    for (int i = 0; i < 16; i++) {
        if(this->eventType[i] == eventType)
            return true;
    }
    
    return false;
}
