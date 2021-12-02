#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>

class GameEntity 
{
public:
	const sf::Sprite& GetSprite() const { return sprite; };
	virtual const sf::Image& GetImage() const = 0;
	virtual void HasBeenHit() = 0;

protected:
	sf::Sprite sprite;
};