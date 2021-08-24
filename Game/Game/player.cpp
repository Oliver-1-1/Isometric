#include "player.h"

Player::Player()
{
}

void Player::update()
{
	getInput();
	moveCam();
}

void Player::moveCam()
{
	//TODO MOUSE INPUT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		window.viewPort.move(-1, 0);
		window.window.setView(window.viewPort);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		window.viewPort.move(sf::Vector2f(1, 0));
		window.window.setView(window.viewPort);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		window.viewPort.move(0, -1);
		window.window.setView(window.viewPort);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		window.viewPort.move(sf::Vector2f(0, 1));
		window.window.setView(window.viewPort);
	}
}

void Player::getInput()
{
	//Tile selector

//Reseting mouse starting position
	this->mousePosView = window.window.mapPixelToCoords(sf::Mouse::getPosition(window.window)); //Make sure we have in game coords

	//Clamp so it snaps 16 pixels
	if (this->mousePosView.x >= 0.f)
		this->mousePosGrid.x = this->mousePosView.x / 64;
	if (this->mousePosView.y >= 0.f)
		this->mousePosGrid.y = this->mousePosView.y / 64;

	// Set the selectors position
	this->selector.setPosition(this->mousePosGrid.x * 64, this->mousePosGrid.y * 64);
}
