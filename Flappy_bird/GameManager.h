#pragma once

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
};

using GameDataRef = std::shared_ptr<GameData>;

class GameManager
{
public:
	GameManager( int width, int height, std::string title );
private:
	const float dt = 1.0f / 60.0f;
	sf::Clock _clock;
	GameDataRef _data = std::make_shared<GameData>();
	void Run();
};

