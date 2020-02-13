#pragma once

class Land
{
public:
	Land(GameDataRef data);
	
	void MoveLand(float dt, int addSpeed);
	void DrawLand();

	const std::vector<sf::Sprite> &GetSprites() const;
private:
	GameDataRef _data;
	std::vector<sf::Sprite> _landSprites;
};

