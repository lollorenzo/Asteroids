#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class CustomTexture : public sf::Texture {
public:
	CustomTexture(const std::string& file_path);
};
