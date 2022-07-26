#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Assets
{
protected:
	//snake
	Texture SnakeBody;
	Texture SnakeHeadDown;
	Texture SnakeHeadUp;
	Texture SnakeHeadLeft;
	Texture SnakeHeadRight;

	//background textures
	Texture BackgroundGrassImage;
	Sprite Grass;

	//ScoreBar Textures
	Texture ScoreBarImage;
	Texture ScoreBackgroundImage;
	Texture LevelBackgroundImage;
	Texture HighestBackgroundImage;
	Sprite ScoreBar;
	Sprite ScoreBackground;
	Sprite LevelBackground;
	Sprite HighestBackground;

	//score Texts
	Text Score;
	Text Level;
	Text Highest;
	Text PlayTimer;
	Font font;
	String DisplayScore;
	String DisplayPlayTimer;
	String DisplayLevels;
	String DisplayHighest;

public:
	Assets();
	void loadGrassSection();
	void loadScoreSection();
	void loadSnakeSection();
};

