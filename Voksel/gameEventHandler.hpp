//
//  gameEventHandler.hpp
//  Voksel
//
//  Created by Marat Isaw on 07.07.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef gameEventHandler_hpp
#define gameEventHandler_hpp
#include "eventHandler.hpp"
#include "player.hpp"
#include "tensorMath.hpp"
using namespace tem;

class GameEventHandler {
public:
    void ProcessInput(Player& player, const EventHandler& eh, float elapsedTime);

private:
    vec2 mousePrevious;
    vec2 mouseCurrent;
};

#endif /* gameEventHandler_hpp */
