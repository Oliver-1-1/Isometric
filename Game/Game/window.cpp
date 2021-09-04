#include "window.h"

#include <iostream>

window::window()
{
	this->display.create(sf::VideoMode(settings.resolution_x, settings.resolution_y), "display");
	
	this->view_port.setSize(static_cast<float>(settings.resolution_x), static_cast<float>(settings.resolution_y));
	this->view_port.setCenter(static_cast<float>(settings.resolution_x) / 2.f, static_cast<float>(settings.resolution_y) / 2.f);
	
	this->display.setView(this->view_port);
}



//This can brake some functions that dosnt run in loop
void window::update_resolution(int x, int y)
{
	display.setSize(sf::Vector2u(x, y));

	settings.resolution_x = x;
	settings.resolution_y = y;
	
	this->view_port.setSize(static_cast<float>(settings.resolution_x), static_cast<float>(settings.resolution_y));
	this->view_port.setCenter(static_cast<float>(settings.resolution_x) / 2.f, static_cast<float>(settings.resolution_y) / 2.f);
	this->view_port.move(0, 0);
	this->display.setView(this->view_port);
}




