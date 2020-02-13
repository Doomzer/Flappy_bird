#include "stdafx.h"
#include "Land.h"

Land::Land(GameDataRef data): _data(data)
{
	sf::Sprite sprite(_data->assets.GetTexture("Land"));
	sf::Sprite sprite2(_data->assets.GetTexture("Land"));

	sprite.setPosition(0, 1000 - sprite.getGlobalBounds().height);
	sprite2.setPosition(sprite.getGlobalBounds().width, 1000 - sprite.getGlobalBounds().height);

	_landSprites.push_back(sprite);
	_landSprites.push_back(sprite2);
}

void Land::MoveLand(float dt, int addSpeed)
{
	if (addSpeed > 500)
		addSpeed = 500;
	for (auto &landSprite: _landSprites)
	{
		float movement = (PIPE_MOVEMENT_SPEED + addSpeed) * dt;

		landSprite.move(-movement, 0.0f);

		if (landSprite.getPosition().x < 0 - landSprite.getGlobalBounds().width)
		{
			sf::Vector2f position(landSprite.getPosition().x + 2 * landSprite.getGlobalBounds().width, landSprite.getPosition().y);
			landSprite.setPosition(position);
		}
	}
}

void Land::DrawLand()
{
	for (auto &landSprite: _landSprites)
	{
		_data->window.draw(landSprite);
	}
}

const std::vector<sf::Sprite>& Land::GetSprites() const
{
	return _landSprites;
}
