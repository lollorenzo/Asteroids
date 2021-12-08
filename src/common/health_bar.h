#pragma once

#include <SFML/Graphics.hpp>
#include <managers/asset_manager.h>

class HealthBar
{
public:
	HealthBar(const AssetManager& asset_manager, int max_health, int decrease_step);
	void Draw(sf::RenderWindow& window) const;
	void Decrease();

private:
	// Get the rectangle of the correct health bar (wrt the texture image) based on the current_health level
	void UpdateBar();

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