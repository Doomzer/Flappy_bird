#pragma once

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 768

#define PIPE_MOVEMENT_SPEED 200.0f
#define PIPE_SPAWN_FREQUENCY 1.5f

#define BIRD_ANIMATION_DURATION 0.4f

#define GRAVITY 350.0f
#define FLYING_SPEED 350.0f
#define FLYING_DURATION 0.25f

#define ROTATION_SPEED 100.0f

#define GAME_OVER_DELAY 1.0f

#define BACKGROUND_FILEPATH "Resources/res/sky.png"
#define GAME_TITLE_FILEPATH "Resources/res/title.png"
#define PLAY_BUTTON_FILEPATH "Resources/res/PlayButton.png"

#define PIPE_UP_FILEPATH "Resources/res/PipeUp.png"
#define PIPE_DOWN_FILEPATH "Resources/res/PipeDown.png"

#define LAND_FILEPATH "Resources/res/Land.png"

#define BIRD_FRAME_1_FILEPATH "Resources/res/bird-01.png"
#define BIRD_FRAME_2_FILEPATH "Resources/res/bird-02.png"
#define BIRD_FRAME_3_FILEPATH "Resources/res/bird-03.png"
#define BIRD_FRAME_4_FILEPATH "Resources/res/bird-04.png"

#define SCORING_PIPE_FILEPATH "Resources/res/InvisibleScoringPipe.png"

#define FONT_FILEPATH "Resources/fonts/FlappyFont.ttf"

#define GAME_OVER_TITLE_FILEPATH "Resources/res/Game-Over-Title.png"

#define HIGHSCORE_FILEPATH "Resources/HighScore.txt"

enum class GameState
{
	eReady,
	ePlaying,
	eGameOver
};
