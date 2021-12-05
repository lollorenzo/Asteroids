#pragma once

#include<map>
#include<memory>
#include<string>
#include<SFML/Graphics.hpp>

class AssetManager
{
public:
	AssetManager();

	const sf::Font& GetFont(const std::string& name) const;
	const sf::Texture& GetTexture(const std::string& name) const;

private:
	template <typename asset_type>
	using asset_container_type = std::map<std::string, asset_type>;

	asset_container_type<sf::Font> m_fonts;
	asset_container_type<sf::Texture> m_textures;
};