#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include <iostream>
#include "window.h"
#include <vector>
class tile_map
{
public:
	
	tile_map();
	std::vector<sf::Vertex> tiles;
	
	sf::Texture texture;
	sf::Texture texture1;
	
	sf::Vector2i map_size;
	sf::Vector2u tile_size;


	void populate_tile_map();
	void add_tile(sf::Vector2i grid_pos);
	void remove_tile(sf::Vector2i grid_pos);
	void draw_tile_map() const;
	std::vector<sf::Vertex> get_tile(sf::Vector2f grid_pos);
	sf::Vector2f screen_to_map(const sf::Vector2f pos);
	sf::Vector2f t2D_to_isometric(sf::Vector2f coordinates, sf::Vector2f tile_size);
	sf::Vector2f get_tile_coordinates(sf::Vector2f coordinate);
	sf::Vector2f iso_to_2d(sf::Vector2f coordinate);
private:
	 void create_tiles();
	 static sf::Vector2i calc_screen_tiles(int resolution_x, int resolution_y, int tile_size);
};