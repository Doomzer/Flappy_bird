#pragma once

class AssetManager
{
public:
	void LoadTexture(std::string name, std::string FileName);
	sf::Texture &GetTexture(std::string name);

	void LoadFont(std::string name, std::string FileName);
	sf::Font &GetFont(std::string name);

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
};

