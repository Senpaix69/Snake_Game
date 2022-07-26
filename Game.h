#pragma once
#include "Apple.h"
#include "Walls.h"
#include <deque>
#include "Assets.h"
#include <iostream>
#include <SFML/Audio.hpp>
enum Direction
{
	UP, RIGHT, DOWN, LEFT 
};
class Game : public Assets
{
	RenderWindow* window;
	static const Time TimePerFrame;
	Time timeSinceLastMove;

	//snakeSection
	vector <SnakeSection> snake;
	deque<int>directionsQueue;  //this will store the directions in queue
	int snakeDirection;
	float speed;
	int sectionsToAdd; //will check how many sections needed to be added to snake body

	//Score Section
	int score;
	int targetScore;
	int addScore;
	int level;
	int highest;

	Apple apple;
	SoundBuffer Eatbuffer;
	Sound Eaten;
	Walls wall;


	bool newgame;
	bool pause;
	bool generateApple;
	int pauseTimer;
	int pauseSec;

public:
	Game();

	//mendatory funcs
	void draw();
	bool input();
	bool update();
	void Levels();
	int run(RenderWindow& window);
	void newGame();
	void playTimer();


	//snake sections
	void newSnake();
	void addSnakeSection();
	void addDirection(int newDirection);
	void checkSnakeHeadDirections();
};

