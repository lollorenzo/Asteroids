#include "custom_texture.h"

CustomTexture::CustomTexture(const std::string& file_path) :
	sf::Texture()
{
	sf::Texture prova;
	if (!loadFromFile(file_path))
	{
		// Manage the error correctly
	}

	setSmooth(true);
}
