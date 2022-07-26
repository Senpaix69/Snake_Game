#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class SnakeSection
{
	Vector2f position;
	RectangleShape section;
	Texture* SnakeImage;
	bool headLeft;
	bool headRight;
	bool headUp;
	bool headDown;

public:
	SnakeSection(Vector2f startingPositon);
	void setPosition(Vector2f newPosition);
	Vector2f getPosition()const;
	void setTexture(Texture* texture);
	RectangleShape getShape()const;
	void update();


	//Texture of head Directions
	void setHeadDirection(const char* Direction);
	bool getHeadDirectionRight()const;
	bool getHeadDirectionLeft()const;
	bool getHeadDirectionUp()const;
	bool getHeadDirectionDown()const;
};