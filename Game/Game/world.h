#include <iostream>
#include <SFML/Graphics.hpp>
#include "chunk.h"
#include <ranges>
class world
{
public:
	world();
	~world() = default;
	void render_world();
	void render_chunk_outlines();
	void detarmain_chunks();
	std::vector<std::vector<chunk>> chunks;

private:
	void initialize_world();
	int world_size; // In chunks like a square
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
	
};