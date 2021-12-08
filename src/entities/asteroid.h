#pragma once

#include <SFML/Graphics.hpp>
#include "entities/game_entity.h"
#include "managers/asset_manager.h"

class Asteroid : public GameEntity
{
public:
	Asteroid(const sf::Vector2u& windows_size, const AssetManager& asset_manager);
	Asteroid(const Asteroid& other) = default;
	Asteroid(Asteroid&& other) = default;

	Asteroid& operator=(const Asteroid& other);
	Asteroid& operator=(Asteroid&& other);

	void update(const sf::Time& t1);
	void draw(sf::RenderWindow& window) const;
	bool IsAlive() const { return alive; }

	// Inherited via GameEntity
	virtual void HasBeenHit() override;

private:
	// Inherited via GameEntity
	virtual bool PixelLevelCollision(const sf::Vector2f& point) const override;
	virtual const sf::FloatRect GetBoundingBox() const override;

	const sf::Texture& texture;
	const sf::Image& texture_image;
	sf::Sprite sprite;
	sf::Vector2f speed;						// speed measured in Pixel per sec (orig top left)
	float rot_speed;						// speed measured in degrees per sec
	bool alive;								// :-)
};