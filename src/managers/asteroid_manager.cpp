#include <algorithm>
#include "asteroid_manager.h"

AsteroidManager::AsteroidManager(const sf::Vector2u& windows_size, const AssetManager& asset_manager) :
	windows_size{ windows_size },
	asset_manager{ asset_manager },
	time_elapsed_acc{0.0f}
{
	// Create 4 random asteroids
	for (int i = 0; i < 5; ++i)
	{
		asteroids.emplace_back(windows_size, asset_manager);
	}
}

void AsteroidManager::update(const sf::Time& t1)
{
	// Update all existing asteroids
	for (auto& a : asteroids)
	{
		a.update(t1);
	}

	// Destroy destroyable asteroids
	static const auto remove_lambda = [](const Asteroid& a) { return !a.IsAlive(); };
	std::remove_if(asteroids.begin(), asteroids.end(), remove_lambda);

	// Create new Asteroids
	time_elapsed_acc += t1.asSeconds();
	while (time_elapsed_acc > 1)
	{
		// I should create an asteroid per sec
		asteroids.emplace_back(windows_size, asset_manager);
		time_elapsed_acc -= 1;
	}
}

void AsteroidManager::draw(sf::RenderWindow& window) const
{
	for (auto& a : asteroids)
	{
		a.draw(window);
	}
}
