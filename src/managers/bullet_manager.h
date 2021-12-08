#pragma once

#include <list>
#include <SFML/System/Time.hpp>
#include "entities/bullet.h"

class BulletManager {
public:
	using container_type = std::list<Bullet>;

	BulletManager();
	container_type& get_bullets() { return bullets; }
	
	const Bullet& create_bullet(const sf::Vector2f& position, float rotation);
	void update(const sf::Time& t1);
	void draw(sf::RenderWindow& window) const;
private:
	container_type bullets;
	const sf::Vector2u windows_size;
	float time_elapsed_acc;
};