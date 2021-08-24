#include "tileMap.h"

TileMap::TileMap()
{
	
	mapSize = calcScreenTiles(settings.resolutionX, settings.resolutionY, 16);
	mapSize.x = 16; mapSize.y = 16;
	this->texture.loadFromFile("blocks_1.png");
	this->tileSize = this->texture.getSize(); // pixels

	this->tiles.resize(this->mapSize.x * this->mapSize.y * 5);	
	window.states.texture = &this->texture;
}

void TileMap::populateTileMap()
{

	//Could be moved to a seperate function
	this->tileSelector.setSize(sf::Vector2f(this->tileSize.x, this->tileSize.y));
	this->tileSelector.setFillColor(sf::Color::Transparent);
	this->tileSelector.setOutlineThickness(1.f);
	this->tileSelector.setOutlineColor(sf::Color::Green);
	
	this->createTiles();
}

void TileMap::addTile(sf::Vector2i gridPos)
{
	sf::Vertex* quad = &this->tiles[(gridPos.x + gridPos.y * mapSize.x) * 4];
	sf::Vector2f pos;
	pos.x = (gridPos.x - gridPos.y) * 32;
	pos.y = (gridPos.x + gridPos.y) * 16;
	int tu = 0 % (this->texture.getSize().x / 64);
	int tv = 0 / (this->texture.getSize().x / 64);


	quad[0].position = sf::Vector2f(pos.x, pos.y);
	quad[1].position = sf::Vector2f(pos.x + tileSize.x, pos.y);
	quad[2].position = sf::Vector2f(pos.x + tileSize.x, pos.y + tileSize.y);
	quad[3].position = sf::Vector2f(pos.x, pos.y + tileSize.y);
	sf::Vector2i tileSize(64, 64);
	
	quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
	quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
	quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
	quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
}

void TileMap::removeTile(sf::Vector2i gridPos)
{

	sf::Vertex* quad = &this->tiles[(gridPos.x + gridPos.y * mapSize.x) * 4];
	std::cout << quad[0].position.x;
}

 void TileMap::drawTileMap() const
{
	
	window.window.draw(tiles.data(), tiles.size(), sf::Quads, window.states);
	 
}
 
void TileMap::createTiles() 
{
	for (int x = 0; x < mapSize.x; x++)
	{
		for (int y = 0; y < mapSize.y; y++)
		{
			int tileNumber = 0; // put tile layout here

			// find its position in the tileset texture
			int tu = tileNumber % (this->texture.getSize().x / 64);
			int tv = tileNumber / (this->texture.getSize().x / 64);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &this->tiles[(x + y * mapSize.x) * 4];
	
			sf::Vector2f pos;
			pos.x = (x - y) * 32;
			pos.y = (x + y) * 16;

			sf::Vector2i tileSize(64, 64);
			quad[0].position = sf::Vector2f(pos.x, pos.y);
			
			quad[1].position = sf::Vector2f(pos.x+ tileSize.x, pos.y);
			quad[2].position = sf::Vector2f(pos.x+tileSize.x, pos.y+tileSize.y);
			quad[3].position = sf::Vector2f(pos.x, pos.y+tileSize.y);

			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}



}

sf::Vector2i TileMap::calcScreenTiles(int resolutionX, int resolutionY, int tileSize)
{
	return sf::Vector2i((int)resolutionX/tileSize, (int)resolutionY/tileSize);
}

