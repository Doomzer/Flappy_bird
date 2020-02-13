#include "stdafx.h"
#include "States.h"

MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{
}

void MainMenuState::Init()
{
	_data->assets.LoadTexture("Main Menu Background", BACKGROUND_FILEPATH);
	_background.setTexture(_data->assets.GetTexture("Main Menu Background"));

	_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
	_title.setTexture(_data->assets.GetTexture("Game Title"));

	_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
	_playButton.setTexture(_data->assets.GetTexture("Play Button"));

	_title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), (_title.getGlobalBounds().height / 2));
	_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));
}

void MainMenuState::HandleInput()
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}

		if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window))
		{
			_data->machine.AddState(StateRef(new InGameState(_data)));
		}
	}
}

void MainMenuState::Update(float dt)
{

}

void MainMenuState::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.draw(_title);
	_data->window.draw(_playButton);
	_data->window.display();
}

InGameState::InGameState(GameDataRef data) : _data(data)
{
}

InGameState::~InGameState()
{
	delete pipe;
	delete land;
	delete bird;
	delete hud;
}

void InGameState::Init()
{
	_data->assets.LoadTexture("Game Background", BACKGROUND_FILEPATH);		
	_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
	_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
	_data->assets.LoadTexture("Land", LAND_FILEPATH);
	_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
	_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
	_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
	_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
	_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
	_data->assets.LoadFont("Flappy Font",FONT_FILEPATH);

	_background.setTexture(_data->assets.GetTexture("Game Background"));

	pipe = new Pipe(_data);	
	land = new Land(_data);
	bird = new Bird(_data);
	hud = new HUD(_data, GameState::ePlaying);

	_score = 0;
	hud->UpdateScore(_score);
	_gameState = GameState::eReady;
}

void InGameState::HandleInput()
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}

		if (_data->input.IsSpriteClicked(_background, sf::Mouse::Left, _data->window))
		{
			if (GameState::eGameOver != _gameState)
			{
				_gameState = GameState::ePlaying;
				bird->Tap();
			}
		}

	}
}

void InGameState::Update(float dt)
{
	if (GameState::eGameOver != _gameState)
	{
		bird->Animate(dt);		
		land->MoveLand(dt, _score * 10);
	}

	if (GameState::ePlaying == _gameState)
	{
		pipe->MovePipes(dt, _score * 10);
		float addSpawn = (float)_score / 50;
		if (_score > 50)
			addSpawn = 1.0f;
		if (_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY - addSpawn)
		{
			pipe->RandomisePipeOffset();

			pipe->SpawnUpPipe();
			pipe->SpawnDownPipe();
			pipe->SpawnScoringPipe();

			_clock.restart();
		}		
		bird->Update(dt);
		std::vector<sf::Sprite> landSprites = land->GetSprites();
		for (auto &landSprite: landSprites)
		{
			if (CheckCollision(bird->GetSprite(), 0.7f, landSprite, 1.0f))
			{
				_gameState = GameState::eGameOver;
				_clock.restart();
				break;
			}
		}
		std::list<sf::Sprite> pipeSprites = pipe->GetSprites();
		for (auto &pipeSprite: pipeSprites)
		{
			if (CheckCollision(bird->GetSprite(), 0.625f, pipeSprite, 1.0f))
			{
				_gameState = GameState::eGameOver;
				_clock.restart();
				break;
			}
		}
		if (GameState::ePlaying == _gameState)
		{
			std::list<sf::Sprite> &scoringPipeSprites = pipe->GetScoringSprites();
			for (auto scoringPipeSprite = scoringPipeSprites.begin(); scoringPipeSprite != scoringPipeSprites.end(); scoringPipeSprite++)
			{
				if (CheckCollision(bird->GetSprite(), 0.4f, *scoringPipeSprite, 0.5f))
				{
					_score++;
					hud->UpdateScore(_score);
					scoringPipeSprites.erase(scoringPipeSprite);
					break;
				}
			}
		}
	}

	if (GameState::eGameOver == _gameState)
	{
		if (_clock.getElapsedTime().asSeconds() > GAME_OVER_DELAY)
		{
			_data->machine.AddState(StateRef(new GameOverState(_data, _score)));
		}
	}

}

void InGameState::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	pipe->DrawPipes();
	land->DrawLand();
	bird->Draw();
	hud->Draw();
	_data->window.display();
}

bool InGameState::CheckCollision(sf::Sprite sprite_1, float scale_1, sf::Sprite sprite_2, float scale_2)
{
	sprite_1.setScale(scale_1, scale_1);
	sprite_2.setScale(scale_2, scale_2);
	sf::Rect<float> rect_1 = sprite_1.getGlobalBounds();
	sf::Rect<float> rect_2 = sprite_2.getGlobalBounds();
	return rect_1.intersects(rect_2);
}

GameOverState::GameOverState(GameDataRef data, int score) : _data(data), _score(score)
{

}

GameOverState::~GameOverState()
{
	delete hud;
}

void GameOverState::Init()
{
	std::ifstream readFile;
	readFile.open(HIGHSCORE_FILEPATH);

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> _highScore;
		}
	}

	readFile.close();

	if (_score > _highScore)
	{
		_highScore = _score;
		std::ofstream writeFile(HIGHSCORE_FILEPATH);

		if (writeFile.is_open())
		{
			writeFile << _highScore;
		}

		writeFile.close();
	}

	_data->assets.LoadTexture("Game Over Background", BACKGROUND_FILEPATH);
	_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);

	_background.setTexture(_data->assets.GetTexture("Game Over Background"));
	_gameOverTitle.setTexture(_data->assets.GetTexture("Game Over Title"));
	_retryButton.setTexture(_data->assets.GetTexture("Play Button"));

	_gameOverTitle.setPosition((_data->window.getSize().x / 2) - (_gameOverTitle.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_gameOverTitle.getGlobalBounds().height * 2));
	_retryButton.setPosition((_data->window.getSize().x / 2) - (_retryButton.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) + (_gameOverTitle.getGlobalBounds().height * 2));

	hud = new HUD(_data, GameState::eGameOver);
	hud->UpdateScore(_score);
	hud->UpdateHighScore(_highScore);
}

void GameOverState::HandleInput()
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}

		if (_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left, _data->window))
		{
			_data->machine.AddState(StateRef(new InGameState(_data)));
		}

	}
}

void GameOverState::Update(float dt)
{
	
}

void GameOverState::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);	
	_data->window.draw(_gameOverTitle);
	_data->window.draw(_retryButton);
	hud->Draw();
	_data->window.display();
}
