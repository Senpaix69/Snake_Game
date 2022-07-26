#include "Game.h"

const Time Game::TimePerFrame = seconds(1.f / 60.f);
Game::Game()
{
	this->window = nullptr;
	this->timeSinceLastMove = Time::Zero;
	this->speed = 0;
	this->sectionsToAdd = 0;
	this->snakeDirection = 0;
	this->level = 0;
	this->targetScore = 0;
	this->score = 0;
	this->highest = 0;
	this->addScore = 0;
	this->newgame = true;
	this->pause = false;
	this->generateApple = false;
	this->pauseTimer = 0;
	this->pauseSec = 0;
	this->Eatbuffer.loadFromFile("assets/SoundEffects/Eat.wav");
	this->Eaten.setBuffer(this->Eatbuffer);
}

void Game::newGame()
{
	this->timeSinceLastMove = Time::Zero;
	this->level = 1;
	this->score = 0;
	this->targetScore = 14;
	this->addScore = 10;
	this->speed = 7.f;
	this->sectionsToAdd = 0;
	this->snakeDirection = Direction::RIGHT;
	this->pauseTimer = 110;
	this->pauseSec = 3;
	this->DisplayPlayTimer = to_string(this->pauseSec);
	this->PlayTimer.setString(this->DisplayPlayTimer);
	this->newSnake();
}

void Game::playTimer()
{
	this->pauseTimer--;
	if (this->pauseTimer == 0)
	{
		this->pauseSec--;
		this->DisplayPlayTimer = to_string(this->pauseSec);
		this->PlayTimer.setString(this->DisplayPlayTimer);
		this->pauseTimer = 110;
	}
	if (this->pauseSec == 0)
	{
		this->pauseSec = 3;
		this->DisplayPlayTimer = to_string(this->pauseSec);
		this->PlayTimer.setString(this->DisplayPlayTimer);
		this->pauseTimer = 110;
		this->pause = false;
	}
}

void Game::Levels()
{
	if (this->score == this->targetScore)
	{
		this->level++;
		this->speed += 1.f;
		this->targetScore += this->addScore;
		this->addScore += 6;
	}
	if (this->score >= this->highest) { this->highest = this->score; }
	this->DisplayScore = to_string(this->score);
	this->Score.setString(this->DisplayScore);
	this->DisplayLevels = to_string(this->level);
	this->Level.setString(this->DisplayLevels);
	this->DisplayHighest = to_string(this->highest);
	this->Highest.setString(this->DisplayHighest);
}

void Game::newSnake()
{
	this->snake.clear();
	this->snake.emplace_back(Vector2f(200, 200));
	this->snake[0].setTexture(&this->SnakeHeadRight);
	this->snake[0].getShape().setOrigin(this->snake[0].getShape().getSize().x / 2, this->snake[0].getShape().getSize().y / 2);
	this->snake.emplace_back(Vector2f(170, 200));
	this->snake[1].setTexture(&this->SnakeBody);
	this->snake.emplace_back(Vector2f(140, 200));
	this->snake[2].setTexture(&this->SnakeBody);

	//generate apple
	this->apple.moveApple(this->window, this->snake, this->wall.getWalls(), this->ScoreBar);
}

void Game::addSnakeSection()
{
	Vector2f newSnakeSection = this->snake[this->snake.size() - 1].getPosition();
	this->snake.emplace_back(newSnakeSection);
	this->snake.back().setTexture(&this->SnakeBody);
}

bool Game::input()
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
			//quit
			if (event.key.code == Keyboard::Escape)
			{
				return false;
			}

			//Directions
			if (event.key.code == Keyboard::Up)
			{
				this->addDirection(Direction::UP);
			}
			else if (event.key.code == Keyboard::Down)
			{
				this->addDirection(Direction::DOWN);
			}
			else if (event.key.code == Keyboard::Right)
			{
				this->addDirection(Direction::RIGHT);
			}
			else if (event.key.code == Keyboard::Left)
			{
				this->addDirection(Direction::LEFT);
			}
		}
	}
	return true;
}

