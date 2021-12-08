#pragma once

#include <list>
#include <SFML/System/Time.hpp>
#include "entities/asteroid.h"
#include "asset_manager.h"

class AsteroidManager {
public:
	using container_type = std::list<Asteroid>;

	AsteroidManager(const sf::Vector2u& windows_size, const AssetManager& asset_manager);
	container_type& get_asteroids() { return asteroids; }
	
	void update(const sf::Time& t1);
	void draw(sf::RenderWindow& window) const;
private:
	container_type asteroids;
	const sf::Vector2u windows_size;
	const AssetManager& asset_manager;
	float time_elapsed_acc;
};