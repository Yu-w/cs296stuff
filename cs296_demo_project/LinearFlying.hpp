//
//  Rock.hpp
//  cs296_demo_project
//
//  Created by Wang Yu on 5/2/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#ifndef LinearFlying_hpp
#define LinearFlying_hpp

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "GlobalConstants.hpp"
#include "HasSprite.hpp"
#include <cmath>

class LinearFlying : public virtual HasSprite {
    
private:
    
    const sf::Vector2f size = sf::Vector2f(44, 44);
    float currentDuration;
    float existenceDuration;

    sf::Vector2f initialPosition;
    sf::Vector2f currentPosition;
    sf::Vector2f finalPosition;

public:
    
    LinearFlying(sf::Sprite object, int initX, int destX, float duration);
    LinearFlying(LinearFlying &other);
    ~LinearFlying();

    sf::Vector2f getCurrentPosition();
    
    sf::Vector2f setObjectPosition(sf::Vector2f position);
    sf::Vector2f proceed(float seconds);
    sf::Vector2f getSize();
    sf::Vector2f getPosition();
};

#endif /* LinearFlying_hpp */
