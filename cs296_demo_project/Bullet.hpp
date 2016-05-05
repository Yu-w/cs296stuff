//
//  Bullet.hpp
//  cs296_demo_project
//
//  Created by Yifei Teng on 5/3/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h

#include <iostream>
#include "LinearFlying.hpp"
#include "GlobalConstants.hpp"

class Bullet : public virtual LinearFlying {
    
public:
    
    Bullet(sf::Sprite object, int initX, float y, int destX, float duration)
    : LinearFlying(object, initX, destX, duration),
      HasSprite(object)
    {
        reverseDirection();
        setInitialYPosition(y);
        setInitialXPosition(getPosition().x + 12);
    }
    
    Bullet(Bullet& other)
    : LinearFlying(other),
      HasSprite(other) {
        
    }
    
    virtual sf::Vector2f proceed(float seconds) {
        auto pos = LinearFlying::proceed(seconds);
        if (pos.y <= 0) goDie();
        return pos;
    }
    
    ~Bullet() {
        
    }

    
};

#endif /* Bullet_h */
