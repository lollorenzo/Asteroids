#include <algorithm>
#include "asteroid_manager.h"

AsteroidManager::AsteroidManager(const sf::Vector2u& windows_size) :
	windows_size{windows_size},
	time_elapsed_acc{0.0f}
{
	// Create 4 random asteroids
	for (int i = 0; i < 5; ++i)
	{
		asteroids.emplace_back(windows_size);
	}
}

void AsteroidManager::update(const sf::Time& t1)
{
	// Update all existing asteroids
	auto update_asteroid = [&t1](Asteroid& a) { a.update(t1); };
	std::for_each(asteroids.begin(), asteroids.end(), update_asteroid);

	// Destroy destroyable asteroids
	auto remove_asteroids = [](Asteroid& a) { return !a.IsAlive(); };
	std::remove_if(asteroids.begin(), asteroids.end(), remove_asteroids);

	// Create new Asteroids
	time_elapsed_acc += t1.asSeconds();
	while (time_elapsed_acc > 1)
	{
		// I should create an asteroid per sec
		asteroids.emplace_back(windows_size);
		time_elapsed_acc -= 1;
	}
}

void AsteroidManager::draw(sf::RenderWindow& window) const
{
	auto draw_asteroid = [&window](const Asteroid& a) { a.draw(window); };
	std::for_each(asteroids.begin(), asteroids.end(), draw_asteroid);
}
