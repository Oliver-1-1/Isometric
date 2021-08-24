#include "window.h"

Window::Window()
{
	this->window.create(sf::VideoMode(settings.resolutionX, settings.resolutionY), "window");
	
	this->viewPort.setSize((float)settings.resolutionX, (float)settings.resolutionY);
	this->viewPort.setCenter((float)settings.resolutionX / 2.f, (float)settings.resolutionY / 2.f);
	
	this->window.setView(this->viewPort);
}

Window::~Window()
{
	
}

//This can brake some functions that dosnt run in loop
void Window::updateResolution(int x, int y)
{
	window.setSize(sf::Vector2u(x, y));

	settings.resolutionX = x;
	settings.resolutionY = y;

	this->viewPort.setSize((float)settings.resolutionX, (float)settings.resolutionY);
	this->viewPort.setCenter((float)settings.resolutionX / 2.f, (float)settings.resolutionY / 2.f);
	this->viewPort.move(0, 0);
	this->window.setView(this->viewPort);
}


