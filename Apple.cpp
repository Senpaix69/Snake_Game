#include "Apple.h"

Apple::Apple()
{
	this->appleimage.loadFromFile("assets/apple.png");
	this->apple.setTexture(&this->appleimage);
	this->apple.setSize(Vector2f(20.f, 20.f));
	this->apple.setScale(Vector2f(1.5f, 1.5f));
}

void Apple::setPosition(Vector2f newPosition)
{
	this->apple.setPosition(newPosition);
}

RectangleShape Apple::getApple()const
{
	return this->apple;
}

void Apple::moveApple(const RenderWindow* window, const vector<SnakeSection>& snake, const vector<Sprite>& walls, const Sprite& border)
{
	srand(time(nullptr));
	//Find apple location to relocate new apple in field
	//also we must not include the position of apple inside snake body or a wall
	Vector2f newLocation;
	bool isValid = false; //will check if the newposition is valid or not
	do
	{
		isValid = true;
		newLocation.x = rand() % (window->getSize().x - 24);
		newLocation.y = rand() % (window->getSize().y - 24);

		//check if the newposition apple is in snake body
		for (auto& s : snake)
		{
			if (s.getShape().getGlobalBounds().intersects(Rect<float>(newLocation.x, newLocation.y, 24, 20)))
			{
				isValid = false;
				break;
			}
		}
		//check if newposition apple is in walls
		for (auto& w : walls)
		{
			if (w.getGlobalBounds().intersects(Rect<float>(newLocation.x, newLocation.y, 30, 30)))
			{
				isValid = false;
				break;
			}
		}
		if (border.getGlobalBounds().intersects(Rect<float>(newLocation.x, newLocation.y, 24, 24)))
		{
			isValid = false;
		}

	} while (!isValid);
	this->setPosition(newLocation);
}

void Apple::drawApple(RenderWindow* window)
{
	window->draw(this->apple);
}