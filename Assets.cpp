#include "Assets.h"
Assets::Assets()
{
	this->loadGrassSection();
	this->loadScoreSection();
	this->loadSnakeSection();
}

void Assets::loadGrassSection()
{
	//setting up Grass
	this->BackgroundGrassImage.loadFromFile("assets/GrassBackground.jpg");
	this->Grass.setTexture(this->BackgroundGrassImage);
	this->Grass.setScale(1.5f, 1.5f);
}

void Assets::loadScoreSection()
{
	//setting up scoreBackground
	this->ScoreBarImage.loadFromFile("assets/GrassBackground1.jpg");
	this->ScoreBar.setTexture(this->ScoreBarImage);
	this->ScoreBar.setScale(Vector2f(1.08f, 1.5f));
	this->ScoreBar.setPosition(Vector2f(928.f, 0.f));
	
	this->ScoreBackgroundImage.loadFromFile("assets/Score.png");
	this->ScoreBackground.setTexture(this->ScoreBackgroundImage);
	this->ScoreBackground.setScale(0.08f, 0.1f);
	this->ScoreBackground.setPosition(Vector2f(930.f, 150.f));

	this->LevelBackgroundImage.loadFromFile("assets/Level.png");
	this->LevelBackground.setTexture(this->LevelBackgroundImage);
	this->LevelBackground.setScale(0.08f, 0.1f);
	this->LevelBackground.setPosition(Vector2f(930.f, 350.f));
	
	this->HighestBackgroundImage.loadFromFile("assets/Highest.png");
	this->HighestBackground.setTexture(this->HighestBackgroundImage);
	this->HighestBackground.setScale(0.08f, 0.1f);
	this->HighestBackground.setPosition(Vector2f(930.f, 550.f));

	//setting score/level fonts
	this->font.loadFromFile("assets/Fonts/Slabo27px-Regular.ttf");
	this->Score.setFont(font);
	this->Score.setFillColor(Color::Yellow);
	this->Score.setScale(3.f, 3.f);
	this->Score.setStyle(Text::Bold);
	this->Score.setOutlineColor(Color(165, 42, 42));
	this->Score.setOutlineThickness(1.f);
	this->Score.setPosition(Vector2f(1020.f, 230.f));
	this->Level.setFont(font);
	this->Level.setFillColor(Color::Yellow);
	this->Level.setScale(3.f, 3.f);
	this->Level.setOutlineColor(Color(165, 42, 42));
	this->Level.setOutlineThickness(1.f);
	this->Level.setPosition(Vector2f(1020.f, 430.f));
	this->Level.setStyle(Text::Bold);
	this->Highest.setFont(font);
	this->Highest.setFillColor(Color::Yellow);
	this->Highest.setScale(3.f, 3.f);
	this->Highest.setOutlineColor(Color(165, 42, 42));
	this->Highest.setOutlineThickness(1.f);
	this->Highest.setPosition(Vector2f(1020.f, 630.f));
	this->Highest.setStyle(Text::Bold);
	this->PlayTimer.setFont(font);
	this->PlayTimer.setFillColor(Color::Yellow);
	this->PlayTimer.setScale(4.f, 4.f);
	this->PlayTimer.setOutlineColor(Color(165, 42, 42));
	this->PlayTimer.setOutlineThickness(1.f);
	this->PlayTimer.setPosition(Vector2f(580.f, 340.f));
	this->PlayTimer.setStyle(Text::Bold);
}

void Assets::loadSnakeSection()
{
	//loading Textures of Snake
	this->SnakeHeadDown.loadFromFile("assets/snakeHeadDown.png");
	this->SnakeHeadUp.loadFromFile("assets/snakeHeadUp.png");
	this->SnakeHeadLeft.loadFromFile("assets/snakeHeadLeft.png");
	this->SnakeHeadRight.loadFromFile("assets/snakeHeadRight.png");
	this->SnakeBody.loadFromFile("assets/SnakeBody.png");
}

