#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include <iostream>
#include "window.h"
#include <vector>
class TileMap
{
public:
	
	TileMap();
	std::vector<sf::Vertex> tiles;
	
	sf::Texture texture;
	
	sf::Vector2i mapSize;
	sf::Vector2u tileSize;

	sf::RectangleShape tileSelector;

	void populateTileMap();
	void addTile(sf::Vector2i gridPos);
	void removeTile(sf::Vector2i gridPos);
	void drawTileMap() const;
	
private:
	 void createTiles();
	 static sf::Vector2i calcScreenTiles(int resolutionX, int resolutionY, int tileSize);
};