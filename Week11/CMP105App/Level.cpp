#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	// initialise game objects
	audio->addMusic("sfx/cantina.ogg", "cantina");
	
	//Moving circle defined
	circle.setRadius(15);
	circle.setPosition(300, 300);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineColor(sf::Color::Magenta);
	circle.setOutlineThickness(2.f);

	speed.x = 150.0f;
	speed.y = 150.0f;

	dir.x = 1;
	dir.y = 1;
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	if (gameState->getCurrentState(State::MENU))
	{
		if (input->isKeyDown(sf::Keyboard::R))
		{
			gameState->setCurrentState(State::GAME);
		}
	}

}



// Update game objects
void Level::update(float dt)
{

	if (circle.getPosition().x + (circle.getRadius() * 2) >= (window->getSize().x))
	{
		// Move circle so it is not past the edge
		circle.setPosition(window->getSize().x - (circle.getRadius() * 2), circle.getPosition().y);

		// Reverse speed
		dir.x = -1;
	}
	else if (circle.getPosition().x <= 0)
	{
		// Move circle so it is not past the edge
		circle.setPosition(0, circle.getPosition().y);

		// change direction 
		dir.x = 1;
	}

	if (circle.getPosition().y + (circle.getRadius() * 2) >= (window->getSize().y))
	{
		// Move circle so it is not past the edge
		circle.setPosition(circle.getPosition().x, window->getSize().y - (circle.getRadius() * 2));

		// change direction
		dir.y = -1;
	}
	else if (circle.getPosition().y <= 0)
	{
		// Move circle so it is not past the edge
		circle.setPosition(circle.getPosition().x, 0);

		// change direction
		dir.y = 1;
	}


	//Update/move circle
	circle.move(speed.x * dt * dir.x, speed.y * dt * dir.y);
}

	
}

// Render level
void Level::render()
{
	beginDraw();

	if (gameState->setCurrentState(State::GAME))
	{
		window->draw(circle);
	}
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}