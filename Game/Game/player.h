#pragma once

#include "window.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "window.h"
class player
{
public:
	player();
	~player() = default;
	void move_cam(); // Moves the camera position. This is done by changing the viewport

private:
	uint16_t player_speed;

};