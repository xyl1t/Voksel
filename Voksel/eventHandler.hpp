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
    
    bool IsKeyDown(int key) const;
    bool IsKeyUp(int key) const;
    bool IsKeyPressed(int key) const;
    inline int GetMouseX() const {
        return mouseX;
    }
    inline int GetMouseY() const {
        return mouseY;
    }
    inline int GetMouseXRel() const {
        return mouseXRel;
    }
    inline int GetMouseYRel() const {
        return mouseYRel;
    }
    inline bool IsLeftMouseDown() const {
        return isLeftMouseDown;
    }
    inline bool IsRightMouseDown() const {
        return isRightMouseDown;
    }
    //bool IsMiddleMouseDown();
    bool IsEvent(uint32_t eventType) const;
    
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
