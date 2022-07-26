#pragma once
#include "SnakeSection.h"
#include <vector>
using namespace std;
class Apple
{
	Texture appleimage;
	RectangleShape apple;

public:
	Apple();

	void setPosition(Vector2f newPosition);
	RectangleShape getApple()const;
	void moveApple(const RenderWindow* window, const vector<SnakeSection>& snake, const vector<Sprite>& walls, const Sprite& border);
	void drawApple(RenderWindow* window);
};

