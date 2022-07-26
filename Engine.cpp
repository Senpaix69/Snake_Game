#include "Engine.h"

Engine::Engine()
	:FPS(120), resolution(1222.f, 925.f)
{
	this->gameOver = false; this->menuState = true;
	this->gameState = false; this->pauseState = false;

	//windows section
	this->window.create(VideoMode(this->resolution.x, this->resolution.y), "Snake Game", Style::Close);
	this->window.setFramerateLimit(FPS);

	//loading assets
	this->loadpauseText();
	this->loadSoundEffects();
}

void Engine::run()
{
	this->Logo.displayLogo(this->window);
	this->song.play();
	this->song.setLoop(true);
	this->song.setVolume(100);
	while (this->window.isOpen())
	{
		//displaying main menu
		if (this->menuState)
		{
			if (this->mainMenu.process(this->window, this->Click, this->Enter, this->song))
			{
				this->gameState = true;
				this->menuState = false;
				this->gameOver = false;
			}
		}
		if (this->gameState)
		{
			int flag = this->game.run(this->window);
			if (flag == 1) //gameOver
			{
				this->gameOver = true;
				this->gameState = false;
			}
			else if (flag == 2) //mainMenu
			{
				this->pauseState = true;
				this->gameState = false;
			}
		}
		if (this->gameOver)
		{
			this->Dead.play();
			bool stateflag = this->Gameover.process(this->window, this->Click, this->Enter);
			if (stateflag) //newGame
			{
				this->gameOver = false;
				this->gameState = true;
			}
			else if (!stateflag) //mainMenu
			{
				this->menuState = true;
				this->gameOver = false;;
			}
		}
		if (pauseState)
		{
			this->pause();
		}
	}
}

void Engine::pause()
{
	Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		{
			this->pauseState = false;
			this->gameState = true;
		}
	}
	this->window.draw(this->GamePause);
	this->window.display();

}

void Engine::loadpauseText()
{
	//gamePause
	this->font.loadFromFile("assets/Fonts/Slabo27px-Regular.ttf");
	this->GamePause.setFont(font);
	this->GamePause.setFillColor(Color::Yellow);
	this->GamePause.setScale(2.f, 2.f);
	this->GamePause.setOutlineColor(Color(165, 42, 42));
	this->GamePause.setOutlineThickness(1.f);
	this->GamePause.setPosition(Vector2f(420.f, 390.f));
	this->GamePause.setStyle(Text::Bold);
	this->Pause = "GAME PAUSED";
	this->GamePause.setString(this->Pause);
}

void Engine::loadSoundEffects()
{
	//soundeffects
	this->Clickbuffer.loadFromFile("assets/SoundEffects/Click.wav");
	this->Click.setBuffer(this->Clickbuffer);
	this->Enterbuffer.loadFromFile("assets/SoundEffects/Enter.wav");
	this->Enter.setBuffer(this->Enterbuffer);
	this->Deadbuffer.loadFromFile("assets/SoundEffects/GameOver.wav");
	this->Dead.setBuffer(this->Deadbuffer);
	this->song.openFromFile("assets/SoundEffects/Gameplay2.wav");
}
