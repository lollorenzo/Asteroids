#pragma once

#include <SFML/Graphics.hpp>
#include "common/custom_texture.h"
#include "common/game_entity.h"

class Bullet : public GameEntity
{
public:
	Bullet(const sf::Vector2f& position, float rotation);
	void update(const sf::Time& t1);
	void draw(sf::RenderWindow& window) const;
	bool IsAlive() const { return alive; }

	// Inherited via GameEntity
	virtual void HasBeenHit() override;

private:
	// Inherited via GameEntity
	virtual bool PixelLevelCollision(const sf::Vector2f& point) const override;
	virtual const sf::FloatRect GetBoundingBox() const override;

	sf::CircleShape shape;
	sf::Vector2f speed;						// speed measured in Pixel per sec (orig top left)
	static const float speed_module;
	static const float lifetime;
	float time_elapsed;
	bool alive;								// :-)
};