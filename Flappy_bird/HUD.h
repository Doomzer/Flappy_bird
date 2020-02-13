#pragma once

class HUD
{
public:
	HUD(GameDataRef data, GameState gameState);
	void Draw();
	void UpdateScore(int score);
	void UpdateHighScore(int highScore);

private:
	GameDataRef _data;
	sf::Text _scoreText;
	sf::Text _highScoreText;
	GameState _gameState;
};

