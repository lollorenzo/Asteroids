#pragma once

#include <list>
#include <SFML/System/Time.hpp>
#include "asteroid.h"

class AsteroidManager {
public:
	using container_type = std::list<Asteroid>;

	AsteroidManager(const sf::Vector2u& windows_size);
	container_type& get_asteroids() { return asteroids; }
	
	void update(const sf::Time& t1);
	void draw(sf::RenderWindow& window) const;
private:
	container_type asteroids;
	const sf::Vector2u windows_size;
	float time_elapsed_acc;
};