#include "SnakeSection.h"

SnakeSection::SnakeSection(Vector2f startingPositon)
	:headRight(true), headDown(false), headUp(false), headLeft(false)
{
	this->SnakeImage = nullptr;
	this->section.setSize(Vector2f(25.f, 25.f));
	this->section.setFillColor(Color::Green);
	this->section.setPosition(startingPositon);
	this->position = startingPositon;
}

void SnakeSection::setPosition(Vector2f newPosition)
{
	this->position = newPosition;
}

Vector2f SnakeSection::getPosition() const
{
	return this->position;
}

void SnakeSection::setTexture(Texture* texture)
{
	this->SnakeImage = texture;
	this->section.setTexture(this->SnakeImage);
	this->section.setScale(1.4f, 1.4f);
}

RectangleShape SnakeSection::getShape() const
{
	return this->section;
}

void SnakeSection::update()
{
	this->section.setPosition(this->position);
}

//setting texture according to head directions
void SnakeSection::setHeadDirection(const char* Direction)
{
	if (Direction == "UP")
	{
		this->headUp = true; this->headDown = false;
		this->headLeft = false; this->headRight = false;
	}
	else if (Direction == "DOWN")
	{
		this->headUp = false; this->headDown = true;
		this->headLeft = false; this->headRight = false;
	}
	else if (Direction == "LEFT")
	{
		this->headUp = false; this->headDown = false;
		this->headLeft = true; this->headRight = false;
	}
	else if (Direction == "RIGHT")
	{
		this->headUp = false; this->headDown = false;
		this->headLeft = false; this->headRight = true;
	}
}

bool SnakeSection::getHeadDirectionRight()const { return this->headRight; }
bool SnakeSection::getHeadDirectionLeft()const { return this->headLeft; }
bool SnakeSection::getHeadDirectionUp()const { return this->headUp; }
bool SnakeSection::getHeadDirectionDown()const { return this->headDown; }
