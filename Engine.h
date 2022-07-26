#pragma once
#include "LogoState.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "Game.h"
class Engine
{
protected:
	//window rendering
	RenderWindow window;
	const unsigned FPS;
	const Vector2f resolution;

	//states
	LogoState Logo;
	MainMenu mainMenu;
	Game game;
	GameOver Gameover;

	//states controllers
	bool gameOver;
	bool menuState;
	bool gameState;
	bool pauseState;

	//pause text
	Font font;
	Text GamePause;
	String Pause;

	//soundEffects
	SoundBuffer Clickbuffer;
	Sound Click;
	SoundBuffer Enterbuffer;
	Sound Enter;
	SoundBuffer Deadbuffer;
	Sound Dead;
	Music song;

public:
	Engine();
	void run();
	void pause();
	void loadpauseText();
	void loadSoundEffects();
};
