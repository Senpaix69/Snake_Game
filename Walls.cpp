#include "Walls.h"

Walls::Walls()
{
	//walls 
	this->TopBottom.loadFromFile("assets/Walls.png");
	this->TopBottomWall.setTexture(this->TopBottom);
	this->Vertical.loadFromFile("assets/Walls1.png");
	this->VerticalWall.setTexture(this->Vertical);
	this->doubleWalls.loadFromFile("assets/Walls2.png");
	this->doubleWall.setTexture(this->doubleWalls);
	this->singleWall.loadFromFile("assets/Walls3.png");
	this->SingleWall.setTexture(this->singleWall);
	this->bush.loadFromFile("assets/Tree1.png");
	this->Bush.setTexture(this->bush);
	this->update();
}

vector<Sprite> Walls::getWalls() const
{
	return walls;
}

void Walls::update()
{
	for (int i = 0, x = 0, count = 0; i < 5; i++)
	{
		float lastPosition = 0.f;
		if (i == 0) // top walls
		{
			lastPosition = 10.f;
			while (count <= 7)
			{
				this->walls.emplace_back(this->TopBottom);
				this->walls[x].setPosition(lastPosition, 0.f);
				lastPosition += 150.f;
				this->walls[x].setScale(0.06f, 0.06f);
				x++; count++;
			}
		}
		if (i == 1) // Bottom walls
		{
			lastPosition = 10.f;
			count = 0;
			while (count <= 7)
			{
				this->walls.emplace_back(this->TopBottom);
				this->walls[x].setPosition(lastPosition, 860.f);
				lastPosition += 150.f;
				this->walls[x].setScale(0.06f, 0.06f);
				x++; count++;
			}
		}
		if (i == 2) //right walls
		{
			lastPosition = 79.f;
			count = 0;
			while (count <= 4)
			{
				this->walls.emplace_back(this->VerticalWall);
				this->walls[x].setPosition(880.f, lastPosition);
				lastPosition += 150.f;
				this->walls[x].setScale(0.06f, 0.06f);
				x++; count++;
			}
		}
		if (i == 3) //left walls
		{
			lastPosition = 79.f;
			count = 0;
			while (count <= 4)
			{
				this->walls.emplace_back(this->VerticalWall);
				this->walls[x].setPosition(0.f, lastPosition);
				lastPosition += 150.f;
				this->walls[x].setScale(0.06f, 0.06f);
				x++; count++;
			}
		}
		if (i == 4) //right walls second
		{
			lastPosition = 79.f;
			count = 0;
			while (count <= 4)
			{
				this->walls.emplace_back(this->VerticalWall);
				this->walls[x].setPosition(1170.f, lastPosition);
				lastPosition += 150.f;
				this->walls[x].setScale(0.06f, 0.06f);
				x++; count++;
			}
		}
	}
}

void Walls::draw(RenderWindow* window)
{
	for (auto& w : walls)
	{
		window->draw(w);
	}
	//Top Left Corner
	this->Bush.setScale(0.2f, 0.2f);
	this->Bush.setPosition(-0.04f, -0.04f);
	window->draw(Bush);
	this->Bush.setPosition(840.f, 0.04f);
	window->draw(Bush);
	this->Bush.setPosition(1130.f, 0.04f);
	window->draw(Bush);
	this->Bush.setPosition(-1.5f, 755.f);
	window->draw(Bush);
	this->Bush.setPosition(840.f, 755.f);
	window->draw(Bush);
	this->Bush.setPosition(1130.f, 755.f);
	window->draw(Bush);
}
