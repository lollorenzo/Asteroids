#pragma once

#include <SFML/Graphics.hpp>
#include "common/custom_texture.h"
#include "common/game_entity.h"

class Asteroid : public GameEntity
{
public:
	Asteroid(const sf::Vector2u& windows_size);
	void update(const sf::Time& t1);
	void draw(sf::RenderWindow& window) const;
	bool IsAlive() const { return alive; }

	// Inherited via GameEntity
	virtual void HasBeenHit() override;

private:
	// Inherited via GameEntity
	virtual const sf::Image& GetImage() const override;

	static const CustomTexture texture;		// One shared texture to speedup display operation
	sf::Vector2f speed;						// speed measured in Pixel per sec (orig top left)
	float rot_speed;						// speed measured in degrees per sec
	bool alive;								// :-)
};