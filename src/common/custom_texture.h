#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class CustomTexture : public sf::Texture {
public:
	CustomTexture(const std::string& file_path);
	const sf::Image& GetImage() const { return image; }

private:
	sf::Image image;
};
