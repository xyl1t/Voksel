//
//  eventHandler.cpp
//  Voxen
//
//  Created by Marat Isaw on 20.04.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "eventHandler.hpp"

#include <iostream>
#include <cstring>


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
    mouseXRel = 0;
    mouseYRel = 0;
    
    for(int i = 0; i < SDL_NUM_SCANCODES; i++) {
        prevKeys[i] = keys[i];
    }
    for(int i = 0; (i < 16) && SDL_PollEvent(&event); i++) {
        eventType[i] = event.type;

        if (event.type == SDL_MOUSEMOTION) {
            mouseXRel = event.motion.xrel;
            mouseYRel = event.motion.yrel;
        }
    }
    
    isLeftMouseDown = SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT);
    isRightMouseDown = SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT);
    isMiddleMouseDown = SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_MIDDLE);
}

bool EventHandler::IsKeyDown(int key) const {
    return (keys[key]);
}

bool EventHandler::IsKeyUp(int key) const {
    return !(keys[key]);
}

bool EventHandler::IsKeyPressed(int key) const {
    return (!(bool)prevKeys[key] && (bool)keys[key]);
}


bool EventHandler::IsEvent(uint32_t eventType) const {
    for (int i = 0; i < 16; i++) {
        if(this->eventType[i] == eventType)
            return true;
    }
    
    return false;
}
