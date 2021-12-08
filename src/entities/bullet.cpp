#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <utility>
#include <array>
#include "bullet.h"

const float Bullet::speed_module{ 300 };
const float Bullet::lifetime{ 1.5f };

// Initialize asteroid with random speed and rot_speed
Bullet::Bullet(const sf::Vector2f& position, float rotation) :
	GameEntity(),
	shape(4.0f),
	speed(),
	time_elapsed(0),
	alive(true)
{
	// Compute the speed vector starting from the speed module and the angle
	static const float DEG_RAD_SCALE_FACTOR = (3.1415f / 180);
	const float rad_rotation = (rotation * DEG_RAD_SCALE_FACTOR);
	const sf::Vector2f speed_versor{ std::cos(rad_rotation), std::sin(rad_rotation) };
	speed = speed_versor * speed_module;
	shape.setOrigin(2.0f, 2.0f);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(position);
	shape.setRotation(rotation);
}

void Bullet::update(const sf::Time& t1)
{
	if (!alive)
	{
		return;
	}

	// Update position using speed along x and y
	const float delta_time_in_sec = t1.asSeconds();
	time_elapsed = time_elapsed + delta_time_in_sec;
	shape.move(speed * delta_time_in_sec);

	sf::Color current_color = shape.getFillColor();
	current_color.a = sf::Color::White.a * (1 - (time_elapsed / lifetime));
	shape.setFillColor(current_color);

	if (time_elapsed >= lifetime)
	{
		alive = false;
	}
}

void Bullet::draw(sf::RenderWindow& window) const
{
	if (!alive)
	{
		return;
	}

	window.draw(shape);
}

void Bullet::HasBeenHit()
{
	// React to an hit
	alive = false;
	return;
}

bool Bullet::PixelLevelCollision(const sf::Vector2f& point) const
{
	const sf::Vector2f distance = shape.getPosition() - point;
	const float distance_module = std::sqrtf((distance.x * distance.x) + (distance.y * distance.y));
	return distance_module < shape.getRadius();
}

const sf::FloatRect Bullet::GetBoundingBox() const
{
	return shape.getGlobalBounds();
}
