#pragma once

#include "State.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "HUD.h"

class MainMenuState :public State
{
public:
	MainMenuState(GameDataRef data);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;
private:
	GameDataRef _data;
	sf::Sprite _background;
	sf::Sprite _title;
	sf::Sprite _playButton;
};

class InGameState :public State
{
public:
	InGameState(GameDataRef data);
	~InGameState();
	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;
	
private:
	bool CheckCollision(sf::Sprite sprite_1, float scale_1, sf::Sprite sprite_2, float scale_2);

	GameDataRef _data;
	sf::Sprite _background;
	Pipe *pipe;
	Land *land;
	Bird *bird;
	HUD *hud;

	sf::Clock _clock;

	GameState _gameState;

	int _score;
};

class GameOverState :public State
{
public:
	GameOverState(GameDataRef data, int score);
	~GameOverState();
	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;
private:
	GameDataRef _data;
	sf::Sprite _background;	
	sf::Sprite _gameOverTitle;
	sf::Sprite _retryButton;
	HUD *hud;

	int _score;
	int _highScore;
};

