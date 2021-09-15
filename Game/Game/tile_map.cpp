#include "tile_map.h"
#include <algorithm>
#include <ranges>
#include <iostream>
using namespace std::ranges;
using namespace std::ranges::views;
tile_map::tile_map()
{
	map_size.x = 32; map_size.y = 32;
	texture.loadFromFile("terrain_0.png");

	this->tile_size = sf::Vector2u(64,64); // pixels

	//this->tiles.resize(this->map_size.x * this->map_size.y * 5 + this->map_size.x * this->map_size.y * 5 + this->map_size.x * this->map_size.y * 5);
	this->tiles2.resize((this->map_size.x * this->map_size.y)*5);
}

 std::vector<sf::Vertex> tile_map::get_tile(const sf::Vector2f grid_pos) const
 {
	 //Code to draw a tile from mouse pos
	if (grid_pos.x <= map_size.x && grid_pos.x >= 0)
		if (grid_pos.y <= map_size.y && grid_pos.y >= 0)
		{
			int const index = (grid_pos.x + grid_pos.y * map_size.x) * 4;
			std::vector<sf::Vertex> q;

		
			display.states.texture = &this->texture;
			display.display.draw(q.data(), q.size(), sf::Quads, display.states);
			return q;
		}
	 return std::vector<sf::Vertex>();
 }

void tile_map::create_tiles(uint16_t z) 
{
	tile_list.clear();
	for (int x = map_size.x * z; x < map_size.x*(z+1); x++)
	{
		for (int y = map_size.y * z; y < map_size.y*(z+1); y++)
		{
		
			const uint16_t index = (x + y * map_size.x) * 4;

			tiles2[index].points.resize(4);
			tiles2[index].texture = texture;
			tiles2[index].type = texture_enum::grass_1;
			if(x+y > 40)
			{
				tiles2[index].type = texture_enum::grass_2;

			}
			// Get a pointer to the mem loc where the tile should start
			const auto quad = &tiles2[index].points[0];
			sf::Vector2f pos;
			
			const auto coords_isometric = t2D_to_isometric(sf::Vector2f(x - (map_size.x + 1)*z, y - (map_size.y + 1)*z), sf::Vector2f(64, 64));
			pos.x = (coords_isometric.x - coords_isometric.y) - 32;
			pos.y = (coords_isometric.x + coords_isometric.y)/2;

			auto points_coords = pos_coords(pos);

			//Get points to the vertex, These point is isometric points converted from 2d perspective
			for(const auto i : iota(0,4))
			{
				quad[i] = points_coords[i];
			}

			//Get what texture is applied accordning to what type it has // Enum
			const int tx = static_cast<int>(tiles2[index].type) % 9;
			const int ty = static_cast<int>(tiles2[index].type) / 9;
	
			auto texture_coordinates = tex_coords(sf::Vector2i(tx, ty));

			//Assign the texture coordinates to the vertex
			for(const auto i: iota(0,4))
			{
				quad[i].texCoords = texture_coordinates[i];
			}

		}
	}

	for (auto& [points, texture, type] : tiles2)
	{
		for (auto& x : points)
		{
			tile_list.push_back(x);
		}
	}
	
}


//Add one tile to a certain position
void tile_map::add_tile(const sf::Vector2i grid_pos, uint16_t z)
{
	int index = (grid_pos.x + grid_pos.y * map_size.x) * 4;
		
	sf::Vector2f pos;

	//Needs to convert for the algoritm later.
	const auto coords_isometric = t2D_to_isometric(sf::Vector2f(grid_pos.x, grid_pos.y), sf::Vector2f(64, 64));

	pos.x = (coords_isometric.x - coords_isometric.y) - 32;
	pos.y = (coords_isometric.x + coords_isometric.y) / 2;
	const auto points_coords = pos_coords(pos);
	for (const auto i : iota(0, 4))
	{
		tile_list[index + i].position = points_coords[i];
	}

	//Get what texture is applied accordning to what type it has // Enum
	const int tx = static_cast<int>(texture_enum::grass_15) % 9;
	const int ty = static_cast<int>(texture_enum::grass_15) / 9;

	auto texture_coordinates = tex_coords(sf::Vector2i(tx, ty));

	//Assign the texture coordinates to the vertex
	for (const auto i : iota(0, 4))
	{
		tile_list[index + i].texCoords = texture_coordinates[i];
	}
	
}

//Remove a tile from the vector, grid_pos is the position of the tile
void tile_map::remove_tile(const sf::Vector2i grid_pos)
{
	uint16_t const index = (grid_pos.x + grid_pos.y * map_size.x) * 4;
	const auto t = &tile_list[index];
	t[0].texCoords = sf::Vector2f(0,0);
	t[1].texCoords = sf::Vector2f(64,0);
	t[2].texCoords = sf::Vector2f(64,64);
	t[3].texCoords = sf::Vector2f(0,64);
	
}

sf::Vector2f tile_map::iso_to_2d(const sf::Vector2f coordinate) // Converts isometric coordinates to normal 2D coordinates
{
	sf::Vector2f pos;
	pos.x = (2 * (coordinate.y) + (coordinate.x)) / 2;
	pos.y = (2 * (coordinate.y) - (coordinate.x)) / 2;
	return pos;
}

// Needs to be 2d coordinates not isometric
sf::Vector2f tile_map::get_tile_coordinates(const sf::Vector2f coordinate) const 
{
	sf::Vector2f pos;
	pos.x = floor(coordinate.x / 32);
	pos.y = floor(coordinate.y / 32);
	return pos;
}

sf::Vector2f tile_map::t2D_to_isometric(sf::Vector2f coordinates, const sf::Vector2f tile_size)
{
	return { coordinates.x * (tile_size.x / 2), coordinates.y * (tile_size.y / 2) };
}

std::vector<sf::Vector2f> tile_map::pos_coords(sf::Vector2f pos) const
{
	std::vector<sf::Vector2f> coordinates;
	coordinates.resize(4);

	coordinates[0] = sf::Vector2f(pos.x, pos.y);
	coordinates[1] = sf::Vector2f(pos.x + tile_size.x, pos.y);
	coordinates[2] = sf::Vector2f(pos.x + tile_size.x, pos.y + tile_size.y);
	coordinates[3] = sf::Vector2f(pos.x, pos.y + tile_size.y);

	return coordinates;
}

std::vector<sf::Vector2f> tile_map::tex_coords(sf::Vector2i pos) const
{
	std::vector<sf::Vector2f> coordinates;
	coordinates.resize(4);

	coordinates[0] = sf::Vector2f(64 * pos.x, 64 * pos.y);
	coordinates[1] = sf::Vector2f(tile_size.x + 64 * pos.x, 64 * pos.y);
	coordinates[2] = sf::Vector2f(tile_size.x + 64 * pos.x, tile_size.y + 64 * pos.y);
	coordinates[3] = sf::Vector2f(64 * pos.x, tile_size.y + 64 * pos.y);

	return coordinates;
}

sf::Vector2f tile_map::screen_to_map(const sf::Vector2f pos) const
{
	const float x = round((pos.x / 32 + pos.y / 32) / 2);
	const float y = round((pos.y / 32 - (pos.x / 32)) / 2);
	return { x, y };
}

void tile_map::populate_tile_map(uint16_t z)
{
	this->create_tiles(z);
}

 void tile_map::draw_tile_map() const
{
	 
	display.states.texture = &texture;
	display.display.draw(tile_list.data(), tile_list.size(), sf::Quads, display.states);
	 
}