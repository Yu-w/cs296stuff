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
    float fixedDegree;
    bool fixed;

public:
    Rotating(sf::Sprite object)
        : HasSprite(object)
    {
        rotationRate = 0;
        fixedDegree = 0;
        fixed = false;
    }
    
    Rotating(Rotating &other)
    : HasSprite(other) {
        rotationRate = other.rotationRate;
    }
    
    void setFixedRotation(float degree) {
        fixed = true;
        fixedDegree = degree;
    }
    
    void setRandomRotation() {
        fixed = false;
        rotationRate = 20 + rand() % 60;
    }
    
    sf::Vector2f proceed(float seconds) {
        if (fixed) {
            object.setRotation(fixedDegree);
        } else {
            object.rotate(seconds * rotationRate);
        }
        return sf::Vector2f(0, 0);
    }
};

#endif /* Rotating_h */
