
#include "player.h"
player::player()
{
	player_speed = 50;
}

void player::move_cam()
{
	//TODO MOUSE INPUT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		display.view_port.move(-player_speed, 0);
		display.display.setView(display.view_port);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//display.view_port.move(sf::Vector2f(1, 0));
		display.view_port.move(player_speed, 0);
		display.display.setView(display.view_port);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		display.view_port.move(0, -player_speed);
		display.display.setView(display.view_port);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		display.view_port.move(0, player_speed);
		display.display.setView(display.view_port);
	}
}

