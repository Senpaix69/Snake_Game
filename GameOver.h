#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class GameOver
{
	Texture gameOverBackground;
	Texture PlayAgainButton;
	Texture MainMenuButton;
	Texture HoverButton;
	RectangleShape gameOver;
	RectangleShape PlayAgain;
	RectangleShape MainMenu;
	RectangleShape Hover;

	RenderWindow* window;
	Sound* click;
	Sound* enter;

	bool mainMenu;
	bool playAgain;
	bool selectMenu;
	bool selectAgain;

public:
	GameOver();

	void draw();
	void input();
	bool process(RenderWindow& window, Sound& click, Sound& enter);

};

