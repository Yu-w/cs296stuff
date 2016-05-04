
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
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "GlobalConstants.hpp"
#include "Rock.hpp"
#include "MainAircraft.hpp"

using namespace std;
using namespace sf;

#include <boost/bind.hpp>
#include <boost/coroutine/coroutine.hpp>

// The coroutine type.
typedef boost::coroutines::asymmetric_coroutine<int> coro;

// The implementation routine of the coroutine.
void xrange_impl(coro::push_type& yield, int limit)
{
    for(int i = 0; i < limit; i++) {
        yield(i); // return results back to the caller
    }
}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Oriental");

    sf::Clock clock;

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
    
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(resourcePath() + "background.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    

    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Score: 0", font, 50);
    text.setColor(sf::Color::Black);

    sf::Texture rockTexture;
    if (!rockTexture.loadFromFile(resourcePath() + "rock.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite rockSprite;
    rockSprite.setTexture(rockTexture);
    
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile(resourcePath() + "enemy_aircraft.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite enemySprite;
    enemySprite.setTexture(enemyTexture);
    
    sf::Texture mainAircraftTexture;
    if (!mainAircraftTexture.loadFromFile(resourcePath() + "main_aircraft.png")) {
        return EXIT_FAILURE;
    }
    
    MainAricraft mainAircraft;
    mainAircraft.setTexture(mainAircraftTexture);
    
    vector<shared_ptr<Rock>> rockArr = vector<shared_ptr<Rock>>();
    
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "main_music.ogg"))
        return -1; // error
    music.play();
    
    sf::Event::MouseMoveEvent mousePosition;
    sf::Time deltaSeconds;
    
    int score = 0;
    int frameCounter = 0;
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
            unique_ptr<Rock> rock;
            if (rand() % 3 < 1)
                rockArr.push_back(shared_ptr<Rock>(
                            new Rock(
                                enemySprite,
                                rand() % screenDimensions.x,
                                rand() % screenDimensions.x,
                                1 + rand() % 8,
                                false)));
            else
                rockArr.push_back(shared_ptr<Rock>(
                            new Rock(
                                rockSprite,
                                rand() % screenDimensions.x,
                                rand() % screenDimensions.x,
                                3 + rand() % 10)));
        }
        
        if (event.type == sf::Event::MouseMoved)
            mousePosition = event.mouseMove;

        window.clear();
        window.draw(windowMask);
        window.draw(backgroundSprite);

        bool willExplode = false;
        mainAircraft.setPosition(mousePosition.x, mousePosition.y);
        
        for (auto& rock : rockArr) {
            rock->proceed(deltaSeconds.asSeconds());
            window.draw(rock->getObject());
            
            if (mainAircraft.checkCollision(*rock)) {
                mainAircraft.explode();
                window.draw(mainAircraft);
                willExplode = true;
            }
        }
        
        if (!willExplode) {
            window.draw(mainAircraft);
        }
        
        if (frameCounter <= fps / 2)
            backgroundSprite.setColor(sf::Color(255, 255, 255, 255 * frameCounter / (fps / 2)));
        else
            backgroundSprite.setColor(sf::Color(255, 255, 255, 255 * (1 - frameCounter / (fps / 2))));
        
        if (++frameCounter > fps) {
            backgroundSprite.scale(-1.f,1.f);
            if (backgroundSprite.getScale().x != 1)
                backgroundSprite.setPosition(screenDimensions.x, 0);
            else
                backgroundSprite.setPosition(0, 0);
            frameCounter = 0;
            
            score++;
            text.setString("Score: " + to_string(score));
        }

        window.draw(text);
        // Update the window
        window.display();
        
        if (mainAircraft.exploded) {
            while(1);
        }
        
        auto pend = remove_if(rockArr.begin(), rockArr.end(), [&window](shared_ptr<Rock>& rock) {
            if (rock->getPosition().y > window.getSize().y + 10)
                return true;
            else
                return false;
        });
        rockArr.resize(distance(rockArr.begin(), pend));
        
        deltaSeconds = clock.restart();
        sleep(frameRate - deltaSeconds);
    }

    return EXIT_SUCCESS;
}
