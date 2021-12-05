#pragma once

#include <SFML/Graphics.hpp>
#include "action/action.h"

class GameEngine;

class Scene
{
public:
	Scene(GameEngine* game_engine, sf::RenderWindow* window) :
		m_game_engine(game_engine),
		m_window(window),
		m_paused(false),
		m_ended(false) { }

	virtual void Update() = 0;
	virtual void Render() const = 0;
	virtual void DoAction(const Action& action) = 0;
	virtual void Pause() = 0;
	virtual void Play() = 0;

protected:
	GameEngine* m_game_engine;
	sf::RenderWindow* m_window;
	bool m_paused;
	bool m_ended;
};