#pragma once

#include <SFML/Graphics.hpp>
#include "common/custom_texture.h"
#include "common/game_entity.h"
#include "common/health_bar.h"
#include "bullet/bullet_manager.h"

class Spaceship : public GameEntity
{
public:
	Spaceship(const sf::Vector2u& window_size);

	void update(const sf::Time& t1);
	void draw(sf::RenderWindow& window) const;

	void CheckBulletCollision(GameEntity& other);
	void CheckCollision(GameEntity& other);

	// Inherited via GameEntity
	virtual void HasBeenHit() override;

private:
	void update_motion(const sf::Time& t1);
	void shoot(const sf::Time& t1);

	// Inherited via GameEntity
	virtual bool PixelLevelCollision(const sf::Vector2f& point) const override;
	virtual const sf::FloatRect GetBoundingBox() const override;

	static const CustomTexture texture;		// One shared texture to speedup display operation
	sf::Sprite sprite;
	sf::Vector2f speed;						// speed measured in Pixel per sec (orig top left)
	const float accelleration_step;			// Acceleration step in pixel per sec^2
	const float rotation_step;				// Rotation step in degrees per sec
	const float friction_coefficent;		// Percentage of speed decrease per sec
	const float brake_coefficent;			// Percentage of speed decrease per sec when brake will be pulled
	const float firing_frequency;			// bullet per second
	HealthBar health_bar;
	BulletManager bullet_manager;
	float time_accumulator;
};