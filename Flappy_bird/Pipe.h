#pragma once


class Pipe
{
public:
	Pipe( GameDataRef data);
	void DrawPipes();
	void SpawnUpPipe();
	void SpawnDownPipe();
	void SpawnScoringPipe();
	void MovePipes(float dt, int addSpeed);
	void RandomisePipeOffset();
	const std::list<sf::Sprite> &GetSprites() const;
	std::list<sf::Sprite> &GetScoringSprites();
private:
	GameDataRef _data;
	std::list<sf::Sprite> _pipeSprites;
	std::list<sf::Sprite> _scoringPipeSprites;

	int _landHeight;
	int _pipeSpawnOffsetY;
};

