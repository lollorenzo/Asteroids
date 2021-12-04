#pragma once

#include <SFML/Graphics.hpp>
#include "common/custom_texture.h"
#include "common/game_entity.h"
#include "common/health_bar.h"

class Spaceship : public GameEntity
{
public:
	Spaceship(const sf::Vector2u& window_size);
	void update(const sf::Time& t1);
	void draw(sf::RenderWindow& window) const;

	// Inherited via GameEntity
	virtual void HasBeenHit() override;

private:
	void update_motion(const sf::Time& t1);

	// Inherited via GameEntity
	virtual const sf::Image& GetImage() const override;

	static const CustomTexture texture;		// One shared texture to speedup display operation
	sf::Vector2f speed;						// speed measured in Pixel per sec (orig top left)
	const float accelleration_step;			// Acceleration step in pixel per sec^2
	const float rotation_step;				// Rotation step in degrees per sec
	const float friction_coefficent;		// Percentage of speed decrease per sec
	const float brake_coefficent;			// Percentage of speed decrease per sec when brake will be pulled
	HealthBar health_bar;
};