//
//  Rock.hpp
//  cs296_demo_project
//
//  Created by Wang Yu on 5/2/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#ifndef Rock_hpp
#define Rock_hpp

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "GlobalConstants.hpp"
#include <cmath>

using namespace sf;

class Rock {
    
private:
    
    const Vector2f size = Vector2f(44, 44);
    float currentDuration;
    float existenceDuration;
    Sprite object;
    Vector2f initialPosition;
    Vector2f currentPosition;
    Vector2f finalPosition;
    int rotationRate;
    
public:
    
    Rock(Sprite object, int initX, int destX, float duration);
    Vector2f getCurrentPosition();
    Sprite getObject();
    Vector2f setObjectPosition(Vector2f position);
    Vector2f proceed(float seconds);
    Vector2f getSize();
    Vector2f getPosition();
    Rock* getPointer() {
        return this;
    }
    
};

#endif /* Rock_hpp */
