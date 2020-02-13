#include "stdafx.h"
#include "Pipe.h"

Pipe::Pipe(GameDataRef data) : _data(data)
{
	_landHeight = _data->assets.GetTexture("Land").getSize().y;
	_pipeSpawnOffsetY = 0;
}

void Pipe::DrawPipes()
{
	for (auto &pipeSprite: _pipeSprites)
	{
		_data->window.draw(pipeSprite);
	}
}

void Pipe::SpawnUpPipe()
{
	sf::Sprite sprite(_data->assets.GetTexture("Pipe Up"));
	sprite.setPosition(_data->window.getSize().x, 1.75f * sprite.getGlobalBounds().height - _pipeSpawnOffsetY);
	_pipeSprites.push_back(sprite);
}

void Pipe::SpawnDownPipe()
{
	sf::Sprite sprite(_data->assets.GetTexture("Pipe Down"));
	sprite.setPosition(_data->window.getSize().x, -_pipeSpawnOffsetY);
	_pipeSprites.push_back(sprite);
}

void Pipe::SpawnScoringPipe()
{
	sf::Sprite sprite(_data->assets.GetTexture("Scoring Pipe"));
	sprite.setPosition(_data->window.getSize().x, 0);
	sprite.setColor(sf::Color(0, 0, 0, 0));
	_scoringPipeSprites.push_back(sprite);
}

void Pipe::MovePipes(float dt, int addSpeed)
{
	if (addSpeed > 500)
		addSpeed = 500;
	for (auto pipeSprite = _pipeSprites.begin(); pipeSprite != _pipeSprites.end(); pipeSprite++)
	{
		if (pipeSprite->getPosition().x < 0 - pipeSprite->getGlobalBounds().width)
		{
			pipeSprite = _pipeSprites.erase(pipeSprite);
		}
		else
		{
			float movement = (PIPE_MOVEMENT_SPEED + addSpeed ) * dt;

			pipeSprite->move(-movement, 0);
		}
	}

	for (auto scoringPipeSprite = _scoringPipeSprites.begin(); scoringPipeSprite != _scoringPipeSprites.end(); scoringPipeSprite++)
	{
		if (scoringPipeSprite->getPosition().x < 0 - scoringPipeSprite->getGlobalBounds().width)
		{
			scoringPipeSprite = _scoringPipeSprites.erase(scoringPipeSprite);
		}
		else
		{
			float movement = (PIPE_MOVEMENT_SPEED + addSpeed) * dt;

			scoringPipeSprite->move(-movement, 0);
		}
	}
}

void Pipe::RandomisePipeOffset()
{
	_pipeSpawnOffsetY = rand() % (_landHeight + 1);
}

const std::list<sf::Sprite>& Pipe::GetSprites() const
{
	return _pipeSprites;
}

std::list<sf::Sprite>& Pipe::GetScoringSprites()
{
	return _scoringPipeSprites;
}
