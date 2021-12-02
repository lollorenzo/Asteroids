#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <ctime>
#include "common/collision_manager.h"
#include "asteroid/asteroid_manager.h"
#include "spaceship/spaceship.h"


int main() {

    constexpr int SCREEN_WIDTH = 1024;
    constexpr int SCREEN_HEIGHT = (SCREEN_WIDTH * 9) / 16;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My window", sf::Style::Titlebar | sf::Style::Close);

    // Initialize the game random seed
    // use current time as seed for random generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    AsteroidManager asteroid_manager{window.getSize()};

    Spaceship spaceship{window.getSize()};

    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

            // "close requested" event: we close the window
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // Get time delta and reset the clock
        const sf::Time time_elapsed = clock.restart();

        // Aggiorna stato
        asteroid_manager.update(time_elapsed);
        spaceship.update(time_elapsed);

		asteroid_manager.draw(window);
        spaceship.draw(window);

        // Manage collisions between the spaceship and the asteroids
        CollisionManager::ManageCollision(spaceship, asteroid_manager.get_asteroids());

        // end the current frame
        window.display();
    }

    return 0;
}