//
//  MainAircraft.hpp
//  cs296_demo_project
//
//  Created by Wang Yu on 5/2/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#ifndef MainAircraft_hpp
#define MainAircraft_hpp

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "GlobalConstants.hpp"
#include "Rock.hpp"

using namespace sf;

class MainAricraft: public sf::Sprite {
    
private:
    
    Texture texture;
    const Vector2f size = Vector2f(32, 42);
    
public:
    
    bool exploded = false;
    
    MainAricraft();
    bool checkCollision(Rock::Rock* rock);
    void explode();
    Vector2f getSize();
};

#endif /* MainAircraft_hpp */
