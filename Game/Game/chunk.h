#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include <iostream>
#include "window.h"
#include <vector>
#include <string>

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
	int type;
};
 
class chunk
{

public:
	chunk(sf::Vector2i pos/*Chunk position*/, std::shared_ptr<sf::Texture> textures);
	~chunk() = default;

	sf::Vector2f world_position;
	sf::Vector2i chunk_pos;
	std::vector<sf::RectangleShape> corner_positions;
	
	std::vector<sf::Vertex> get_tile(sf::Vector2f grid_pos) const;	//Fetch a tile
	
	void add_tile(sf::Vector2i grid_pos, sf::Vector2i chunk_position); //Add a tile to the map, this is dome by applying a texture to the vertex, since the vertex position is already in a vector
	void remove_tile(sf::Vector2i grid_pos); //Remove a tile. this is done by setting vertex texture position to a non texture in the atlas.

	void draw_tile_map() const; //Draw map

	sf::Vector2f get_tile_coordinates(sf::Vector2f coordinate) const; // Needs to be 2d coordinates not isometric
	sf::Vector2i screen_to_map(const sf::Vector2f pos) const;
	sf::Vector2i get_middle_tile(const sf::Vector2f player_pos);

	static sf::Vector2f iso_to_2d(sf::Vector2f coordinate); // Converts isometric coordinates to normal 2D coordinates
	static sf::Vector2f t2D_to_isometric(sf::Vector2f coordinates, sf::Vector2f tile_size); // Return isometric coordinates from 2D

private:
	 void create_tiles(sf::Vector2i chunk_position);
	 void create_corners(sf::Vector2i pos);
	 sf::Vector2i map_size;
	 sf::Vector2u tile_size;
	 std::vector<sf::Vector2f> pos_coords(sf::Vector2f pos)    const;	//Get the vertex position for the tiles
	 std::vector<sf::Vector2f> tex_coords(sf::Vector2i pos)    const; //Get the texture coords in the texture atlas
	 std::shared_ptr<sf::Texture> texture;
	 std::vector<sf::Vertex> tile_list;
	 std::vector<Block> tiles;
}; 