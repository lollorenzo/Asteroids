#include "asset_manager.h"

AssetManager::AssetManager()
{
	m_fonts.insert({ "atari", sf::Font() });
	m_fonts["atari"].loadFromFile("images/AtariClassic.ttf");

	m_images.insert({ "asteroid", sf::Image() });
	m_images["asteroid"].loadFromFile("./images/asteroid.png");
	m_images.insert({ "spaceship", sf::Image() });
	m_images["spaceship"].loadFromFile("images/spaceship.png");

	m_textures.insert({ "asteroid", sf::Texture() });
	m_textures["asteroid"].loadFromImage(m_images["asteroid"]);
	m_textures.insert({ "spaceship", sf::Texture() });
	m_textures["spaceship"].loadFromImage(m_images["spaceship"]);
}

const sf::Font& AssetManager::GetFont(const std::string& name) const
{
	auto it = m_fonts.find(name);
	if (it == m_fonts.end())
	{
		// No value found, manage it!
	}
	return it->second;
}

const sf::Texture& AssetManager::GetTexture(const std::string& name) const
{
	auto it = m_textures.find(name);
	if (it == m_textures.end())
	{
		// No value found, manage it!
	}
	return it->second;
}

const sf::Image& AssetManager::GetImage(const std::string& name) const
{
	auto it = m_images.find(name);
	if (it == m_images.end())
	{
		// No value found, manage it!
	}
	return it->second;
}
