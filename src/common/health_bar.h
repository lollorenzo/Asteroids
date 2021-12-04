#pragma once

#include <SFML/Graphics.hpp>
#include "common/custom_font.h"
#include "common/custom_texture.h"

class HealthBar
{
public:
	HealthBar(int max_health, int decrease_step);
	void Draw(sf::RenderWindow& window) const;
	void Decrease();

private:
	// Get the rectangle of the correct health bar (wrt the texture image) based on the current_health level
	void UpdateBar();

	static const CustomFont font;
	static const int BAR_WIDTH;
	static const int BAR_HEIGHT;
	static const int CHAR_SIZE;

	sf::Text text;
	const int max_health;
	const int decrease_step;
	int current_health;
	sf::RectangleShape external_bar;
	sf::RectangleShape internal_bar;

};