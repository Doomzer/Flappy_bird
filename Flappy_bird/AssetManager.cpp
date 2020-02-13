#include "stdafx.h"

#include "AssetManager.h"

void AssetManager::LoadTexture(std::string name, std::string FileName)
{
	sf::Texture temp_tex;
	if (temp_tex.loadFromFile(FileName))
	{
		_textures[name] = temp_tex;
	}
}

sf::Texture & AssetManager::GetTexture(std::string name)
{
	return _textures.at(name);
}

void AssetManager::LoadFont(std::string name, std::string FileName)
{
	sf::Font temp_font;
	if (temp_font.loadFromFile(FileName))
	{
		_fonts[name] = temp_font;
	}
}

sf::Font & AssetManager::GetFont(std::string name)
{
	return _fonts.at(name);
}
