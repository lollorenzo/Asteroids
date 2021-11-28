#include "spaceship.h"

const CustomTexture Spaceship::texture{ "images/spaceship.png" };

Spaceship::Spaceship() :
	speed{ 0.0f, 0.0f },
	accelleration { 20 }
{
	sprite.setTexture(texture);
	sprite.setPosition(512.0f, 288.0f);
	sprite.setOrigin(50, 74);
	sprite.setScale(0.5f, 0.5f);
}

void Spaceship::update(sf::Time t1)
{
	const float speed_delta = t1.asSeconds() * accelleration;
	speed = speed + sf::Vector2f(speed_delta, speed_delta);
	sprite.move(speed * t1.asSeconds());
}

void Spaceship::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}
