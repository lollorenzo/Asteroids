#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class CustomFont : public sf::Font 
{
public:
	CustomFont(const std::string& file_path);
};
