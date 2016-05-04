//
//  Bullet.hpp
//  cs296_demo_project
//
//  Created by Yifei Teng on 5/3/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h

#include "Rock.hpp"

class Bullet : public virtual LinearFlying {
    Bullet(sf::Sprite object, int initX, int destX, float duration) {
        Rock(object, initX, destX, duration, false);
        
    }
};

#endif /* Bullet_h */
