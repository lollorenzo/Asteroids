#include "custom_font.h"

CustomFont::CustomFont(const std::string& file_path) :
	sf::Font()
{
	if (!loadFromFile(file_path))
	{
		// Manage the error correctly
	}
}
