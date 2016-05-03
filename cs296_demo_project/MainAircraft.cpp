//
//  MainAircraft.cpp
//  cs296_demo_project
//
//  Created by Wang Yu on 5/2/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#include "MainAircraft.hpp"
#include <iostream>

MainAricraft::MainAricraft() {
    if (!texture.loadFromFile(resourcePath() + "main_aircraft.png")) {
        return EXIT_FAILURE;
    }
    this->setTexture(texture);
}

bool MainAricraft::checkCollision(Rock::Rock* rock) {
    auto currentPosition = getPosition();
    currentPosition.x += getSize().x / 2;
    currentPosition.y += getSize().y / 2;
    auto size = rock->getSize();
    size.x /= 2;
    size.y /= 2;
    auto rotatedSize = size;
    auto sizeR = sqrt(size.x * size.x + size.y * size.y);
    auto sizeTheta = atan2(size.y, size.x);
    
    auto rockPosition = rock->getPosition() + size;
    auto delta = rockPosition - currentPosition;
    std::cout << delta.x * delta.x + delta.y * delta.y << " ";
    std::cout << size.x * size.x + size.y * size.y << " ";
    if (delta.x * delta.x + delta.y * delta.y < (size.x * size.x + size.y * size.y))
        return true;
    else return false;
}

void MainAricraft::explode() {
    this->exploded = true;
    if (!texture.loadFromFile(resourcePath() + "explosion_3.png")) {
        return EXIT_FAILURE;
    }
    setTexture(texture);
}

sf::Vector2f MainAricraft::getSize() {
    return size;
}