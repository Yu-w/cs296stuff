//
//  Rotating.hpp
//  cs296_demo_project
//
//  Created by Yifei Teng on 5/3/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#ifndef Rotating_h
#define Rotating_h

#include "GlobalConstants.hpp"
#include "HasSprite.hpp"

class Rotating : public virtual HasSprite {

protected:
    float rotationRate;

public:
    Rotating(sf::Sprite object)
        : HasSprite(object)
    {
        
    }
    
    void setRotation() {
        rotationRate = 15 + rand() % 60;
    }
    
    sf::Vector2f proceed(float seconds) {
        object.rotate(seconds * rotationRate);
        return sf::Vector2f(0, 0);
    }
};

#endif /* Rotating_h */
