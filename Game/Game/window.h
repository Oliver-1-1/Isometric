#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
class Window
{
public:
	sf::RenderWindow window;
	sf::RenderStates states;
	sf::View viewPort;
	
	Window();
	~Window();
	void updateResolution(int x, int y);
private:

};

extern Window window;