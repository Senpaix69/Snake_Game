#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Walls
{
	vector <Sprite> walls;

	//walls
	Texture TopBottom;
	Texture Vertical;
	Texture doubleWalls;
	Texture singleWall;
	Texture bush;
	Sprite TopBottomWall;
	Sprite VerticalWall;
	Sprite doubleWall;
	Sprite SingleWall;
	Sprite Bush;
public:
	Walls();

	vector <Sprite> getWalls()const;
	void update();

	void draw(RenderWindow* window);
};

