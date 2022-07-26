#include "GameOver.h"

GameOver::GameOver()
{
	this->window = nullptr;
	this->click = nullptr;
	this->enter = nullptr;
	this->mainMenu = true;
	this->playAgain = false;
	this->selectAgain = false;
	this->selectMenu = false;

	//loading background
	this->gameOverBackground.loadFromFile("assets/gameOver.jpg");
	this->gameOver.setTexture(&this->gameOverBackground);
	this->gameOver.setSize(Vector2f(1222.f, 925.f));

	//loading textures
	this->HoverButton.loadFromFile("assets/Arrow.png");
	this->PlayAgainButton.loadFromFile("assets/PlayAgainButton.png");
	this->MainMenuButton.loadFromFile("assets/MainMenuButton.png");

	//setting textures
	this->Hover.setTexture(&this->HoverButton);
	this->MainMenu.setTexture(&this->MainMenuButton);
	this->PlayAgain.setTexture(&this->PlayAgainButton);

	//setting sizes
	this->Hover.setSize(Vector2f(80.f, 90.f));
	this->MainMenu.setSize(Vector2f(270.f, 120.f));
	this->PlayAgain.setSize(Vector2f(270.f, 120.f));

	//setting positions
	this->Hover.setPosition(Vector2f(170.f, 665.f));
	this->MainMenu.setPosition(Vector2f(270.f, 650.f));
	this->PlayAgain.setPosition(Vector2f(700.f, 652.f));
}

void GameOver::draw()
{
	this->window->clear();
	this->window->draw(this->gameOver);
	this->window->draw(this->MainMenu);
	this->window->draw(this->PlayAgain);
	this->window->draw(this->Hover);
	this->window->display();
}

void GameOver::input()
{
	Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Right && !this->playAgain)
			{
				this->click->play();
				this->playAgain = true;
				this->mainMenu = false;
				this->Hover.setPosition(Vector2f(610.f, 665.f));
			}
			else if (event.key.code == Keyboard::Left && !this->mainMenu)
			{
				this->click->play();
				this->playAgain = false;
				this->mainMenu = true;
				this->Hover.setPosition(Vector2f(180.f, 665.f));
			}
			if (event.key.code == Keyboard::Enter)
			{
				this->enter->play();
				if (this->playAgain)
				{
					this->selectAgain = true;
				}
				else if (this->mainMenu)
				{
					this->selectMenu = true;
				}
			}
		}
	}
}
bool GameOver::process(RenderWindow& window, Sound& click, Sound& enter)
{
	this->window = &window;
	this->click = &click;
	this->enter = &enter;
	while (this->window->isOpen())
	{
		this->input();
		if (this->selectAgain)
		{
			this->selectAgain = false;
			return true;
		}
		else if (this->selectMenu)
		{
			this->selectMenu = false;
			return false;
		}
		this->draw();
	}
	return true;
}