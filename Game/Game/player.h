#pragma once

#include "window.h"
#include <SFML/Graphics.hpp>

class Player
{
public:
	sf::RectangleShape selector; //The ui for selecting tiles
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	Player();

	void update(); //Update the moving functions.

private:
	void moveCam(); // Moves the camera position. This is done by changing the viewport

	void getInput();

};