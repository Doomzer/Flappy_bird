#include "stdafx.h"

#include "GameManager.h"
#include "States.h"

GameManager::GameManager(int width, int height, std::string title)
{
	srand(time(nullptr));
	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	_data->machine.AddState(StateRef(new MainMenuState(_data)));
	Run();
}

void GameManager::Run()
{
	float newTime, frameTime, interpolation;
	float currentTime = _clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (_data->window.isOpen())
	{
		_data->machine.StateChanges();
		newTime = _clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			_data->machine.GetActiveState()->HandleInput();
			_data->machine.GetActiveState()->Update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		_data->machine.GetActiveState()->Draw(interpolation);
	}
}
