//
//  Rock.cpp
//  cs296_demo_project
//
//  Created by Wang Yu on 5/2/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#include "Rock.hpp"

Rock::Rock(sf::Sprite object, int initX, int destX, float duration, bool rototed) {
    this->object = object;
    currentDuration = 0;
    existenceDuration = duration;
    initialPosition = sf::Vector2f(initX, -getSize().y);
    currentPosition = initialPosition;
    finalPosition = sf::Vector2f(destX, screenDimensions.y);
    setObjectPosition(currentPosition);
    
    if (rototed)
        rotationRate = 15 + rand() % 60;
    else
        rotationRate = 0;
}

sf::Vector2f Rock::proceed(float seconds) {
    currentDuration += seconds;
    auto newX = initialPosition.x + (finalPosition.x - initialPosition.x) * (currentDuration / existenceDuration);
    auto newY = initialPosition.y + (finalPosition.y - initialPosition.y) * (currentDuration / existenceDuration);
    currentPosition = sf::Vector2f(newX, newY);
    setObjectPosition(currentPosition);
    object.rotate(frameRate.asSeconds() * rotationRate);
    return getCurrentPosition();
}


sf::Vector2f Rock::getCurrentPosition() {
    return currentPosition;
}

sf::Sprite Rock::getObject() {
    return object;
}

sf::Vector2f Rock::setObjectPosition(sf::Vector2f position) {
    object.setPosition(position);
}

sf::Vector2f Rock::getSize() {
    return size;
}

sf::Vector2f Rock::getPosition() {
    return object.getPosition();
}