//
//  Rock.cpp
//  cs296_demo_project
//
//  Created by Wang Yu on 5/2/16.
//  Copyright © 2016 Yu Wang. All rights reserved.
//

#include "LinearFlying.hpp"

LinearFlying::LinearFlying(sf::Sprite object, int initX, int destX, float duration)
    : HasSprite(object)
{
    currentDuration = 0;
    existenceDuration = duration;
    initialPosition = sf::Vector2f(initX, -getSize().y);
    currentPosition = initialPosition;
    finalPosition = sf::Vector2f(destX, screenDimensions.y);
    setObjectPosition(currentPosition);
}

LinearFlying::LinearFlying(LinearFlying &other)
    : HasSprite(other)
{
    currentDuration = other.currentDuration;
    existenceDuration = other.existenceDuration;
    initialPosition = other.initialPosition;
    currentPosition = other.currentPosition;
    finalPosition = other.finalPosition;
}

LinearFlying::~LinearFlying() {
}

void LinearFlying::setSize(sf::Vector2f newSize) {
    size = newSize;
}

void LinearFlying::reverseDirection() {
    auto initTempPos = initialPosition;
    initialPosition = finalPosition;
    finalPosition = initTempPos;
}

void LinearFlying::setInitalYPosition(float y) {
    initialPosition.y = y;
}

sf::Vector2f LinearFlying::proceed(float seconds) {
    currentDuration += seconds;
    auto newX = initialPosition.x + (finalPosition.x - initialPosition.x) * (currentDuration / existenceDuration);
    auto newY = initialPosition.y + (finalPosition.y - initialPosition.y) * (currentDuration / existenceDuration);
    currentPosition = sf::Vector2f(newX, newY);
    setObjectPosition(currentPosition);
    return getCurrentPosition();
}

bool LinearFlying::checkCollision(LinearFlying& rock) {
    auto currentPosition = getPosition();
    currentPosition.x += getSize().x / 2;
    currentPosition.y += getSize().y / 2;
    auto size = rock.getSize();
    size.x /= 2;
    size.y /= 2;
    auto rotatedSize = size;
    auto angle = rock.getObject().getRotation() / 360 * M_PI * 2;
    rotatedSize.x = size.x * cos(angle) - size.y * sin(angle);
    rotatedSize.y = size.x * sin(angle) + size.y * cos(angle);
    
    auto rockPosition = rock.getPosition() + rotatedSize;
    auto delta = rockPosition - currentPosition;
    if (delta.x * delta.x + delta.y * delta.y < (size.x * size.x + size.y * size.y))
        return true;
    else return false;
}


sf::Vector2f LinearFlying::getCurrentPosition() {
    return currentPosition;
}

sf::Vector2f LinearFlying::setObjectPosition(sf::Vector2f position) {
    object.setPosition(position);
}

sf::Vector2f LinearFlying::getSize() {
    return size;
}

sf::Vector2f LinearFlying::getPosition() {
    return object.getPosition();
}
