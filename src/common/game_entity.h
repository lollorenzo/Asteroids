#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>
#include "custom_texture.h"

class GameEntity 
{
public:
	const sf::Sprite& GetSprite() const { return sprite; };
	void CheckCollision(GameEntity& other);
	virtual void HasBeenHit() = 0;

protected:
	bool PixelLevelCollision(const GameEntity& other) const;
	virtual const sf::Image& GetImage() const = 0;

	sf::Sprite sprite;
};

