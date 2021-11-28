#include <cstdlib>
#include <ctime>
#include "asteroid.h"

const CustomTexture Asteroid::texture{ "./images/asteroid.png" };

// Initialize asteroid with random speed and rot_speed
Asteroid::Asteroid()
{
	x_speed = ((static_cast<float>(std::rand()) / RAND_MAX) * (100));
	y_speed = ((static_cast<float>(std::rand()) / RAND_MAX) * (100));
	rot_speed = ((static_cast<float>(std::rand()) / RAND_MAX) * (2));
	const float scale = 0.2f + ((static_cast<float>(std::rand()) / RAND_MAX) * (0.8f));

	sprite.setTexture(texture);
	sprite.setPosition(0.0f, 0.0f);
	sprite.setRotation(0.0f);
	sprite.setScale(scale, scale);
	sprite.setOrigin(40, 38);
}

void Asteroid::update(sf::Time t1)
{
	// Update position using speed slong x and y
	const float delta_time_in_sec = t1.asSeconds();
	const float delta_x = (delta_time_in_sec * x_speed);
	const float delta_y = (delta_time_in_sec * y_speed);
	sprite.move(delta_x, delta_y);

	// update angle using rot_speed
	static const float RAD_DEG_SCALE_FACTOR = (180 / 3.1415f);
	const float delta_angle = (delta_time_in_sec * rot_speed) * RAD_DEG_SCALE_FACTOR;
	sprite.rotate(delta_angle);
}

void Asteroid::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}
