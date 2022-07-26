#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
using namespace sf;
class MainMenu
{
	//temp variables
	RenderWindow* window;
	Sound* click;
	Music* music;
	Sound* enter;

	//Textures of Main Menu
	Texture menubackgroundimg;
	Texture PlayButton;
	Texture SettingButton;
	Texture ExitButton;
	Texture HoverButton;
	Texture VolumeButton;
	Texture MusicOnOffButton;
	RectangleShape menuBackground;
	RectangleShape Play;
	RectangleShape Exit;
	RectangleShape Settings;
	RectangleShape Hover;
	RectangleShape Hover2;
	RectangleShape Volume;
	RectangleShape MusicOnOff;


	//for hovering positions
	bool isPlay;
	bool isSettings;
	bool isExit;
	bool settingState;
	bool isVolume;
	bool isMusic;
	int countInputs;

	//checking for user specific input
	bool isClose;

public:
	MainMenu();
	void draw();
	bool input();
	void settings();
	void loadAssets();
	bool process(RenderWindow& window, Sound& click, Sound& enter, Music& music);
};

