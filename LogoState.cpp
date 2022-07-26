#include "LogoState.h"
LogoState::LogoState()
	:event()
{
	this->window = nullptr;
	this->opacity = 255;
	this->isFlag = true;

	//loading textures
	this->Mylogo.loadFromFile("assets/Logo.png");
	this->Logo.setTexture(&this->Mylogo);
	this->Logo.setSize(Vector2f(600.f, 400.f));
	this->Logo.setPosition(320.f, 250.f);

	//loading GameLogo textures
	this->gameLogo.loadFromFile("assets/SnakeBackground1.jpg");
	this->Gamelogo.setTexture(&this->gameLogo);
	this->Gamelogo.setSize(Vector2f(1222.f, 925.f));
}

void LogoState::displayLogo(RenderWindow& window)
{
	this->window = &window;
	//display the First Logo
	this->Transition.setSize(Vector2f(1222.f, 925.f));
	this->MyLogo();

	if (this->window->isOpen())
	{
		//display the game logo
		this->isFlag = true;
		this->GameLogo();
	}
}

void LogoState::MyLogo()
{
	bool tempFlag = true;
	//displaying myLogo
	while (this->isFlag)
	{
		this->window->clear();
		if (this->opacity >= 0 && tempFlag)
		{
			this->opacity -= 0.5f;
		}
		else { tempFlag = false; }
		if (!tempFlag)
		{
			this->opacity += 0.5f;
			if (this->opacity >= 255) { this->isFlag = false; }
		}
		this->Transition.setFillColor(Color(0, 0, 0, int(this->opacity)));
		this->window->draw(this->Logo);
		this->window->draw(this->Transition);
		this->window->display();

		//check if user wants to exit
		if (this->window->pollEvent(this->event))
		{
			if (this->event.type == Event::Closed)
			{
				this->window->close(); this->isFlag = false;
			}
			else if (this->event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				this->window->close(); this->isFlag = false;
			}
		}
	}
}

void LogoState::GameLogo()
{
	//displaying Gamelogo
	bool tempFlag = true;
	while (this->isFlag)
	{
		this->window->clear();
		if (this->opacity >= 0 && tempFlag)
		{
			this->opacity -= 0.35f;
		}
		else { tempFlag = false; }
		if (!tempFlag)
		{
			this->opacity += 0.35f;
			if (this->opacity >= 255) { this->isFlag = false; }
		}
		this->Transition.setFillColor(Color(0, 0, 0, int(this->opacity)));
		this->window->draw(this->Gamelogo);
		this->window->draw(this->Transition);
		this->window->display();

		//check if user wants to exit
		if (this->window->pollEvent(this->event))
		{
			if (this->event.type == Event::Closed)
			{
				this->window->close(); this->isFlag = false;
			}
			else if (this->event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				this->window->close(); this->isFlag = false;
			}
		}
	}
}