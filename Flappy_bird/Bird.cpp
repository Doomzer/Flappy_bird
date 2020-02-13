#include "stdafx.h"
#include "Bird.h"

Bird::Bird(GameDataRef data):_data(data)
{
	_animationIterator = 0;

	_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 1"));
	_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 2"));
	_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 3"));
	_animationFrames.push_back(_data->assets.GetTexture("Bird Frame 4"));

	_birdSprite.setTexture(_animationFrames.at(_animationIterator));
	_birdSprite.setPosition((_data->window.getSize().x / 4) - (_birdSprite.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_birdSprite.getGlobalBounds().height / 2));

	_birdState = BirdState::eStill;

	sf::Vector2f origin = sf::Vector2f(_birdSprite.getGlobalBounds().width / 2, _birdSprite.getGlobalBounds().height / 2);
	_birdSprite.setOrigin(origin);
	_rotation = 0;
}

void Bird::Draw()
{
	_data->window.draw(_birdSprite);
}

void Bird::Animate(float dt)
{
	if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size())
	{
		if (_animationIterator < _animationFrames.size() - 1)
		{
			_animationIterator++;
		}
		else
		{
			_animationIterator = 0;
		}

		_birdSprite.setTexture(_animationFrames.at(_animationIterator));
		_clock.restart();
	}
}

void Bird::Update(float dt)
{
	if (BirdState::eFalling == _birdState)
	{
		_birdSprite.move(0, GRAVITY * dt);
		_rotation += ROTATION_SPEED;
		if (_rotation > 25.0f)
		{
			_rotation = 25.0f;
		}
		_birdSprite.setRotation(_rotation);
	}
	else if (BirdState::eFlying == _birdState)
	{
		_birdSprite.move(0, -FLYING_SPEED * dt);
		_rotation -= ROTATION_SPEED;
		if (_rotation < -25.0f)
		{
			_rotation = -25.0f;
		}
		_birdSprite.setRotation(_rotation);
	}

	if (_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
	{
		_movementClock.restart();
		_birdState = BirdState::eFalling;
	}
}

void Bird::Tap()
{
	_movementClock.restart();
	_birdState = BirdState::eFlying;
}

const sf::Sprite &Bird::GetSprite() const
{
	return _birdSprite;
}
