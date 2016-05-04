//
//  Header.h
//  cs296_demo_project
//
//  Created by Yifei Teng on 5/3/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#ifndef HasSprite_h
#define HasSprite_h

#include <SFML/Graphics.hpp>

class HasSprite {
protected:
    sf::Sprite object;
public:
    
    HasSprite(sf::Sprite object) {
        this->object = object;
    }
    
    HasSprite(HasSprite &other) {
        this->object = other.object;
    }
    
    ~HasSprite() {
        
    }
    
    sf::Sprite getObject() {
        return object;
    }
};

#endif /* HasSprite_h */
