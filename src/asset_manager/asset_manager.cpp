#include "asset_manager.h"

AssetManager::AssetManager()
{
	m_fonts.insert({ "atari", sf::Font() });
	m_fonts["atari"].loadFromFile("images/AtariClassic.ttf");
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
