#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class LogoState
{
	RenderWindow* window;
	Event event;
	Texture Mylogo;
	Texture gameLogo;
	RectangleShape Logo;
	RectangleShape Gamelogo;
	RectangleShape Transition;
	float opacity;
	bool isFlag;
public:
	LogoState();
	void displayLogo(RenderWindow& window);
	void MyLogo();
	void GameLogo();
};

