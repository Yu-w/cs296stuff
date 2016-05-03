
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>

#include "GlobalConstants.hpp"
#include "Rock.hpp"
#include "MainAircraft.hpp"
#include <vector>

using namespace std;
using namespace sf;


int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.setMouseCursorVisible(false);

    sf::RectangleShape windowMask;
    windowMask.setFillColor(sf::Color::White);
    windowMask.setSize(sf::Vector2f(screenDimensions.x, screenDimensions.y));
    windowMask.setPosition(0, 0);
    
    sf::CircleShape circle(2);

//    sf::Font font;
//    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
//        return EXIT_FAILURE;
//    }
//    sf::Text text("Hello SFML", font, 50);
//    text.setColor(sf::Color::Black);

    sf::Texture rockTexture;
    if (!rockTexture.loadFromFile(resourcePath() + "rock.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite rockSprite;
    rockSprite.setTexture(rockTexture);
    
    sf::Texture mainAircraftTexture;
    if (!mainAircraftTexture.loadFromFile(resourcePath() + "main_aircraft.png")) {
        return EXIT_FAILURE;
    }
    
    MainAricraft mainAircraft;
    mainAircraft.setTexture(mainAircraftTexture);
    
    vector<Rock*> rockArr = vector<Rock*>();
    
    sf::Event::MouseMoveEvent mousePosition;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
        }
        if (rand() % 10 < 1) {
            Rock* rock = new Rock(rockSprite, rand() % screenDimensions.x, rand() % screenDimensions.x, 2 + rand() % 10);
            rockArr.push_back(rock);
            cout << rock->getObject().getTextureRect().left << " " << rock->getObject().getTextureRect().top << endl;
        }
        
        if (event.type == sf::Event::MouseMoved)
            mousePosition = event.mouseMove;

        window.clear();
        window.draw(windowMask);

        bool willExplode = false;
        mainAircraft.setPosition(mousePosition.x, mousePosition.y);
        
        cout << endl;
        for (auto rock : rockArr) {
            rock->proceed(frameRate.asSeconds());
            window.draw(rock->getObject());
            
            // Debug rock position as seen on the screen
            /*
            auto size = rock->getSize();
            size.x /= 2;
            size.y /= 2;
            auto rotatedSize = size;
            auto angle = rock->getObject().getRotation() / 90 * M_PI_2;
            rotatedSize.x = size.x * cos(angle) - size.y * sin(angle);
            rotatedSize.y = size.x * sin(angle) + size.y * cos(angle);
            
            auto rockPosition = rock->getPosition() + rotatedSize;
            circle.setPosition(rockPosition);
            */
            
            if (mainAircraft.checkCollision(rock)) {
                mainAircraft.explode();
                window.draw(mainAircraft);
                willExplode = true;
            }
        }
        cout << endl;
        
        if (!willExplode) {
            window.draw(mainAircraft);
        }
        
        // Update the window
        window.display();
        
        if (mainAircraft.exploded) {
            while(1);
        }
        
        sleep(frameRate);
    }

    return EXIT_SUCCESS;
}
