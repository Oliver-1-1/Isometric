#pragma once

#include "window.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "window.h"
class player
{
public:
	sf::Vector2f mouse_pos_view;
	sf::Vector2u mouse_pos_grid;
	std::vector<sf::Vertex> sel;
	player();

	void update(); //Update the moving functions.
	sf::Vector2i get_selector_position(std::vector<sf::Vertex> vertices);
private:
	void move_cam(); // Moves the camera position. This is done by changing the viewport

	void get_input();

};