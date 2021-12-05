#pragma once

#include <string>
#include <SFML/Window/Event.hpp>

class Action
{
public:
	Action(const sf::Event& event);

	const sf::Event& m_event;
};