
#include "player.h"
player::player()
{

}

void player::update()
{
	get_input();
	move_cam();
	display.display.draw(sel.data(), sel.size(), sf::Quads, display.states);

}

sf::Vector2i player::get_selector_position(std::vector<sf::Vertex> vertices)
{
	sel = vertices;

	return sf::Vector2i(0, 0);
}

void player::move_cam()
{
	//TODO MOUSE INPUT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		display.view_port.move(-1, 0);
		display.display.setView(display.view_port);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		display.view_port.move(sf::Vector2f(1, 0));
		display.display.setView(display.view_port);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		display.view_port.move(0, -1);
		display.display.setView(display.view_port);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		display.view_port.move(sf::Vector2f(0, 1));
		display.display.setView(display.view_port);
	}
}

void player::get_input()
{
	//Tile selector

//Resetting mouse starting position
	this->mouse_pos_view = display.display.mapPixelToCoords(sf::Mouse::getPosition(display.display)); //Make sure we have in game coords

	//Clamp so it snaps 64 pixels
	if (this->mouse_pos_view.x >= 0.f)
		this->mouse_pos_grid.x = this->mouse_pos_view.x / 64;
	if (this->mouse_pos_view.y >= 0.f)
		this->mouse_pos_grid.y = this->mouse_pos_view.y / 64;

	// Set the selectors position

}
