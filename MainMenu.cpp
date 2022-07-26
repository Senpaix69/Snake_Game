#include "MainMenu.h"
MainMenu::MainMenu()
{
	this->countInputs = 0;
	this->isPlay = true;
	this->isExit = false;
	this->isSettings = false;
	this->isClose = false;
	this->settingState = false;
	this->isVolume = true;
	this->isMusic = false;
	this->window = nullptr;
	this->click = nullptr;
	this->enter = nullptr;

	this->loadAssets();
}

void MainMenu::draw()
{
	this->window->clear();
	this->window->draw(this->menuBackground);
	if (!settingState)
	{
		this->window->draw(this->Play);
		this->window->draw(this->Settings);
		this->window->draw(this->Exit);
		this->window->draw(this->Hover);
	}
	else
	{
		this->window->draw(this->Volume);
		this->window->draw(this->MusicOnOff);
		this->window->draw(this->Hover);
		this->window->draw(this->Hover2);
	}

	this->window->display();
}

bool MainMenu::input()
{
	Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			this->window->close();
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Up && !isExit && this->countInputs == 1)
			{
				this->click->play();
				this->countInputs = 0;
				this->Hover.setPosition(530.f, 200.f);
				this->isPlay = true;
				this->isExit = false;
				this->isSettings = false;
			}
			if ((event.key.code == Keyboard::Down && !isExit) ||
				(event.key.code == Keyboard::Up && !isPlay))
			{
				this->click->play();
				this->countInputs++;
				if (this->countInputs <= 1)
				{
					this->Hover.setPosition(530.f, 350.f);
					this->isPlay = false;
					this->isExit = false;
					this->isSettings = true;
				}
				else
				{
					this->isSettings = false;
				}
			}
			if (event.key.code == Keyboard::Down && !this->isSettings && !isExit)
			{
				this->click->play();
				this->countInputs = 0;
				this->Hover.setPosition(530.f, 500.f);
				this->isPlay = false;
				this->isExit = true;
				this->isSettings = false;
			}

			if (event.key.code == Keyboard::Enter)
			{
				this->enter->play();
				if (this->isPlay) { return true; }
				else if (this->isExit)
				{
					this->isClose = true;
				}
				else if (this->isSettings)
				{
					this->Hover.setPosition(500.f, 250.f);
					this->settingState = true;
				}
			}
		}
	}
	return false;
}

void MainMenu::settings()
{
	Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			this->window->close();
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Up && !isVolume)
			{
				this->click->play();
				this->isMusic = false;
				this->isVolume = true;
				this->Hover.setPosition(500.f, 250.f);
				this->Hover2.setPosition(978.f, 350.f);
			}
			else if (event.key.code == Keyboard::Down && !isMusic)
			{
				this->click->play();
				this->isVolume = false;
				this->isMusic = true;
				this->Hover.setPosition(500.f, 400.f);
				this->Hover2.setPosition(978.f, 500.f);
			}

			if (event.key.code == Keyboard::Right && isMusic)
			{
				this->click->play();
				this->MusicOnOff.setFillColor(Color::Red);
				this->music->pause();
			}
			else if (event.key.code == Keyboard::Left && isMusic)
			{
				this->click->play();
				this->music->play();
				this->MusicOnOff.setFillColor(Color::White);
			}

			if (event.key.code == Keyboard::Right && isVolume)
			{
				this->click->play();
				if (this->music->getVolume() < 100)
					this->music->setVolume(this->music->getVolume() + 5);
			}
			else if (event.key.code == Keyboard::Left && isVolume)
			{
				this->click->play();
				if (this->music->getVolume() > 10)
					this->music->setVolume(this->music->getVolume() - 5);
			}

			//return to mainMenu
			if (event.key.code == Keyboard::Enter || event.key.code == Keyboard::Escape)
			{
				this->settingState = false;
				this->isVolume = true;
				this->isMusic = false;
				this->Hover2.setPosition(978.f, 350.f);
				this->Hover.setPosition(530.f, 350.f);
			}
		}
	}
}

void MainMenu::loadAssets()
{
	//background texture loading
	this->menubackgroundimg.loadFromFile("assets/MainMenu.jpg");
	this->menuBackground.setTexture(&this->menubackgroundimg);
	this->menuBackground.setSize(Vector2f(1222.f, 925.f));

	//buttons texture loading
	this->PlayButton.loadFromFile("assets/PlayButton.png");
	this->ExitButton.loadFromFile("assets/ExitButton.png");
	this->SettingButton.loadFromFile("assets/SettingsButton.png");
	this->HoverButton.loadFromFile("assets/Arrow.png");
	this->VolumeButton.loadFromFile("assets/Volume.png");
	this->MusicOnOffButton.loadFromFile("assets/MusicOnOff.png");

	//setting textures
	this->Hover.setTexture(&this->HoverButton);
	this->Hover2.setTexture(&this->HoverButton);
	this->Play.setTexture(&this->PlayButton);
	this->Exit.setTexture(&this->ExitButton);
	this->Settings.setTexture(&this->SettingButton);
	this->Volume.setTexture(&this->VolumeButton);
	this->MusicOnOff.setTexture(&this->MusicOnOffButton);

	//setting sizes
	this->Hover.setSize(Vector2f(80.f, 100.f));
	this->Hover2.setSize(Vector2f(80.f, 100.f));
	this->Play.setSize(Vector2f(250.f, 100.f));
	this->Exit.setSize(Vector2f(250.f, 100.f));
	this->Settings.setSize(Vector2f(250.f, 100.f));
	this->Volume.setSize(Vector2f(300.f, 100.f));
	this->MusicOnOff.setSize(Vector2f(300.f, 100.f));

	//setting positions
	this->Hover.setPosition(530.f, 200.f);
	this->Hover2.setRotation(180.f);
	this->Hover2.setPosition(978.f, 350.f);
	this->Play.setPosition(610.f, 200.f);
	this->Settings.setPosition(610.f, 350.f);
	this->Exit.setPosition(610.f, 500.f);
	this->Volume.setPosition(590.f, 250.f);
	this->MusicOnOff.setPosition(590.f, 400.f);
}

bool MainMenu::process(RenderWindow& window, Sound& click, Sound& enter, Music& music)
{
	this->window = &window;
	this->click = &click;
	this->enter = &enter;
	this->music = &music;
	while (this->window->isOpen())
	{
		if (!isClose)
		{
			if (!settingState)
			{
				if (this->input())
				{
					return true;
				}
			}
			else
			{
				this->settings();
			}
			this->draw();
		}
		else
		{
			this->window->close();
		}
	}
	return true;
}