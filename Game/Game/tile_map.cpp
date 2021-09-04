#include "tile_map.h"
#include <algorithm>
tile_map::tile_map()
{
	
	map_size = calc_screen_tiles(settings.resolution_x, settings.resolution_y, 16);
	map_size.x = 16; map_size.y = 16;
	this->texture.loadFromFile("blocks_1.png");
	this->texture1.loadFromFile("0.png");
	this->tile_size = this->texture.getSize(); // pixels

	this->tiles.resize(this->map_size.x * this->map_size.y * 5);	
}

void tile_map::populate_tile_map()
{
	this->create_tiles();
}

 void tile_map::draw_tile_map() const
{
	display.states.texture = &this->texture;
	

	display.display.draw(tiles.data(), tiles.size(), sf::Quads, display.states);
	 
}

 std::vector<sf::Vertex> tile_map::get_tile(sf::Vector2f grid_pos)
 {
	 //Code to draw a tile from mouse pos
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	 {

		 std::cout << grid_pos.x << " " << grid_pos.y << std::endl;
		 if (grid_pos.x <= 16 && grid_pos.x >= 0)
			 if (grid_pos.y <= 16 && grid_pos.y >= 0)
			 {
				 int const index = (grid_pos.x + grid_pos.y * map_size.x) * 4;
				 std::vector<sf::Vertex> q;
				 for (int i = index; i < index + 4; i++)
					 q.push_back(tiles[i]);
					 
				 display.states.texture = &this->texture1;
				 display.display.draw(q.data(), q.size(), sf::Quads, display.states);
				 return q;
			 }
		 
	 }
	 return std::vector<sf::Vertex>();

 }

 sf::Vector2f tile_map::screen_to_map(const sf::Vector2f pos)
 {
	 
	 const float x = round((pos.x / 32 + pos.y / 32) / 2);
	 const float y = round((pos.y/32 - (pos.x/32))/2);
	 return sf::Vector2f(x, y);
 }

 sf::Vector2f tile_map::t2D_to_isometric(sf::Vector2f coordinates, const sf::Vector2f tile_size)
 {
	 return sf::Vector2f(coordinates.x * (tile_size.x / 2), coordinates.y * (tile_size.y / 2));
 }

 sf::Vector2f tile_map::get_tile_coordinates(sf::Vector2f coordinate)
 {
	 sf::Vector2f pos;
	 pos.x = floor(coordinate.x / 32);
	 pos.y = floor(coordinate.y / 32);
	 return pos;
 }

 sf::Vector2f tile_map::iso_to_2d(sf::Vector2f coordinate)
 {
	sf::Vector2f pos;
	pos.x = (2 * (coordinate.y) + (coordinate.x)) / 2;
	pos.y = (2 * (coordinate.y) - (coordinate.x)) / 2;
	 return pos;
 }
 
void tile_map::create_tiles() 
{
	for (int x = 0; x < map_size.x; x++)
	{
		for (int y = 0; y < map_size.y; y++)
		{
			const int tileNumber = 0; // put tile layout here

			// find its position in the tileset texture
			const int tu = tileNumber % (this->texture.getSize().x / 64);
			const int tv = tileNumber / (this->texture.getSize().x / 64);

			// Get a pointer to the mem loc where the tile should start
			sf::Vertex* quad = &tiles[(x + y * map_size.x) * 4];

			sf::Vector2f pos;

			//                      2D
			auto coords_2d = t2D_to_isometric(sf::Vector2f(x, y), sf::Vector2f(64, 64));
			pos.x = (coords_2d.x - coords_2d.y) - 32;
			pos.y = (coords_2d.x + coords_2d.y)/2;
			quad[0].position = sf::Vector2f(pos.x, pos.y);
			
			quad[1].position = sf::Vector2f(pos.x + tile_size.x, pos.y);
			quad[2].position = sf::Vector2f(pos.x + tile_size.x, pos.y + tile_size.y);
			quad[3].position = sf::Vector2f(pos.x, pos.y + tile_size.y);
			
			quad[0].texCoords = sf::Vector2f(tile_size.x * tu, tv * tile_size.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
			quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
		}
	}

}

sf::Vector2i tile_map::calc_screen_tiles(int resolution_x, int resolution_y, int tile_size)
{
	return {static_cast<int>(resolution_x) / tile_size, static_cast<int>(resolution_y) / tile_size};
}

void tile_map::add_tile(sf::Vector2i grid_pos)
{
	sf::Vertex* quad = &this->tiles[(grid_pos.x + grid_pos.y * map_size.x) * 4];
	sf::Vector2f pos;
	auto coords_2d = t2D_to_isometric(sf::Vector2f(grid_pos.x, grid_pos.y), sf::Vector2f(64, 64));
	pos.x = (coords_2d.x - coords_2d.y);
	pos.y = (coords_2d.x + coords_2d.y) / 2;
	const int tu = 0 % (this->texture.getSize().x / 64);
	const int tv = 0 / (this->texture.getSize().x / 64);


	quad[0].position = sf::Vector2f(pos.x, pos.y);
	quad[1].position = sf::Vector2f(pos.x + tile_size.x, pos.y);
	quad[2].position = sf::Vector2f(pos.x + tile_size.x, pos.y + tile_size.y);
	quad[3].position = sf::Vector2f(pos.x, pos.y + tile_size.y);

	quad[0].texCoords = sf::Vector2f(tu * tile_size.x, tv * tile_size.y);
	quad[1].texCoords = sf::Vector2f((tu + 1) * tile_size.x, tv * tile_size.y);
	quad[2].texCoords = sf::Vector2f((tu + 1) * tile_size.x, (tv + 1) * tile_size.y);
	quad[3].texCoords = sf::Vector2f(tu * tile_size.x, (tv + 1) * tile_size.y);
}

void tile_map::remove_tile(sf::Vector2i grid_pos)
{

	int const index = (grid_pos.x + grid_pos.y * map_size.x) * 4;
	tiles.erase(tiles.begin() + index, tiles.begin() + index + 4);

}
