#include "chunk.h"
#include <algorithm>
#include <ranges>
#include <iostream>
using namespace std::ranges;
using namespace std::ranges::views;
chunk::chunk(sf::Vector2i pos, std::shared_ptr<sf::Texture> textures)
{
	map_size.x = 32; map_size.y = 32;
	tiles.resize(32 * 32 * 5);
	texture = textures;

	tile_size = sf::Vector2u(64,64); // pixels
	chunk_pos = pos;
	create_corners(pos);
	create_tiles(pos);

	world_position = sf::Vector2f(pos.x, pos.y);

}
void chunk::create_tiles(sf::Vector2i chunk_position)
{
	tile_list.clear();
	
	for (int x = 0; x < map_size.x; x++)
	{
		for (int y = 0; y < map_size.y; y++)
		{
			const uint16_t index = (x + y * map_size.x) * 4;
	
			tiles[index].points.resize(4);
			tiles[index].type = texture_enum::grass_1;
		
			// Get a pointer to the mem loc where the tile should start
			const auto quad = &tiles[index].points[0];
			sf::Vector2f pos;
			
			const auto coords_isometric = t2D_to_isometric(sf::Vector2f(((x) + chunk_position.x*map_size.x), (y+chunk_position.y*map_size.y)), sf::Vector2f(64, 64));
			pos.x = (coords_isometric.x - coords_isometric.y)-32; //32 because the chunk is offset by 32 to the middle
			pos.y = ((coords_isometric.x + coords_isometric.y)/2);

			auto points_coords = pos_coords(pos);
			//Get what texture is applied accordning to what type it has // Enum
			const int tx = static_cast<int>(tiles[index].type) % 9;
			const int ty = static_cast<int>(tiles[index].type) / 9;

			auto texture_coordinates = tex_coords(sf::Vector2i(tx, ty));
			//Get points to the vertex, These point is isometric points converted from 2d perspective
			for(const auto i : iota(0,4))
			{
				quad[i] = points_coords[i];
				quad[i].texCoords = texture_coordinates[i];//Assign the texture coordinates to the vertex
				tile_list.push_back(tiles[index].points[i]);
			}
			

		}
	}

}

//Add one tile to a certain position
void chunk::add_tile(const sf::Vector2i grid_pos, sf::Vector2i chunk_position)
{
	const int index = (grid_pos.x + grid_pos.y * map_size.x) * 4;
	std::vector<Block> ss;
	ss.resize(32 * 32 * 5);
	sf::Vector2f pos;
	ss[index].points.resize(5);
	//Needs to convert for the algoritm later.
	const auto quad = &ss[index].points[0];

	const auto coords_isometric = t2D_to_isometric(sf::Vector2f(((grid_pos.x) + chunk_pos.x * map_size.x), grid_pos.y+(chunk_pos.y * map_size.y)), sf::Vector2f(64, 64));

	pos.x = (coords_isometric.x - coords_isometric.y) - 32; //32 because the chunk is offset by 32 to the middle
	pos.y = ((coords_isometric.x + coords_isometric.y) / 2);
	const auto points_coords = pos_coords(pos);


	//Get what texture is applied accordning to what type it has // Enum
	const int tx = static_cast<int>(texture_enum::grass_4) % 9;
	const int ty = static_cast<int>(texture_enum::grass_4) / 9;

	const auto texture_coordinates = tex_coords(sf::Vector2i(tx, ty));

	//Assign the texture coordinates to the vertex
	for (const auto i : iota(0, 4))
	{
		
		quad[i] = points_coords[i];
		quad[i].texCoords = texture_coordinates[i];//Assign the texture coordinates to the vertex
		tile_list.push_back(ss[index].points[i]);
	}
	
}

void chunk::remove_tile(const sf::Vector2i grid_pos)
{
	uint16_t const index = (grid_pos.x + grid_pos.y * map_size.x) * 4;
	const auto t = &tile_list[index];
	t[0].texCoords = sf::Vector2f(0,0);
	t[1].texCoords = sf::Vector2f(64,0);
	t[2].texCoords = sf::Vector2f(64,64);
	t[3].texCoords = sf::Vector2f(0,64);
	
}

sf::Vector2f chunk::iso_to_2d(const sf::Vector2f coordinate)
{
	sf::Vector2f pos;
	pos.x = (2 * (coordinate.y) + (coordinate.x)) / 2;
	pos.y = (2 * (coordinate.y) - (coordinate.x)) / 2;
	return pos;
}

sf::Vector2f chunk::get_tile_coordinates(const sf::Vector2f coordinate) const 
{
	sf::Vector2f pos;
	pos.x = floor(coordinate.x / map_size.x);
	pos.y = floor(coordinate.y / map_size.y);
	return pos; // returns vector coordinates from world coordinates,
}

