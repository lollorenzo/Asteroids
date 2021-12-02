#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "common/collision_manager.h"
#include "asteroid/asteroid_manager.h"
#include "spaceship/spaceship.h"

int main() {

    constexpr int SCREEN_WIDTH = 1024;
    constexpr int SCREEN_HEIGHT = (SCREEN_WIDTH * 9) / 16;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My window", sf::Style::Titlebar | sf::Style::Close);

    // Initialize the game random seed
    // use current time as seed for random generator
    std::srand(std::time(nullptr));
    
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
		asteroid_manager.draw(window);

        spaceship.update(time_elapsed);
        spaceship.draw(window);

        //sf::Vector2f tmp{ spaceship.GetBoundingBox().width, spaceship.GetBoundingBox().height };
        //sf::RectangleShape rectangle(tmp);
        //rectangle.setPosition(spaceship.GetBoundingBox().left, spaceship.GetBoundingBox().top);
        //window.draw(rectangle);

        CollisionManager::ManageCollision(spaceship, asteroid_manager.get_asteroids());

        // end the current frame
        window.display();
    }

    return 0;
}