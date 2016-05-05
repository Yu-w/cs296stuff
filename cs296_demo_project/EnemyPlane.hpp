//
//  EnemyPlane.hpp
//  cs296_demo_project
//
//  Created by Yifei Teng on 5/4/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#ifndef EnemyPlane_h
#define EnemyPlane_h

#include <iostream>
#include "LinearFlying.hpp"
#include "Rotating.hpp"
#include "GlobalConstants.hpp"

class EnemyPlane : public virtual LinearFlying, public virtual Rotating {
public:
    
    EnemyPlane(sf::Sprite object, int initX, int destX, float duration)
    : LinearFlying(object, initX, destX, duration),
    Rotating(object),
    HasSprite(object)
    {
        auto degree = atan2(screenDimensions.y, destX - initX) * 360.0 / M_PI / 2 - 90;
        setFixedRotation(degree);
    }
    
    EnemyPlane(EnemyPlane& other)
    : LinearFlying(other),
    Rotating(other),
    HasSprite(other) {
        
    }
    
    virtual sf::Vector2f proceed(float seconds) {
        auto pos = LinearFlying::proceed(seconds);
        Rotating::proceed(seconds);
        return pos;
    }
    
    ~EnemyPlane() {
        
    }
};

#endif /* EnemyPlane_h */
