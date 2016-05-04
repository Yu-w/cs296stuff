//
//  Rock.hpp
//  cs296_demo_project
//
//  Created by Yifei Teng on 5/3/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#ifndef Rock_h
#define Rock_h

#include "LinearFlying.hpp"
#include "Rotating.hpp"

class Rock : public virtual LinearFlying, public virtual Rotating {
public:

    Rock(sf::Sprite object, int initX, int destX, float duration)
    : LinearFlying(object, initX, destX, duration),
      Rotating(object),
      HasSprite(object)
    {
        
    }
    
    Rock(Rock& other)
    : LinearFlying(other),
      Rotating(other),
      HasSprite(other) {
        
    }
    
    sf::Vector2f proceed(float seconds) {
        auto pos = LinearFlying::proceed(seconds);
        Rotating::proceed(seconds);
        return pos;
    }
    
    ~Rock() {
        
    }
};

#endif /* Rock_h */
