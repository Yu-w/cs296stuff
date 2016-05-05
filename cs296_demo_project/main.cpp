
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
#include "EnemyPlane.hpp"
#include "MainAircraft.hpp"
#include "Bullet.hpp"

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
    
    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile(resourcePath() + "bullet.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite bulletSprite;
    bulletSprite.setTexture(bulletTexture);
    
    vector<shared_ptr<LinearFlying>> rockArr;
    vector<shared_ptr<LinearFlying>> bulletArr;
    
    sf::SoundBuffer gunSoundBuffer;
    if (!gunSoundBuffer.loadFromFile(resourcePath() + "gun_sound.ogg"))
        return -1;
    sf::Sound gunSound;
    gunSound.setBuffer(gunSoundBuffer);
    
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "main_music.ogg"))
        return -1; // error
    music.setLoop(true);
    music.play();
    
    sf::Event::MouseMoveEvent mousePosition;
    mousePosition.x = screenDimensions.x / 2 - mainAircraft.getSize().x / 2;
    mousePosition.y = screenDimensions.y - 200;
    sf::Time deltaSeconds;
    
    int score = 0;
    int frameCounter = 0;
    
    // Start the game loop
    while (window.isOpen())
    {
        bool makeBullet = false;
        
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
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                gunSound.play();
                makeBullet = true;
            }
        }
        
        if (rand() % 10 < 1) {
            if (rand() % 3 < 1)
                rockArr.push_back(shared_ptr<LinearFlying>(
                            new EnemyPlane(
                                enemySprite,
                                rand() % screenDimensions.x,
                                rand() % screenDimensions.x,
                                1 + rand() % 8)));
            else
                rockArr.push_back(shared_ptr<LinearFlying>(
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
        
        if (makeBullet)
            bulletArr.push_back(shared_ptr<LinearFlying>(
                         new Bullet(
                             bulletSprite,
                             mainAircraft.getPosition().x,
                             mainAircraft.getPosition().y,
                             mainAircraft.getPosition().x,
                             3)));
        
        for (auto& bullet : bulletArr) {
            bullet->proceed(deltaSeconds.asSeconds());
            bullet->setSize(Vector2f(9, 21));
            window.draw(bullet->getObject());
        }
        
        for (auto& rock : rockArr) {
            rock->proceed(deltaSeconds.asSeconds());
            window.draw(rock->getObject());
            
            for (auto& bullet : bulletArr) {
                if (rock->checkCollision(*bullet)) rock->goDie();
            }
            
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
        
        auto pend = remove_if(rockArr.begin(), rockArr.end(),
            [&window](shared_ptr<LinearFlying>& rock) {
                return (rock->shouldDisappear());});

        rockArr.resize(distance(rockArr.begin(), pend));
        
        auto bend = remove_if(bulletArr.begin(), bulletArr.end(),
                              [&window](shared_ptr<LinearFlying>& bullet) {
                                  return (bullet->shouldDisappear());});
        
        bulletArr.resize(distance(bulletArr.begin(), bend));
        
        deltaSeconds = clock.restart();
        sleep(frameRate - deltaSeconds);
    }

    return EXIT_SUCCESS;
}
