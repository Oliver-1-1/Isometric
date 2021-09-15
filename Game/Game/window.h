#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
class window
{
public:
	sf::RenderWindow display;
	sf::RenderStates states;
	sf::View view_port;
	
	window();
	~window() = default;
	void update_resolution(int x, int y);
	sf::Vector2f get_mouse_position() const;
private:

};

extern window display;