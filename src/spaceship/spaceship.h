#pragma once

#include <SFML/Graphics.hpp>
#include "common/custom_texture.h"

class Spaceship {
public:
	Spaceship();
	void update(sf::Time t1);
	void draw(sf::RenderWindow& window) const;
private:
	static const CustomTexture texture;		// One shared texture to speedup display operation
	sf::Vector2f speed;						// speed mesured in Pixel per sec (orig top left)
	const int accelleration;
	sf::Sprite sprite;
};