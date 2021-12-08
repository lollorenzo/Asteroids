#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>

class GameEntity 
{
public:
	void CheckCollision(GameEntity& other);
	virtual void HasBeenHit() = 0;

protected:
	virtual bool PixelLevelCollision(const sf::Vector2f& point) const = 0;
	virtual const sf::FloatRect GetBoundingBox() const = 0;
};

