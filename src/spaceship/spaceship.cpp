#include <cmath>
#include "spaceship.h"

const CustomTexture Spaceship::texture{ "images/spaceship.png" };

Spaceship::Spaceship(const sf::Vector2u& window_size) :
	GameEntity{},
	speed{ 0.0f, 0.0f },
	accelleration_step { 80.0f },
	rotation_step{ 180.0f },
	friction_coefficent{ 0.70f },
	brake_coefficent{ 0.85f },
	health_bar{ 100, 10 }
{
	sprite.setTexture(texture);
	sprite.setPosition(window_size.x / 2.0f, window_size.y / 2.0f);

	const sf::Vector2u texture_size = texture.getSize();
	sprite.setOrigin(texture_size.x / 2.0f, texture_size.y / 2.0f);
	sprite.setScale(0.5f, 0.5f);
	sprite.setRotation(0);
}

void Spaceship::update(const sf::Time& t1)
{
	update_motion(t1);
}

void Spaceship::update_motion(const sf::Time& t1)
{
	static const float DEG_RAD_SCALE_FACTOR = (3.1415f / 180);
	const bool is_down_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	const bool is_up_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

	// Compute the speed decrease related to the friction
	speed = speed - (speed * friction_coefficent * t1.asSeconds());

	if (is_up_pressed || is_down_pressed)
	{
		if (is_up_pressed)
		{
			// increase the speed using the acceleration_step (oriented like the spaceship)
			const float current_direction = (sprite.getRotation() * DEG_RAD_SCALE_FACTOR);
			const sf::Vector2f acceleration_versor{ std::sin(current_direction), -std::cos(current_direction) };
			const sf::Vector2f acceleration = acceleration_versor * accelleration_step;
			const sf::Vector2f speed_delta = t1.asSeconds() * acceleration;
			speed = speed + speed_delta;
		}
		if (is_down_pressed)
		{
			// Compute the speed decrease related to the brake
			speed = speed - (speed * brake_coefficent * t1.asSeconds());
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

void Spaceship::HasBeenHit()
{
	// React to an hit
	health_bar.Decrease();
	return;
}

const sf::Image& Spaceship::GetImage() const
{
	return texture.GetImage();
}

void Spaceship::draw(sf::RenderWindow& window) const
{
	health_bar.Draw(window);
	window.draw(sprite);
}
