#include "custom_texture.h"

CustomTexture::CustomTexture(const std::string& file_path) :
	sf::Texture()
{
	image.loadFromFile(file_path);
	if (!loadFromImage(image))
	{
		// Manage the error correctly
	}

	setSmooth(true);
}
