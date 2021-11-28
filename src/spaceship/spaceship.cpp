#include <cmath>
#include "spaceship.h"

const CustomTexture Spaceship::texture{ "images/spaceship.png" };

Spaceship::Spaceship() :
	speed{ 0.0f, 0.0f },
	accelleration_step { 80 },
	rotation_step{ 180 },
	friction_coefficent{ 0.35f }
{
	sprite.setTexture(texture);
	sprite.setPosition(512.0f, 288.0f);
	sprite.setOrigin(50, 74);
	sprite.setScale(0.5f, 0.5f);
	sprite.setRotation(0);
}

void Spaceship::update(sf::Time t1)
{
	static const float DEG_RAD_SCALE_FACTOR = (3.1415f / 180);
	const bool is_down_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	const bool is_up_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

	speed = speed - (speed * 0.35f * t1.asSeconds());

	if (is_up_pressed || is_down_pressed)
	{
		const float current_direction = (sprite.getRotation() * DEG_RAD_SCALE_FACTOR);
		const sf::Vector2f acceleration_versor{ std::sin(current_direction), -std::cos(current_direction) };
		const sf::Vector2f acceleration = acceleration_versor * accelleration_step;
		const sf::Vector2f speed_delta = t1.asSeconds() * acceleration;
		
		if (is_up_pressed)
		{
			speed = speed + speed_delta;
		}
		if (is_down_pressed)
		{
			speed = speed - speed_delta;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sprite.rotate(-rotation_step * t1.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sprite.rotate(rotation_step * t1.asSeconds());
	}
	
	sprite.move(speed * t1.asSeconds());
}

void Spaceship::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}
