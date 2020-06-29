//
//  eventHandler.hpp
//  Voxen
//
//  Created by Marat Isaw on 20.04.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <SDL2/SDL.h>

// EventHandler is using Singleton pattern
class EventHandler {
public:
    
    static EventHandler& GetInstance();
    
    void Update();
    
    bool IsKeyDown(int key);
    bool IsKeyUp(int key);
    bool IsKeyPressed(int key);
    inline int GetMouseX() {
        return mouseX;
    }
    inline int GetMouseY() {
        return mouseY;
    }
    inline int GetMouseXRel() {
        return mouseXRel;
    }
    inline int GetMouseYRel() {
        return mouseYRel;
    }
    inline bool IsLeftMouseDown() {
        return isLeftMouseDown;
    }
    inline bool IsRightMouseDown() {
        return isRightMouseDown;
    }
    //bool IsMiddleMouseDown();
    bool IsEvent(uint32_t eventType);
    
    ~EventHandler();

    SDL_Event event;

private:
    EventHandler();
    EventHandler(EventHandler const&);   // Don't Implement
    void operator=(EventHandler const&); // Don't implement
    
    // input fields
    uint8_t prevKeys[284] { 0 };
    uint8_t* keys;
    int mouseX;
    int mouseY;
    int mouseXRel;
    int mouseYRel;
    int isLeftMouseDown;
    int isRightMouseDown;
    int isMiddleMouseDown;
    uint32_t eventType[16];
};


#endif /* EVENTHANDLER_HPP */