sf::Vector2f chunk::t2D_to_isometric(sf::Vector2f coordinates, const sf::Vector2f tile_size)
{
	return { coordinates.x * (tile_size.x / 2), coordinates.y * (tile_size.y / 2) };
}

std::vector<sf::Vector2f> chunk::pos_coords(sf::Vector2f pos) const
{
	std::vector<sf::Vector2f> coordinates;
	coordinates.resize(4);

	coordinates[0] = sf::Vector2f(pos.x, pos.y);
	coordinates[1] = sf::Vector2f(pos.x + tile_size.x, pos.y);
	coordinates[2] = sf::Vector2f(pos.x + tile_size.x, pos.y + tile_size.y);
	coordinates[3] = sf::Vector2f(pos.x, pos.y + tile_size.y);

	return coordinates;
}

std::vector<sf::Vector2f> chunk::tex_coords(sf::Vector2i pos) const
{
	std::vector<sf::Vector2f> coordinates;
	coordinates.resize(4);

	coordinates[0] = sf::Vector2f(64 * pos.x, 64 * pos.y);
	coordinates[1] = sf::Vector2f(tile_size.x + 64 * pos.x, 64 * pos.y);
	coordinates[2] = sf::Vector2f(tile_size.x + 64 * pos.x, tile_size.y + 64 * pos.y);
	coordinates[3] = sf::Vector2f(64 * pos.x, tile_size.y + 64 * pos.y);

	return coordinates;
}

sf::Vector2i chunk::screen_to_map(const sf::Vector2f pos) const
{
	const float x = round((pos.x / map_size.x + (pos.y / map_size.y)) / 2);
	const float y = round((pos.y / map_size.y - (pos.x / map_size.x)) / 2);
	return	sf::Vector2i(x, abs(y));
}

sf::Vector2i chunk::get_middle_tile(const sf::Vector2f player_pos)
{
	const auto t = screen_to_map(sf::Vector2f(player_pos.x, player_pos.y));
	return sf::Vector2i(t.x, t.y);
}


 void chunk::draw_tile_map() const
{
	display.states.texture = texture.get();
	display.display.draw(tile_list.data(), tile_list.size(), sf::Quads, display.states);
	 
}

 void chunk::create_corners(sf::Vector2i pos)
 {
	 corner_positions.resize(4);
	 sf::Vector2f pot;
	 auto temp = t2D_to_isometric(sf::Vector2f(pos.x * map_size.x, pos.y * map_size.y), sf::Vector2f(64, 64));
	 pot.x = (temp.x - temp.y); //32 because the chunk is offset by 32 to the middle
	 pot.y = ((temp.x + temp.y) / 2);
	 corner_positions[0].setPosition(sf::Vector2f(pot.x, pot.y));


	 temp = t2D_to_isometric(sf::Vector2f((pos.x + 1) * map_size.x, pos.y * map_size.y), sf::Vector2f(64, 64));
	 pot.x = (temp.x - temp.y); //32 because the chunk is offset by 32 to the middle
	 pot.y = ((temp.x + temp.y) / 2);
	 corner_positions[1].setPosition(sf::Vector2f(pot.x, pot.y));

	 temp = t2D_to_isometric(sf::Vector2f((pos.x) * map_size.x, (pot.y + 1) * map_size.y), sf::Vector2f(64, 64));
	 pot.x = (temp.x - temp.y); //32 because the chunk is offset by 32 to the middle
	 pot.y = ((temp.x + temp.y) / 2);
	 corner_positions[2].setPosition(sf::Vector2f(pot.x, pot.y));

	 temp = t2D_to_isometric(sf::Vector2f((pot.x + 1) * map_size.x, (pot.y + 1) * map_size.y), sf::Vector2f(64, 64));
	 pot.x = (temp.x - temp.y); //32 because the chunk is offset by 32 to the middle
	 pot.y = ((temp.x + temp.y) / 2);
	 corner_positions[3].setPosition(sf::Vector2f(pot.x, pot.y));

	 corner_positions[0].setSize(sf::Vector2f(10, 10));
	 corner_positions[1].setSize(sf::Vector2f(10, 10));
	 corner_positions[2].setSize(sf::Vector2f(10, 10));
	 corner_positions[3].setSize(sf::Vector2f(10, 10));

 }

 std::vector<sf::Vertex> chunk::get_tile(const sf::Vector2f grid_pos) const
 {
	 //Code to draw a tile from mouse pos
	 if (grid_pos.x <= map_size.x && grid_pos.x >= 0)
		 if (grid_pos.y <= map_size.y && grid_pos.y >= 0)
		 {
			 int const index = (grid_pos.x + grid_pos.y * map_size.x) * 4;
			 std::vector<sf::Vertex> q;
			 display.states.texture = texture.get();
			 display.display.draw(q.data(), q.size(), sf::Quads, display.states);
			 return q;
		 }
	 return std::vector<sf::Vertex>();
 }