#include "health_bar.h"

const int HealthBar::BAR_WIDTH = 250;
const int HealthBar::BAR_HEIGHT = 20;
const int HealthBar::CHAR_SIZE = 12;

HealthBar::HealthBar(const AssetManager& asset_manager, int max_health, int decrease_step):
	max_health(max_health),
	decrease_step(decrease_step),
	current_health(max_health),
	external_bar(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT)),
	internal_bar(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT)),
	text()
{
	// set the string to display
	text.setFont(asset_manager.GetFont("atari"));
	text.setString("HP: ");
	text.setCharacterSize(CHAR_SIZE);	// in pixels, not points!
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Regular | sf::Text::Underlined);
	text.setPosition(20, 20);

	// Create the bar using two Rectangular shapes
	external_bar.setOutlineColor(sf::Color::White);
	external_bar.setFillColor(sf::Color::Black);
	external_bar.setOutlineThickness(4);
	internal_bar.setFillColor(sf::Color::Green);

	// Move the bar near the text, we align the center of the bar to the center of the text bounding box
	external_bar.setOrigin(0, BAR_HEIGHT / 2);
	internal_bar.setOrigin(0, BAR_HEIGHT / 2);
	const sf::FloatRect text_bounding_box{ text.getGlobalBounds() };
	const sf::Vector2f destionation_point{ text_bounding_box.left + text_bounding_box.width, text_bounding_box.top + text_bounding_box.height / 2};
	external_bar.setPosition(destionation_point);
	internal_bar.setPosition(destionation_point);
}

void HealthBar::UpdateBar()
{
	// Compute the size of the internal rectangulare shape
	const float current_health_prcentage = static_cast<float>(current_health) / max_health;
	internal_bar.setSize(sf::Vector2f(BAR_WIDTH * current_health_prcentage, BAR_HEIGHT));
	
	if (current_health_prcentage < 0.25f)
	{
		internal_bar.setFillColor(sf::Color::Red);
	}
	else if (current_health_prcentage < 0.50f)
	{
		internal_bar.setFillColor(sf::Color::Yellow);
	}

	return;
}

void HealthBar::Draw(sf::RenderWindow& window) const
{
	window.draw(text);
	window.draw(external_bar);
	window.draw(internal_bar);
}

void HealthBar::Decrease()
{
	current_health -= decrease_step;
	UpdateBar();
}
