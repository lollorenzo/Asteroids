#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <string>
#include "scene.h"
#include "game_engine/game_engine.h"
#include "asteroid/asteroid_manager.h"
#include "asset_manager/asset_manager.h"

class MenuScene : public Scene
{
public:
	MenuScene(GameEngine* game_engine, sf::RenderWindow* window, const AssetManager& asset_manager);

	// Inherited by Scene
	virtual void Update() override;
	virtual void Render() const override;
	virtual void DoAction(const Action& action) override;
	virtual void Pause() override;
	virtual void Play() override;

private:

	void SetTextPosition();

	const int CHAR_HEIGHT = 25;
	const int BIG_CHAR_HEIGHT = 35;
	const int CHAR_PADDING = 15;
	const int MENU_HEIGHT = (CHAR_HEIGHT + CHAR_PADDING) * (m_menu_voices.size() - 1) + BIG_CHAR_HEIGHT + CHAR_PADDING;
	const float MENU_SPEED = 0.25f;
	const std::array<std::string, 4> m_menu_voices{ "PLAY", "STOP", "BOH", "EXIT" };

	const AssetManager& m_asset_manager;
	sf::RectangleShape m_background;
	sf::Clock m_clock;
	AsteroidManager m_asteroid_manager;
	std::vector<sf::Text> m_texts;
	int m_current_menu_voice;
};