#include "stdafx.h"
#include "HUD.h"

HUD::HUD(GameDataRef data, GameState gameState) : _data(data), _gameState(gameState)
{
	if (GameState::ePlaying == _gameState)
	{
		_scoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_scoreText.setString("0");
		_scoreText.setCharacterSize(128);
		_scoreText.setFillColor(sf::Color::White);
		_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
		_scoreText.setPosition(_data->window.getSize().x / 2, _data->window.getSize().x / 5);
	}
	else if (GameState::eGameOver == _gameState)
	{
		_scoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_scoreText.setCharacterSize(56);
		_scoreText.setFillColor(sf::Color::White);
		_scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
		_scoreText.setPosition(_data->window.getSize().x / 4, _data->window.getSize().y / 2.15);

		_highScoreText.setFont(_data->assets.GetFont("Flappy Font"));
		_highScoreText.setCharacterSize(56);
		_highScoreText.setFillColor(sf::Color::White);
		_highScoreText.setOrigin(_highScoreText.getGlobalBounds().width / 2, _highScoreText.getGlobalBounds().height / 2);
		_highScoreText.setPosition(_data->window.getSize().x / 4, _data->window.getSize().y / 1.80);
	}
}

void HUD::Draw()
{
	if (GameState::ePlaying == _gameState)
	{
		_data->window.draw(_scoreText);
	}
	else if (GameState::eGameOver == _gameState)
	{
		_data->window.draw(_scoreText);
		_data->window.draw(_highScoreText);
	}
}

void HUD::UpdateScore(int score)
{
	if (GameState::ePlaying == _gameState)
	{
		_scoreText.setString(std::to_string(score));
	}
	else if (GameState::eGameOver == _gameState)
	{
		_scoreText.setString("Your score: " + std::to_string(score));
	}
}

void HUD::UpdateHighScore(int highScore)
{
	_highScoreText.setString("High score: " + std::to_string(highScore));
}