bool Game::update()
{
	if (this->timeSinceLastMove.asSeconds() >= seconds(1.f / float(this->speed)).asSeconds())
	{
		Vector2f headSectionPosition = this->snake[0].getPosition();
		Vector2f TailSectionPosition = headSectionPosition;

		//we make sure dont reveerse snake direction
		if (!this->directionsQueue.empty())
		{
			switch (this->snakeDirection)
			{
			case Direction::UP:
				if (this->directionsQueue.front() != Direction::DOWN)
				{
					this->snakeDirection = this->directionsQueue.front();
				}
				break;
			case Direction::DOWN:
				if (this->directionsQueue.front() != Direction::UP)
				{
					this->snakeDirection = this->directionsQueue.front();
				}
				break;
			case Direction::RIGHT:
				if (this->directionsQueue.front() != Direction::LEFT)
				{
					this->snakeDirection = this->directionsQueue.front();
				}
				break;
			case Direction::LEFT:
				if (this->directionsQueue.front() != Direction::RIGHT)
				{
					this->snakeDirection = this->directionsQueue.front();
				}
				break;
			}
			this->directionsQueue.pop_front();
		}

		//if there are some sections to add to snake body
		if (this->sectionsToAdd >= 0)
		{
			this->sectionsToAdd--;
			this->addSnakeSection();
		}

		//update snake Head positions
		switch (this->snakeDirection)
		{
		case Direction::RIGHT:
			this->snake[0].setPosition(Vector2f(headSectionPosition.x + 30, headSectionPosition.y));
			break;
		case Direction::LEFT:
			this->snake[0].setPosition(Vector2f(headSectionPosition.x - 30, headSectionPosition.y));
			break;
		case Direction::UP:
			this->snake[0].setPosition(Vector2f(headSectionPosition.x, headSectionPosition.y - 30));
			break;
		case Direction::DOWN:
			this->snake[0].setPosition(Vector2f(headSectionPosition.x, headSectionPosition.y + 30));
			break;
		}

		//update snake tail positions
		for (int i = 1; i < this->snake.size(); i++)
		{
			headSectionPosition = this->snake[i].getPosition();
			this->snake[i].setPosition(TailSectionPosition);
			TailSectionPosition = headSectionPosition;
		}

		//now calling the run for snakesections to run_update the positions
		for (auto& s : this->snake)
		{
			s.update();
		}

		//collision detection if the snake hits the apple basically ate the apple
		if (this->snake[0].getShape().getGlobalBounds().intersects(this->apple.getApple().getGlobalBounds()))
		{
			this->sectionsToAdd += 1;
			this->score += 2;
			this->generateApple = true;
			this->Eaten.play();
		}

		//check the direction of snake and set the texture according to direction
		this->checkSnakeHeadDirections();

		//check if snake hits the walls
		for (auto& w : this->wall.getWalls())
		{
			if (w.getGlobalBounds().intersects(this->snake[0].getShape().getGlobalBounds()))
			{
				return false;
			}
		}

		//check if snake hits its own body
		for (int i = 1; i < this->snake.size(); i++)
		{
			if (this->snake[0].getPosition() == snake[i].getPosition())
			{
				return false;
			}
		}


		//update levels
		this->Levels();

		//reset the time of since last move for next move
		this->timeSinceLastMove = Time::Zero;
	}
	return true;
}

void Game::addDirection(int newDirection)
{
	bool isEmpty = false;
	if (this->directionsQueue.empty()) { isEmpty = true; }

	//if the new direction is already the current direction it will skip it
	if (!this->directionsQueue.empty() && newDirection != this->directionsQueue.back())
	{
		this->directionsQueue.emplace_back(newDirection);

	}
	else if (isEmpty) // if the direction queue is empty will add new direction
	{
		this->directionsQueue.emplace_back(newDirection);
	}
}

void Game::checkSnakeHeadDirections()
{
	//check the direction of snake and set the texture according to direction
	if (this->snakeDirection == Direction::DOWN && !this->snake[0].getHeadDirectionDown())
	{
		this->snake[0].setHeadDirection("DOWN");
		this->snake[0].setTexture(&this->SnakeHeadDown);
	}
	else if (this->snakeDirection == Direction::UP && !this->snake[0].getHeadDirectionUp())
	{
		this->snake[0].setHeadDirection("UP");
		this->snake[0].setTexture(&this->SnakeHeadUp);
	}
	else if (this->snakeDirection == Direction::LEFT && !this->snake[0].getHeadDirectionLeft())
	{
		this->snake[0].setHeadDirection("LEFT");
		this->snake[0].setTexture(&this->SnakeHeadLeft);
	}
	else if (this->snakeDirection == Direction::RIGHT && !this->snake[0].getHeadDirectionRight())
	{
		this->snake[0].setHeadDirection("RIGHT");
		this->snake[0].setTexture(&this->SnakeHeadRight);
	}
}

void Game::draw()
{
	this->window->clear(Color::Black);
	//draw background
	this->window->draw(this->Grass);
	this->window->draw(this->ScoreBar);

	//draw walls
	this->wall.draw(this->window);

	//draw apple
	this->apple.drawApple(this->window);

	//draw snake
	for (auto& s : this->snake)
	{
		window->draw(s.getShape());
	}
	if (this->pause)
	{
		this->playTimer();
		this->window->draw(this->PlayTimer);
	}
	this->window->draw(this->ScoreBackground);
	this->window->draw(this->LevelBackground);
	this->window->draw(this->HighestBackground);
	this->window->draw(this->Score);
	this->window->draw(this->Level);
	this->window->draw(this->Highest);
	this->window->display();
}

int Game::run(RenderWindow& window)
{
	Clock clock;
	this->window = &window;
	if (this->newgame)
	{
		this->newGame(); //generate snake with its right initial direction
		this->newgame = false;
	}

	//window will be running until its closed
	while (this->window->isOpen())
	{
		this->timeSinceLastMove += clock.restart();
		if (!this->input()) { this->pause = true; return 2; } //to mainMenu
		this->draw();
		if (!this->pause)
		{
			if (!this->update()) { this->newgame = true; return 1; } //GameOver
		}
		if (this->generateApple)
		{
			this->apple.moveApple(this->window, this->snake, this->wall.getWalls(), this->ScoreBar);
			this->generateApple = false;
		}
	}
	return 0;
}