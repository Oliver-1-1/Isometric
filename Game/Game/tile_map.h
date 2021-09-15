#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include <iostream>
#include "window.h"
#include <vector>
#include <string>
struct coord
{
	int x;
	int y;
};
enum te
{
	x,y
};
enum texture_enum
{
	//Coordinate system
	air = 0,		// (0, 0)
	grass_1 = 1,	// (1, 0)
	grass_2 = 2,	// (2, 0)
	grass_3 = 3,	// (3, 0)
	grass_4 = 4,	// (4, 0)
	grass_5 = 5,	// (5, 0)
	grass_6 = 6,	// (6, 0)
	grass_7 = 7,	// (7, 0)
	grass_8 = 8,	// (8, 0)
	grass_9 = 9,	// (9, 0)

	// Y = 1

	grass_10 = 10,	// (0, 1)
	grass_11 = 11,	// (1, 1)
	grass_12 = 12,	// (2, 1)
	grass_13 = 13,	// (3, 1)
	grass_14 = 14,	// (4, 1)
	grass_15 = 15,	// (5, 1)
	grass_16 = 16,	// (6, 1)
	grass_17 = 17,	// (7, 1)
	grass_18 = 18,	// (8, 1)
	
};
struct Block
{
	std::vector<sf::Vertex> points;
	sf::Texture texture;
	texture_enum type;
};



class tile_map
{
public:

	std::vector<sf::Vertex> tile_list;
	tile_map();
	sf::Texture texture;
	std::vector<Block> tiles2;
	sf::Vector2i map_size;
	sf::Vector2u tile_size;
	std::vector<sf::Vector2f> pos_coords(sf::Vector2f pos) const;
	std::vector<sf::Vector2f> tex_coords(sf::Vector2i pos) const;
	
	void populate_tile_map(uint16_t z);
	void add_tile(sf::Vector2i grid_pos, uint16_t z);
	void remove_tile(sf::Vector2i grid_pos);
	void draw_tile_map() const;

	std::vector<sf::Vertex> get_tile(sf::Vector2f grid_pos) const;
	sf::Vector2f screen_to_map(const sf::Vector2f pos) const;
	static sf::Vector2f t2D_to_isometric(sf::Vector2f coordinates, sf::Vector2f tile_size);
	sf::Vector2f get_tile_coordinates(sf::Vector2f coordinate) const;
	static sf::Vector2f iso_to_2d(sf::Vector2f coordinate);
private:
	 void create_tiles(uint16_t z);
}; 