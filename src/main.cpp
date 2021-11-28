#include <SFML/Graphics.hpp>
#include <list>
#include "asteroid/asteroid.h"
#include "spaceship/spaceship.h"

int main() {

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = (SCREEN_WIDTH * 9) / 16;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My window");

    // Initialize the game random seed
    // use current time as seed for random generator
    std::srand(std::time(nullptr));

    Asteroid asteroid{};
    Spaceship spaceship{};

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
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // Aggiorna stato
        const sf::Time time_elapsed = clock.restart();
        asteroid.update(time_elapsed);
        asteroid.draw(window);

        spaceship.update(time_elapsed);
        spaceship.draw(window);

        // end the current frame
        window.display();
    }

    return 0;
}