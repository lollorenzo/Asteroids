#pragma once

#include <SFML/Graphics.hpp>
#include "common/custom_texture.h"

class Asteroid {
public:
	Asteroid();
	void update(sf::Time t1);
	void draw(sf::RenderWindow& window) const;
private:
	static const CustomTexture texture;		// One shared texture to speedup display operation
	float x_speed, y_speed;					// speed mesured in Pixel per sec (orig top left)
	float rot_speed;						// speed mesured in degrees per sec
	sf::Sprite sprite;
};